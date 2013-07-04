#include "stdafx.h"
#include "MainFrame.h"

#include "PacketCapturer.h"
#include "CaptureThread.h"
#include "ProcessDlg.h"
#include "DeviceDlg.h"

#include <vector>
#include <algorithm>


CMainFrame::CMainFrame(void)
	: MainFrame(NULL, wxID_ANY, wxT("Packet Viewer"))
	, m_selectAttr(wxColour("black"), wxColour("grey"))
	, m_defaultAttr(wxColor("black"), wxColour("white"))
{
	this->Connect(wxEVT_THREAD, wxThreadEventHandler( CMainFrame::OnWorkerEvent ), NULL, this );
	m_capturer = NULL;

	PacketCapturer& inst = PacketCapturer::instance();
	inst.initialize();

	
	InitWidgets();
}


CMainFrame::~CMainFrame(void)
{
	if (m_capturer) {
		m_capturer->Delete();
		m_capturer = NULL;
	}

	PacketCapturer& inst = PacketCapturer::instance();
	inst.finalize();

	this->Disconnect(wxEVT_THREAD, wxThreadEventHandler( CMainFrame::OnWorkerEvent ), NULL, this );

}

void CMainFrame::InitWidgets()
{
	// list control
	m_listCtrl_pktList->AppendColumn(wxT("No."), wxLIST_FORMAT_LEFT, 60);
	m_listCtrl_pktList->AppendColumn(wxT("Time"), wxLIST_FORMAT_LEFT, 80);
	m_listCtrl_pktList->AppendColumn(wxT("Length"), wxLIST_FORMAT_LEFT, 90);
	m_listCtrl_pktList->AppendColumn(wxT("Source IP"), wxLIST_FORMAT_LEFT, 100);
	m_listCtrl_pktList->AppendColumn(wxT("port"), wxLIST_FORMAT_LEFT, 60);
	m_listCtrl_pktList->AppendColumn(wxT("Destination IP"), wxLIST_FORMAT_LEFT, 100);
	m_listCtrl_pktList->AppendColumn(wxT("port"), wxLIST_FORMAT_LEFT, 60);
	m_listCtrl_pktList->AppendColumn(wxT("Dump"), wxLIST_FORMAT_LEFT, 200);

	// text ctrl (fixed width font)
	m_textCtrl_raw->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, L"Consolas", wxFONTENCODING_SYSTEM ));

	// tree control
	wxTreeItemId root = m_treeCtrl_hdr->AddRoot(wxT("Header"));
	wxTreeItemId eth = m_treeCtrl_hdr->AppendItem(root, wxT("Ether frame"));
		wxTreeItemId dstMac = m_treeCtrl_hdr->AppendItem(eth, wxT("Dest Mac"));
		wxTreeItemId srcMac = m_treeCtrl_hdr->AppendItem(eth, wxT("Sorc Mac"));
		wxTreeItemId ipType = m_treeCtrl_hdr->AppendItem(eth, wxT("IP Type"));
	wxTreeItemId ipHdr = m_treeCtrl_hdr->AppendItem(root, wxT("IP frame"));
		wxTreeItemId srcIP = m_treeCtrl_hdr->AppendItem(ipHdr, wxT("Source IP"));
		wxTreeItemId dstIP = m_treeCtrl_hdr->AppendItem(ipHdr, wxT("Desination IP"));
	wxTreeItemId tcpHdr = m_treeCtrl_hdr->AppendItem(root, wxT("TCP frame"));
		wxTreeItemId srcPort = m_treeCtrl_hdr->AppendItem(tcpHdr, wxT("Source Port"));
		wxTreeItemId dstPort = m_treeCtrl_hdr->AppendItem(tcpHdr, wxT("Desination Port"));

	m_treeCtrl_hdr->Expand(root);
	
	m_hdrRangeMap[root] = Range(0, sizeof(ether_header)+sizeof(ip_header)+sizeof(tcp_header));
	m_hdrRangeMap[eth]	= Range(0, sizeof(ether_header));
	m_hdrRangeMap[dstMac] = Range(0, sizeof(uint8)* 6);
	m_hdrRangeMap[srcMac] = Range(sizeof(uint8)* 6, sizeof(uint8)* 6);
	m_hdrRangeMap[ipType] = Range(sizeof(uint8)* 12, sizeof(uint16));
	m_hdrRangeMap[ipHdr] = Range(sizeof(ether_header), sizeof(ip_header));
	m_hdrRangeMap[srcIP] = Range(sizeof(ether_header) + sizeof(uint32)*3, sizeof(uint32));
	m_hdrRangeMap[dstIP] = Range(sizeof(ether_header) + sizeof(uint32)*4, sizeof(uint32));
	m_hdrRangeMap[tcpHdr] = Range(sizeof(ether_header)+sizeof(ip_header), sizeof(tcp_header));
	m_hdrRangeMap[srcPort] = Range(sizeof(ether_header)+sizeof(ip_header), sizeof(uint16));
	m_hdrRangeMap[dstPort] = Range(sizeof(ether_header)+sizeof(ip_header)+sizeof(uint16), sizeof(uint16));

	UpdateWidgetState();
}

void CMainFrame::UpdateWidgetState()
{
	const bool is_running = m_capturer ? m_capturer->IsRunning() : false;
	m_button_start->Enable(!is_running);
	m_button_stop->Enable(is_running);

	PacketCapturer& mgr = PacketCapturer::instance();
	m_checkBox_skipNoData->SetValue( mgr.getNoDataSkip() );
	m_checkBox_sendOnly->SetValue( mgr.getSend() );
	m_checkBox_recvOnly->SetValue( mgr.getRecv() );

	std::vector<byte> macAddr = mgr.getHostMacAddr();
	address ipAddr(mgr.getHostIpAddr());

	m_statusBar->SetStatusText(
		wxString::Format("%s - MAC[%.2x:%.2x:%.2x:%.2x:%.2x:%.2x] - IP[%d.%d.%d.%d]", 
		mgr.getDeviceDesc( mgr.getDeviceIndex() ).c_str(),
		macAddr[0],
		macAddr[1],
		macAddr[2],
		macAddr[3],
		macAddr[4],
		macAddr[5],
		ipAddr.byte1,
		ipAddr.byte2,
		ipAddr.byte3,
		ipAddr.byte4
		));
}


void CMainFrame::OnButtonClick_Device( wxCommandEvent& event )
{
	CDeviceDlg dlg(this);

	// device desc init
	PacketCapturer& mgr = PacketCapturer::instance();
	for (size_t i=0; i< mgr.getNumDevice(); ++i)
	{
		wxString desc = mgr.getDeviceDesc(i).c_str();
		dlg.addDeviceDesc(desc);
	}


	if (dlg.ShowModal())
	{
		int sel = dlg.getSelection();
		mgr.setDeviceIndex(sel);
		UpdateWidgetState();
	}
}

void CMainFrame::OnButtonClick_Start( wxCommandEvent& event )
{
	if (m_capturer == NULL)
	{
		m_capturer = new CaptureThread(this);
		m_capturer->Create();
		m_capturer->Run();
		UpdateWidgetState();
	}
}

void CMainFrame::OnButtonClick_Stop( wxCommandEvent& event )
{
	if (m_capturer != NULL)
	{
		m_capturer->Delete();
		m_capturer = NULL;
		UpdateWidgetState();
	}
}

void CMainFrame::OnButtonClick_Clear( wxCommandEvent& event )
{
	m_listCtrl_pktList->DeleteAllItems();
	PacketCapturer::instance().clearPackets();
}

void CMainFrame::OnButtonClick_ProcessList( wxCommandEvent& event )
{
	PacketCapturer& mgr = PacketCapturer::instance();

	CProcessDlg dlg(this);
	if (dlg.ShowModal())
	{
		mgr.setTraceAddr(dlg.m_Addr.c_str(), dlg.m_Port);
		m_textCtrl_traceProcess->SetLabelText(dlg.m_Name);
	}
}

void CMainFrame::OnButtonClick_traceCancel( wxCommandEvent& event )
{
	PacketCapturer& mgr = PacketCapturer::instance();
	mgr.setTraceAddr(NULL, 0);
	m_textCtrl_traceProcess->SetLabelText(wxString());
}

void CMainFrame::OnCheckBox_skipNodata( wxCommandEvent& event )
{
	PacketCapturer::instance().setNoDataSkip( event.IsChecked() );
}

void CMainFrame::OnCheckBox_sendOnly( wxCommandEvent& event )
{
	PacketCapturer::instance().setSend( event.IsChecked() );
}

void CMainFrame::OnCheckBox_recvOnly( wxCommandEvent& event )
{
	PacketCapturer::instance().setRecv( event.IsChecked() );
}

void CMainFrame::OnListItemSelected( wxListEvent& event )
{
	// text ctrl
	PacketCapturer& mgr = PacketCapturer::instance();
	int index = event.GetIndex();
	wxString strIndex = m_listCtrl_pktList->GetItemText(index, 0);
	long number;
	strIndex.ToLong(&number);

	wxString output;
	char* pBase = (char*)(mgr.getEtherHeader(number));
	char* pChar = pBase;
	char* pLine;

	size_t tlen = mgr.getLength(number);
	size_t ulen = tlen;
	const int nline = (tlen+15)/ 16;

	for (int i=0; i< nline; ++i)
	{
		pLine = pChar;
		output += wxString::Format(wxT("%08lx : "), pChar-pBase);

		ulen = tlen;
		ulen = (ulen>16) ? 16 : ulen;
		tlen -= ulen;

		for (size_t j=0; j< ulen; ++j)
			output += wxString::Format(wxT("%02x "), *(BYTE*)pChar++);

		if (ulen< 16)
			output += wxString::Format(wxT("%*s"), (16- ulen)* 3, " ");

		output.Append(' ', 4);
		pChar = pLine;
		for (size_t j=0; j< ulen; j++, pChar++)
		{
			output += wxString::Format(wxT("%c"), isprint( (unsigned char)*pChar ) ? *pChar : '.');
		}
		output.Append('\r');
		output.Append('\n');
	}
	output.Append('\0');

	m_textCtrl_raw->SetLabel(output);
}

void CMainFrame::OnWorkerEvent( wxThreadEvent& event )
{
	PacketCapturer& mgr = PacketCapturer::instance();
	int idx = event.GetInt();
	int cnt = m_listCtrl_pktList->GetItemCount();
	address srcIp(mgr.getSourceIpAddr(idx));
	address dstIp(mgr.getDestinationIpAddr(idx));

	m_listCtrl_pktList->InsertItem(cnt, wxString::Format("%d", idx));
	m_listCtrl_pktList->SetItem(cnt, 1, wxString::Format("%s", mgr.getTimeStamp(idx).c_str()));
	m_listCtrl_pktList->SetItem(cnt, 2, wxString::Format("%d", mgr.getLength(idx)));
	m_listCtrl_pktList->SetItem(cnt, 3, wxString::Format("%d.%d.%d.%d", srcIp.byte1, srcIp.byte2, srcIp.byte3, srcIp.byte4));
	m_listCtrl_pktList->SetItem(cnt, 4, wxString::Format("%u", mgr.getSourcePort(idx)));
	m_listCtrl_pktList->SetItem(cnt, 5, wxString::Format("%u.%u.%u.%u", dstIp.byte1, dstIp.byte2, dstIp.byte3, dstIp.byte4));
	m_listCtrl_pktList->SetItem(cnt, 6, wxString::Format("%u", mgr.getDestinationPort(idx)));
	m_listCtrl_pktList->SetItemState(cnt, wxLIST_STATE_FOCUSED, wxLIST_STATE_FOCUSED);
	m_listCtrl_pktList->EnsureVisible(cnt);
}

long cvt_textPos(int line, int col)
{
	/**
	line  : 8, 3, [3*16], 4, 16, 1 => total 80
	*/
	return (line * 80) + 8 + 3 + (col * 3);
}

void CMainFrame::OnTreeSelChanged( wxTreeEvent& event )
{
	wxTreeItemId item = event.GetItem();
	Range& range = m_hdrRangeMap[item];
	
	// byte range to text ctrl range
	int beg_line = range.beg / 16;
	int beg_col = (range.beg % 16);

	int end_line = range.end / 16;
	int end_col = (range.end % 16);
	
	using namespace std;
	vector<pair<long, long> >	selections;

	if (beg_line == end_line) 
	{
		selections.push_back(make_pair(cvt_textPos(beg_line, beg_col), cvt_textPos(end_line, end_col)));
	}
	else
	{
		for (int i=beg_line; i<= end_line; ++i)
		{
			if (i == beg_line) // first line
				selections.push_back(make_pair(cvt_textPos(i, beg_col), cvt_textPos(i, 16)));	// [beg, 16]
			else if (i != end_line) // middle line
				selections.push_back(make_pair(cvt_textPos(i, 0), cvt_textPos(i, 16)));			// [0, 16]
			else // last line
				selections.push_back(make_pair(cvt_textPos(i, 0), cvt_textPos(i, end_col)));	// [0, end]
		}
	}

	// clear style
	m_textCtrl_raw->SetStyle(0, m_textCtrl_raw->GetLastPosition(), m_defaultAttr);

	// set style
	for (size_t i=0; i< selections.size(); ++i)
	{
		pair<long, long>& range = selections[i];
		m_textCtrl_raw->SetStyle(range.first, range.second-1, m_selectAttr);
	}
}



/**
*/
IMPLEMENT_APP(Application);

bool Application::OnInit()
{
	CMainFrame*	frame = new CMainFrame();
	frame->Show(true);
	SetTopWindow(frame);

	return true;
}

#include "stdafx.h"
#include "ProcessDlg.h"

#include <map>

#include <Windows.h>
#include <TlHelp32.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <IPHlpApi.h>

#pragma comment (lib, "iphlpapi.lib")
#pragma comment (lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

CProcessDlg::CProcessDlg( wxWindow* parent )
	: ProcessDlg(parent)
	, m_Port(0)
{

}

CProcessDlg::~CProcessDlg( void )
{

}

void CProcessDlg::OnClose( wxCloseEvent& event )
{
	wxDialog::EndModal(0);
}

void CProcessDlg::OnInitDialog( wxInitDialogEvent& event )
{
	// list ctrl
	m_listCtrlPList->AppendColumn(wxT("PID"), 0, 80);
	m_listCtrlPList->AppendColumn(wxT("Name"), 0, 180);
	m_listCtrlPList->AppendColumn(wxT("LocalAddr"), 0, 120);
	m_listCtrlPList->AppendColumn(wxT("LocalPort"), 0, 80);
	m_listCtrlPList->AppendColumn(wxT("RemoteAddr"), 0, 120);
	m_listCtrlPList->AppendColumn(wxT("RemotePort"), 0, 80);


	// process name table
	std::map<int, wxString> pid_nameTlb;
	HANDLE hProcess = NULL;
	PROCESSENTRY32 pe32 = {0, };
	hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcess, &pe32)) 
	{
		do {
			pid_nameTlb[ pe32.th32ProcessID ] = wxString(pe32.szExeFile);
		} while (Process32Next(hProcess, &pe32));
	}
	CloseHandle(hProcess);


	// tcp table
	PMIB_TCPTABLE2 pTcpTable;
	ULONG ulSize = 0;
	DWORD dwRetVal = 0;

	char szLocalAddr[128];
	char szRemoteAddr[128];
	u_short usLocalPort;
	u_short usRemotePort;

	struct in_addr IpAddr;

	pTcpTable = (MIB_TCPTABLE2 *) MALLOC(sizeof (MIB_TCPTABLE2));
	if (pTcpTable == NULL) {
		wxMessageBox("Error allocating memory");
		return;
	}

	ulSize = sizeof (MIB_TCPTABLE);
	// Make an initial call to GetTcpTable2 to get the necessary size into the ulSize variable
	if ((dwRetVal = GetTcpTable2(pTcpTable, &ulSize, TRUE)) == ERROR_INSUFFICIENT_BUFFER) {
		FREE(pTcpTable);
		pTcpTable = (MIB_TCPTABLE2 *) MALLOC(ulSize);
		if (pTcpTable == NULL) {
			wxMessageBox("Error allocating memory");
			return;
		}
	}

	// Make a second call to GetTcpTable2 to get the actual data we require
	if ((dwRetVal = GetTcpTable2(pTcpTable, &ulSize, TRUE)) == NO_ERROR) 
	{
		for (int i = 0; i < (int) pTcpTable->dwNumEntries; i++) 
		{
			if (pTcpTable->table[i].dwLocalAddr == 0) continue;
			if (pTcpTable->table[i].dwRemoteAddr == 0) continue;
			if (pTcpTable->table[i].dwLocalAddr == 0x0100007f) continue;			// 127.0.0.1
			if (pTcpTable->table[i].dwRemoteAddr == 0x0100007f) continue;

			IpAddr.S_un.S_addr = (u_long) pTcpTable->table[i].dwLocalAddr;
			strcpy_s(szLocalAddr, sizeof (szLocalAddr), inet_ntoa(IpAddr));
			usLocalPort = ntohs((u_short)pTcpTable->table[i].dwLocalPort);

			IpAddr.S_un.S_addr = (u_long) pTcpTable->table[i].dwRemoteAddr;
			strcpy_s(szRemoteAddr, sizeof (szRemoteAddr), inet_ntoa(IpAddr));
			usRemotePort = ntohs((u_short)pTcpTable->table[i].dwRemotePort);

			int idx = m_listCtrlPList->GetItemCount();
			m_listCtrlPList->InsertItem(idx, wxString::Format("%d", pTcpTable->table[i].dwOwningPid));
			m_listCtrlPList->SetItem(idx, 1, pid_nameTlb[pTcpTable->table[i].dwOwningPid]);
			m_listCtrlPList->SetItem(idx, 2, wxString::Format("%s", szLocalAddr));
			m_listCtrlPList->SetItem(idx, 3, wxString::Format("%d", usLocalPort));
			m_listCtrlPList->SetItem(idx, 4, wxString::Format("%s", szRemoteAddr));
			m_listCtrlPList->SetItem(idx, 5, wxString::Format("%d", usRemotePort));
		}
	}
}

void CProcessDlg::OnLeftDClick( wxMouseEvent& event )
{
	wxDialog::EndModal(1);
}

void CProcessDlg::OnListItemSelected( wxListEvent& event )
{
	int sel = event.GetIndex();
	wxString name = m_listCtrlPList->GetItemText(sel, 1);
	wxString localAddr = m_listCtrlPList->GetItemText(sel, 2);
	wxString localPort = m_listCtrlPList->GetItemText(sel, 3);
	wxString remoteAddr = m_listCtrlPList->GetItemText(sel, 4);
	wxString remotePort = m_listCtrlPList->GetItemText(sel, 5);

	//wxLogDebug("%s, %s, %s, %s, %s", name, localAddr, localPort, remoteAddr, remotePort);

	long tmp;
	remotePort.ToLong(&tmp);

	m_Addr = remoteAddr;
	m_Port = (int)tmp;
	m_Name = name;
}

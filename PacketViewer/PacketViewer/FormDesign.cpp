///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "FormDesign.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	m_button_device = new wxButton( m_panel3, wxID_ANY, wxT("Device"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button_device, 0, wxALL, 5 );

	m_button_start = new wxButton( m_panel3, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button_start, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_button_stop = new wxButton( m_panel3, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button_stop, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_button_clear = new wxButton( m_panel3, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button_clear, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_button_process = new wxButton( m_panel3, wxID_ANY, wxT("Process List"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button_process, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl_traceProcess = new wxTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_textCtrl_traceProcess, 0, wxALL, 5 );

	m_button_traceCancel = new wxButton( m_panel3, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button_traceCancel, 0, wxALL, 5 );

	m_staticline1 = new wxStaticLine( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer7->Add( m_staticline1, 0, wxEXPAND|wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_checkBox_skipNoData = new wxCheckBox( m_panel3, wxID_ANY, wxT("Header Only"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_checkBox_skipNoData, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_checkBox_sendOnly = new wxCheckBox( m_panel3, wxID_ANY, wxT("Send"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_checkBox_sendOnly, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_checkBox_recvOnly = new wxCheckBox( m_panel3, wxID_ANY, wxT("Receive"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_checkBox_recvOnly, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticline2 = new wxStaticLine( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer7->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );

	m_panel3->SetSizer( bSizer7 );
	m_panel3->Layout();
	bSizer7->Fit( m_panel3 );
	bSizer6->Add( m_panel3, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );

	bSizer1->Add( bSizer6, 0, wxEXPAND, 5 );

	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE|wxSP_PERMIT_UNSPLIT );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter1OnIdle ), NULL, this );

	m_panel1 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	m_listCtrl_pktList = new wxListCtrl( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizer2->Add( m_listCtrl_pktList, 1, wxALL|wxEXPAND, 5 );

	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	m_panel2 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_splitter2 = new wxSplitterWindow( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE );
	m_splitter2->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter2OnIdle ), NULL, this );

	m_panel4 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxVERTICAL );

	m_treeCtrl_hdr = new wxTreeCtrl( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_EXTENDED );
	bSizer71->Add( m_treeCtrl_hdr, 1, wxALL|wxEXPAND, 5 );

	m_panel4->SetSizer( bSizer71 );
	m_panel4->Layout();
	bSizer71->Fit( m_panel4 );
	m_panel5 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	m_textCtrl_raw = new wxTextCtrl( m_panel5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH );
	bSizer8->Add( m_textCtrl_raw, 1, wxEXPAND|wxALL, 5 );

	m_panel5->SetSizer( bSizer8 );
	m_panel5->Layout();
	bSizer8->Fit( m_panel5 );
	m_splitter2->SplitVertically( m_panel4, m_panel5, 202 );
	bSizer3->Add( m_splitter2, 1, wxEXPAND, 5 );

	m_panel2->SetSizer( bSizer3 );
	m_panel2->Layout();
	bSizer3->Fit( m_panel2 );
	m_splitter1->SplitHorizontally( m_panel1, m_panel2, 359 );
	bSizer1->Add( m_splitter1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );

	this->SetSizer( bSizer1 );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	m_button_device->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_Device ), NULL, this );
	m_button_start->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_Start ), NULL, this );
	m_button_stop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_Stop ), NULL, this );
	m_button_clear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_Clear ), NULL, this );
	m_button_process->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_ProcessList ), NULL, this );
	m_button_traceCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_traceCancel ), NULL, this );
	m_checkBox_skipNoData->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::OnCheckBox_skipNodata ), NULL, this );
	m_checkBox_sendOnly->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::OnCheckBox_sendOnly ), NULL, this );
	m_checkBox_recvOnly->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::OnCheckBox_recvOnly ), NULL, this );
	m_listCtrl_pktList->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( MainFrame::OnListItemSelected ), NULL, this );
	m_treeCtrl_hdr->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( MainFrame::OnTreeSelChanged ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	m_button_device->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_Device ), NULL, this );
	m_button_start->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_Start ), NULL, this );
	m_button_stop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_Stop ), NULL, this );
	m_button_clear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_Clear ), NULL, this );
	m_button_process->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_ProcessList ), NULL, this );
	m_button_traceCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonClick_traceCancel ), NULL, this );
	m_checkBox_skipNoData->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::OnCheckBox_skipNodata ), NULL, this );
	m_checkBox_sendOnly->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::OnCheckBox_sendOnly ), NULL, this );
	m_checkBox_recvOnly->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::OnCheckBox_recvOnly ), NULL, this );
	m_listCtrl_pktList->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( MainFrame::OnListItemSelected ), NULL, this );
	m_treeCtrl_hdr->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( MainFrame::OnTreeSelChanged ), NULL, this );

}

ProcessDlg::ProcessDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_listCtrlPList = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizer4->Add( m_listCtrlPList, 1, wxALL|wxEXPAND, 5 );

	this->SetSizer( bSizer4 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ProcessDlg::OnClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ProcessDlg::OnInitDialog ) );
	m_listCtrlPList->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( ProcessDlg::OnLeftDClick ), NULL, this );
	m_listCtrlPList->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ProcessDlg::OnListItemSelected ), NULL, this );
}

ProcessDlg::~ProcessDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ProcessDlg::OnClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ProcessDlg::OnInitDialog ) );
	m_listCtrlPList->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( ProcessDlg::OnLeftDClick ), NULL, this );
	m_listCtrlPList->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ProcessDlg::OnListItemSelected ), NULL, this );

}

DeviceDlg::DeviceDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_listBox_devicelist = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer9->Add( m_listBox_devicelist, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );

	m_button_select = new wxButton( this, wxID_ANY, wxT("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_button_select, 1, wxALL, 5 );

	m_button_cancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_button_cancel, 1, wxALL, 5 );

	bSizer9->Add( bSizer10, 0, wxEXPAND|wxALIGN_RIGHT, 5 );

	this->SetSizer( bSizer9 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_listBox_devicelist->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( DeviceDlg::OnListBox ), NULL, this );
	m_listBox_devicelist->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( DeviceDlg::OnListBoxDClick ), NULL, this );
	m_button_select->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeviceDlg::OnButtonClick_Select ), NULL, this );
	m_button_cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeviceDlg::OnButtonClick_Cancel ), NULL, this );
}

DeviceDlg::~DeviceDlg()
{
	// Disconnect Events
	m_listBox_devicelist->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( DeviceDlg::OnListBox ), NULL, this );
	m_listBox_devicelist->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( DeviceDlg::OnListBoxDClick ), NULL, this );
	m_button_select->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeviceDlg::OnButtonClick_Select ), NULL, this );
	m_button_cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeviceDlg::OnButtonClick_Cancel ), NULL, this );

}

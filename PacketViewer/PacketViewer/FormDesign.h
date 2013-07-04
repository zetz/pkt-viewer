///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FormDesign__
#define __FormDesign__

#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/listbox.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
private:

protected:
	wxPanel* m_panel3;
	wxButton* m_button_device;
	wxButton* m_button_start;
	wxButton* m_button_stop;
	wxButton* m_button_clear;
	wxButton* m_button_process;
	wxTextCtrl* m_textCtrl_traceProcess;
	wxButton* m_button_traceCancel;
	wxStaticLine* m_staticline1;
	wxCheckBox* m_checkBox_skipNoData;
	wxCheckBox* m_checkBox_sendOnly;
	wxCheckBox* m_checkBox_recvOnly;
	wxStaticLine* m_staticline2;
	wxSplitterWindow* m_splitter1;
	wxPanel* m_panel1;
	wxListCtrl* m_listCtrl_pktList;
	wxPanel* m_panel2;
	wxSplitterWindow* m_splitter2;
	wxPanel* m_panel4;
	wxTreeCtrl* m_treeCtrl_hdr;
	wxPanel* m_panel5;
	wxTextCtrl* m_textCtrl_raw;
	wxStatusBar* m_statusBar;

	// Virtual event handlers, overide them in your derived class
	virtual void OnButtonClick_Device( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButtonClick_Start( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButtonClick_Stop( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButtonClick_Clear( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButtonClick_ProcessList( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButtonClick_traceCancel( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnCheckBox_skipNodata( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnCheckBox_sendOnly( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnCheckBox_recvOnly( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnListItemSelected( wxListEvent& event ) { event.Skip(); }
	virtual void OnTreeSelChanged( wxTreeEvent& event ) { event.Skip(); }


public:

	MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PacketViewer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 940,555 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
	~MainFrame();

	void m_splitter1OnIdle( wxIdleEvent& )
	{
		m_splitter1->SetSashPosition( 359 );
		m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter1OnIdle ), NULL, this );
	}

	void m_splitter2OnIdle( wxIdleEvent& )
	{
		m_splitter2->SetSashPosition( 202 );
		m_splitter2->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter2OnIdle ), NULL, this );
	}

};

///////////////////////////////////////////////////////////////////////////////
/// Class ProcessDlg
///////////////////////////////////////////////////////////////////////////////
class ProcessDlg : public wxDialog 
{
private:

protected:
	wxListCtrl* m_listCtrlPList;

	// Virtual event handlers, overide them in your derived class
	virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
	virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
	virtual void OnLeftDClick( wxMouseEvent& event ) { event.Skip(); }
	virtual void OnListItemSelected( wxListEvent& event ) { event.Skip(); }


public:

	ProcessDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Process List"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 740,340 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
	~ProcessDlg();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DeviceDlg
///////////////////////////////////////////////////////////////////////////////
class DeviceDlg : public wxDialog 
{
private:

protected:
	wxListBox* m_listBox_devicelist;
	wxButton* m_button_select;
	wxButton* m_button_cancel;

	// Virtual event handlers, overide them in your derived class
	virtual void OnListBox( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnListBoxDClick( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButtonClick_Select( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButtonClick_Cancel( wxCommandEvent& event ) { event.Skip(); }


public:

	DeviceDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 486,313 ), long style = wxDEFAULT_DIALOG_STYLE );
	~DeviceDlg();

};

#endif //__FormDesign__

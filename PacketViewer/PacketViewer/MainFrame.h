#pragma once

#include "FormDesign.h"

class CaptureThread;

class CMainFrame : public MainFrame
{
public:
	CMainFrame(void);
	virtual ~CMainFrame(void);

	void		InitWidgets();
	void		UpdateWidgetState();


	virtual void OnButtonClick_Device( wxCommandEvent& event );
	virtual void OnButtonClick_Start( wxCommandEvent& event );
	virtual void OnButtonClick_Stop( wxCommandEvent& event );
	virtual void OnButtonClick_Clear( wxCommandEvent& event );
	virtual void OnButtonClick_ProcessList( wxCommandEvent& event );
	virtual void OnButtonClick_traceCancel( wxCommandEvent& event );
	virtual void OnCheckBox_skipNodata( wxCommandEvent& event );
	virtual void OnCheckBox_sendOnly( wxCommandEvent& event );
	virtual void OnCheckBox_recvOnly( wxCommandEvent& event );
	virtual void OnListItemSelected( wxListEvent& event );
	
	virtual void OnWorkerEvent(wxThreadEvent& event);

	virtual void OnTreeSelChanged( wxTreeEvent& event );
	
private:
	CaptureThread*		m_capturer;
	wxTextAttr			m_selectAttr;
	wxTextAttr			m_defaultAttr;
	
	struct Range
	{
		Range() : beg(0), end(0) {};
		Range(unsigned long start, unsigned long len) : beg(start), end(start+len) {}
		unsigned long beg;
		unsigned long end;
	};
	WX_DECLARE_VOIDPTR_HASH_MAP(Range, ItemIdHdrRangeMap);

	ItemIdHdrRangeMap	m_hdrRangeMap;
};




class Application : public wxApp
{
public:
	virtual bool OnInit();
};


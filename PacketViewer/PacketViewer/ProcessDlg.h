#pragma once

#include "FormDesign.h"

class CProcessDlg : public ProcessDlg
{
public:
	CProcessDlg(wxWindow* parent);
	~CProcessDlg(void);

	virtual void OnClose( wxCloseEvent& event );
	virtual void OnInitDialog( wxInitDialogEvent& event );
	virtual void OnLeftDClick( wxMouseEvent& event );
	virtual void OnListItemSelected( wxListEvent& event );

	wxString		m_Name;
	wxString		m_Addr;
	int				m_Port;	
};


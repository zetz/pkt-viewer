#pragma once

#include "FormDesign.h"

class CDeviceDlg : public DeviceDlg
{
public:
	CDeviceDlg(wxWindow* parent);
	~CDeviceDlg(void);

	virtual void OnListBox( wxCommandEvent& event );
	virtual void OnListBoxDClick( wxCommandEvent& event );
	virtual void OnButtonClick_Select( wxCommandEvent& event );
	virtual void OnButtonClick_Cancel( wxCommandEvent& event );


	void	addDeviceDesc(const wxString& name);
	int		getSelection() const;

	int		m_select;
};


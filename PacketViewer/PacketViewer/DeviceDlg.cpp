#include "stdafx.h"
#include "DeviceDlg.h"


CDeviceDlg::CDeviceDlg(wxWindow* parent)
	: DeviceDlg(parent)
	, m_select(0)
{

}


CDeviceDlg::~CDeviceDlg(void)
{
}

void CDeviceDlg::OnListBox( wxCommandEvent& event )
{
	int sel = m_listBox_devicelist->GetSelection();
	m_select = sel;
}

void CDeviceDlg::OnListBoxDClick( wxCommandEvent& event )
{
	int sel = m_listBox_devicelist->GetSelection();
	m_select = sel;
	wxDialog::EndModal(1);
}

void CDeviceDlg::OnButtonClick_Select( wxCommandEvent& event )
{
	wxDialog::EndModal(1);
}

void CDeviceDlg::OnButtonClick_Cancel( wxCommandEvent& event )
{
	wxDialog::EndModal(0);
}

void CDeviceDlg::addDeviceDesc( const wxString& name )
{
	m_listBox_devicelist->AppendString(name);
}

int CDeviceDlg::getSelection() const
{
	return m_select;
}

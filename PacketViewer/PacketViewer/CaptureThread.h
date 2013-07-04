#pragma once
#include <wx/wx.h>


class CMainFrame;

class CaptureThread : public wxThread
{
public:
	CaptureThread(CMainFrame* frame);
	~CaptureThread(void);

	virtual ExitCode Entry();

	CMainFrame*		m_owner;
};


#include "stdafx.h"
#include "CaptureThread.h"

#include "PacketCapturer.h"
#include "MainFrame.h"

CaptureThread::CaptureThread(CMainFrame* frame)
	: m_owner(frame)
{
}

CaptureThread::~CaptureThread(void)
{
}

wxThread::ExitCode CaptureThread::Entry()
{
	PacketCapturer& mgr = PacketCapturer::instance();

	mgr.handle_open();
	while (!TestDestroy())
	{
		int idx = mgr.capture();
		if (idx < 0) 
			continue;

		wxThreadEvent evt(wxEVT_THREAD, wxID_ANY);
		evt.SetInt(idx);

		wxQueueEvent( m_owner, evt.Clone() );
	}

	mgr.handle_close();
	return ExitCode(1);
}

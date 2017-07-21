/**
 * main program for timer
 */
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/display.h>
#include "SettingsFrame.hpp"

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	SettingsFrame* settingsFrame = new SettingsFrame("Timer Settings");
	settingsFrame->Show();
	return true;
}


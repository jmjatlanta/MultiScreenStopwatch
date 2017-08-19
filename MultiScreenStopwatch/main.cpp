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

/**
 * The basic class
 */
class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};


wxIMPLEMENT_APP(MyApp);


/***
 * This is what runs when the app starts up...
 */
bool MyApp::OnInit()
{
	wxPoint* dialogPoint = SettingsFrame::GetDefaultLocation(1);
	SettingsFrame* settingsFrame = new SettingsFrame("Timer Settings", dialogPoint);
	settingsFrame->Show();
	return true;
}


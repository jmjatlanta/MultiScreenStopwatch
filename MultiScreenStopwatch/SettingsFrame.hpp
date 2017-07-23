//
//  SettingsPanel.hpp
//  TestWxWidgets
//
//  Created by John Jones on 6/11/17.
//  Copyright © 2017 JMJAtlanta. All rights reserved.
//

#pragma once

#include <wx/wx.h>
#include <chrono>
#include "TimerFrame.hpp"
#include "SecondTimer.hpp"
#include "TextControl.hpp"

class SettingsFrame : public wxFrame
{
public:
	SettingsFrame(const wxString& window_title);
	~SettingsFrame();
	void OnButtonStart(wxCommandEvent& event);
	void OnButtonStop(wxCommandEvent& event);
	void OnButtonHide(wxCommandEvent& event);
	void OnButtonBackgroundColor(wxCommandEvent& event);
	void OnButtonForegroundColorNormal(wxCommandEvent& event);
	void OnButtonForegroundColorWarning(wxCommandEvent& event);
	void OnButtonForegroundColorError(wxCommandEvent& event);
	void OnColorButton(wxTextCtrl* textControl);
	DECLARE_EVENT_TABLE()
private:
	/////////////
	// private members
	/////////////
	// other display's frame
	TimerFrame* currentTimerFrame;
	// the timer
	SecondTimer *secondTimer;
	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point warningTime;
	std::chrono::system_clock::time_point errorTime;
	wxColour *normalColor;
	wxColour *warningColor;
	wxColour *errorColor;
private:
	////////////
	// Private methods
	////////////
	// put the TimerFrame on a particular display
	TimerFrame* createTimerOnDisplay(int displayNumber);
	// turn string of mm:ss into duration
	std::chrono::seconds getDuration(std::string input);
	// respond to a timer event
	void OnTimer(wxTimerEvent &event);
private:
	//////////
	// UI pieces
	//////////
	// box and frame
	wxPanel *panel;
	wxBoxSizer *horizontal_box;
	wxFlexGridSizer *flex_grid_sizer;
	// static text
	wxStaticText *textScreenNumber;
	wxStaticText *textTimerMinutes;
	wxStaticText *textTimerDisplaying;
	wxStaticText *textBackgroundColor;
	wxStaticText *textForegroundColorNormal;
	wxStaticText *textForegroundColorWarning;
	wxStaticText *textWarningTime;
	wxStaticText *textForegroundColorError;
	// controls
	wxTextCtrl *inputScreenNumber;
	wxTextCtrl *inputTimerMinutes;
	wxTextCtrl *inputBackgroundColor;
	wxButton *buttonBackgroundColor;
	wxTextCtrl *inputForegroundColorNormal;
	wxButton *buttonForegroundColorNormal;
	wxTextCtrl *inputForegroundColorWarning;
	wxButton *buttonForegroundColorWarning;
	wxTextCtrl *inputWarningTime;
	wxTextCtrl *inputForegroundColorError;
	wxButton *buttonForegroundColorError;
	wxButton *buttonStart;
	wxButton *buttonStop;
	wxButton *buttonHide;
};

enum
{
	BUTTON_Start = wxID_HIGHEST + 1,
	BUTTON_Stop = BUTTON_Start + 1,
	BUTTON_Hide = BUTTON_Start + 2,
	BUTTON_BackgroundColor = BUTTON_Start + 3,
	BUTTON_ForegroundColorNormal = BUTTON_Start + 4,
	BUTTON_ForegroundColorWarning = BUTTON_Start + 5,
	BUTTON_ForegroundColorError = BUTTON_Start + 6
};




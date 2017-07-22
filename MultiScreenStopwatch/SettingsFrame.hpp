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
	TextControl *inputBackgroundColor;
	TextControl *inputForegroundColorNormal;
	TextControl *inputForegroundColorWarning;
	wxTextCtrl *inputWarningTime;
	TextControl *inputForegroundColorError;
	wxButton *buttonStart;
	wxButton *buttonStop;
	wxButton *buttonHide;
};

enum
{
	BUTTON_Start = wxID_HIGHEST + 1,
	BUTTON_Stop = BUTTON_Start + 1,
	BUTTON_Hide = BUTTON_Stop + 1
};




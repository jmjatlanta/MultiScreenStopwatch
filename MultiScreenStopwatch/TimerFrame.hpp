//
//  TimerFrame.hpp
//  TestWxWidgets
//
//  Created by John Jones on 6/12/17.
//  Copyright © 2017 JMJAtlanta. All rights reserved.
//

#ifndef TimerFrame_hpp
#define TimerFrame_hpp

#include <stdio.h>
#include <chrono>

#include <wx/wx.h>
#include "SecondTimer.hpp"

class TimerFrame : public wxDialog
{
public:
	TimerFrame(wxWindow *parent, SecondTimer* secondTimer, int displayNumber);
	~TimerFrame();
public:
	void SetTimer(std::chrono::seconds seconds);
	void OnTimer(wxTimerEvent& event);
	bool SetForegroundColour(const wxColour &colour);
	void SetDisplayTime(bool displaingTime);
	
private:
	int getOptimalFontSize(std::string str, int screenWidth);

private:
	wxPanel *panel;
	wxBoxSizer *horizontal_box;
	wxFlexGridSizer *flex_grid_sizer;
	wxStaticText *textTimer;
	wxFont *alarmClockFont;
	wxSize alarmClockFontSize;
	wxFont *clockFont;
	wxSize clockFontSize;
	int minutes;
	bool stopping;
	std::chrono::time_point<std::chrono::system_clock> startTime;
	SecondTimer* second_timer;
	bool displayingTime;
private:
};


#endif /* TimerFrame_hpp */

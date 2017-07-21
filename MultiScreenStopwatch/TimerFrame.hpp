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
	TimerFrame(wxWindow *parent, SecondTimer* secondTimer);
	~TimerFrame();
public:
	void SetTimer(int minutes);
	void OnTimer(wxTimerEvent& event);
	bool SetForegroundColour(const wxColour &colour);

private:
	wxPanel *panel;
	wxBoxSizer *horizontal_box;
	wxFlexGridSizer *flex_grid_sizer;
	wxStaticText *textTimer;
	wxFont *alarmClockFont;
	int minutes;
	bool stopping;
	std::chrono::time_point<std::chrono::system_clock> startTime;
	SecondTimer* second_timer;
private:
};


#endif /* TimerFrame_hpp */

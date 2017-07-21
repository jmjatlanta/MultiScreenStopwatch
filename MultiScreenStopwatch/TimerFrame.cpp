//
//  TimerFrame.cpp
//  TestWxWidgets
//
//  Created by John Jones on 6/12/17.
//  Copyright © 2017 JMJAtlanta. All rights reserved.
//
#include "TimerFrame.hpp"

TimerFrame::TimerFrame(wxWindow *parent, SecondTimer* secondTimer)
	: wxDialog(parent, -1, _T("Timer Frame"), wxPoint(-1, -1), wxSize(220, 220), wxRESIZE_BORDER)
{
	minutes = 0;
	
	this->second_timer = secondTimer;
	this->second_timer->Bind(wxEVT_TIMER, &TimerFrame::OnTimer, this);
	
	// create font
	alarmClockFont = new wxFont(512, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "alarm clock", wxFONTENCODING_DEFAULT);
	// create a panel
	panel = new wxPanel(this, -1);
	
	horizontal_box = new wxBoxSizer(wxHORIZONTAL);
	
	flex_grid_sizer = new wxFlexGridSizer(1,1,9,25);
	
	// add text
	textTimer = new wxStaticText(panel, -1, wxT("00:00"));
	textTimer->SetFont(*alarmClockFont);
	
	// put everything into the wxFlexGridSizer
	flex_grid_sizer->Add(textTimer);
	
	// If we're going to grow vertically, grow the review text area
	flex_grid_sizer->AddGrowableRow(0, 1); // row 0, proportion 1
	// if we're going to grow horizontally, grow the data input column
	flex_grid_sizer->AddGrowableCol(0, 1); // column 0, proportion 1
	
	// put it all together
	horizontal_box->Add(flex_grid_sizer, 1, wxALL | wxEXPAND, 150);
	panel->SetSizer(horizontal_box);
	Center();
}

TimerFrame::~TimerFrame()
{
	textTimer->Destroy();
	panel->Destroy();
	delete alarmClockFont;
}

void TimerFrame::SetTimer(int minutes)
{
	textTimer->SetLabel(SecondTimer::ToString(minutes));
}

void TimerFrame::OnTimer(wxTimerEvent& event)
{
	textTimer->SetLabel(SecondTimer::ToString(second_timer->SecondsSinceStart()));
	event.Skip();
}

bool TimerFrame::SetForegroundColour(const wxColour &colour)
{
	wxDialog::SetForegroundColour(colour);
	return textTimer->SetForegroundColour(colour);
}

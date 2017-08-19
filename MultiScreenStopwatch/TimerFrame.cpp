//
//  TimerFrame.cpp
//  TestWxWidgets
//
//  Created by John Jones on 6/12/17.
//  Copyright © 2017 JMJAtlanta. All rights reserved.
//
#include "TimerFrame.hpp"
#include <wx/display.h>

TimerFrame::TimerFrame(wxWindow *parent, SecondTimer* secondTimer, int displayNumber)
	: wxDialog(parent, -1, _T("Timer Frame"), wxPoint(-1, -1), wxSize(220, 220), wxRESIZE_BORDER), displayingTime(false)
{
	minutes = 0;
	
	this->second_timer = secondTimer;
	this->second_timer->Bind(wxEVT_TIMER, &TimerFrame::OnTimer, this);

	// find the correct display and get its dimentions
	wxDisplay *chosenDisplay = new wxDisplay(displayNumber);
	wxRect* chosenGeometry = new wxRect(chosenDisplay->GetGeometry());
	Move(chosenGeometry->x, chosenGeometry->y);
	SetSize(chosenGeometry->width, chosenGeometry->height);

	// adjust font sizes
	int alarmClockFontSize = getOptimalFontSize(" 00:00", chosenGeometry->GetWidth());
	int clockFontSize = getOptimalFontSize(" 00:00:00", chosenGeometry->GetWidth());
	
	// no longer need these objects
	delete chosenGeometry;
	delete chosenDisplay;
	
	// create font
	alarmClockFont = new wxFont(alarmClockFontSize, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "alarm clocks", wxFONTENCODING_DEFAULT);
	clockFont = new wxFont(clockFontSize, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "alarm clock", wxFONTENCODING_DEFAULT);
	
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

	// now put it on the display
	Show();
}

TimerFrame::~TimerFrame()
{
	textTimer->Destroy();
	panel->Destroy();
	delete alarmClockFont;
	delete clockFont;
}

/***
 * Based on the passed in string, determine what font size is smaller than the scren width, starting at 512pt
 * @param str the string
 * @param screenWidth the width of the screen
 * @returns the font size that will not overrun the screen
 */
int TimerFrame::getOptimalFontSize(std::string str, int screenWidth) {
	wxCoord w;
	wxCoord h;
	int currSize = 513;
	wxFont* font = NULL;
	do {
		currSize--;
		font = new wxFont(currSize, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "alarm clock", wxFONTENCODING_DEFAULT);
		GetTextExtent(str, &w, &h, NULL, NULL, font);
		delete font;
	} while (w >= screenWidth);
	return currSize;
}

void TimerFrame::SetTimer(std::chrono::seconds seconds)
{
	textTimer->SetLabel(SecondTimer::ToString(seconds));
}

void TimerFrame::SetDisplayTime(bool displayTimer) {
	this->displayingTime = displayTimer;
	if (displayingTime) {
		textTimer->SetFont(*clockFont);
	} else {
		textTimer->SetFont(*alarmClockFont);
	}
}

void TimerFrame::OnTimer(wxTimerEvent& event)
{
	if (displayingTime) {
		textTimer->SetLabel(SecondTimer::ToString());
	} else {
		textTimer->SetLabel(SecondTimer::ToString(second_timer->SecondsSinceStart()));
	}
	event.Skip();
}

bool TimerFrame::SetForegroundColour(const wxColour &colour)
{
	wxDialog::SetForegroundColour(colour);
	return textTimer->SetForegroundColour(colour);
}

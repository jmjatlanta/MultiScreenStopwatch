//
//  SettingsPanel.cpp
//  TestWxWidgets
//
//  Created by John Jones on 6/11/17.
//  Copyright © 2017 JMJAtlanta. All rights reserved.
//

#include "SettingsFrame.hpp"
#include <sstream>
#include <wx/event.h>
#include <wx/display.h>
#include <wx/fontdlg.h>
#include <wx/generic/fontdlgg.h>

SettingsFrame::SettingsFrame(const wxString& window_title)
	: wxFrame(NULL, -1, window_title, wxPoint(-1, -1), wxSize(540, 540))
{
	currentTimerFrame = nullptr;
	normalColor = nullptr;
	warningColor = nullptr;
	errorColor = nullptr;
	secondTimer = new SecondTimer();
	secondTimer->Bind(wxEVT_TIMER, &SettingsFrame::OnTimer, this);
	
	// create a panel that has a BoxSizer that has a FlexGridSizer
	panel = new wxPanel(this, -1);
	horizontal_box = new wxBoxSizer(wxHORIZONTAL);
	flex_grid_sizer = new wxFlexGridSizer(10,2,25,25);
	
	// labels
	textScreenNumber = new wxStaticText(panel, -1, wxT("Screen Number"));
	textTimerMinutes = new wxStaticText(panel, -1, wxT("Timer Minutes"));
	textBackgroundColor = new wxStaticText(panel, -1, wxT("Background Color"));
	textForegroundColorNormal = new wxStaticText(panel, -1, wxT("Foreground Color Normal"));
	textForegroundColorWarning = new wxStaticText(panel, -1, wxT("Foreground Color Warning"));
	textWarningTime = new wxStaticText(panel, -1, wxT("Time left before warning"));
	textForegroundColorError = new wxStaticText(panel, -1, wxT("Foreground Color Error"));
	textTimerDisplaying = new wxStaticText(panel, -1, SecondTimer::ToString(0));
	// text controls
	inputScreenNumber = new wxTextCtrl(panel, -1);
	inputScreenNumber->SetValue(_T("2"));
	inputTimerMinutes = new wxTextCtrl(panel, -1);
	inputTimerMinutes->SetValue(_T("1"));
	inputBackgroundColor = new TextControl(panel);
	inputBackgroundColor->SetValue("rgb(127, 127, 127)");
	inputForegroundColorNormal = new TextControl(panel);
	inputForegroundColorNormal->SetValue("black");
	inputForegroundColorWarning = new TextControl(panel);
	inputForegroundColorWarning->SetValue("rgb(204,208,15)");
	inputWarningTime = new wxTextCtrl(panel, -1);
	inputWarningTime->SetValue("0:30");
	inputForegroundColorError = new TextControl(panel);
	inputForegroundColorError->SetValue("rgb(175,0,20)");
	// buttons
	buttonStart = new wxButton(panel, BUTTON_Start, _T("Start"));
	buttonStop  = new wxButton(panel, BUTTON_Stop,  _T("Stop"));
	buttonHide  = new wxButton(panel, BUTTON_Hide, _T("Hide"));
	
	// put everything into the wxFlexGridSizer
	flex_grid_sizer->Add(textScreenNumber);
	flex_grid_sizer->Add(inputScreenNumber, 1, wxEXPAND);
	flex_grid_sizer->Add(textTimerMinutes);
	flex_grid_sizer->Add(inputTimerMinutes, 1, wxEXPAND);
	flex_grid_sizer->Add(textBackgroundColor);
	flex_grid_sizer->Add(inputBackgroundColor, 1, wxEXPAND);
	flex_grid_sizer->Add(textForegroundColorNormal);
	flex_grid_sizer->Add(inputForegroundColorNormal, 1, wxEXPAND);
	flex_grid_sizer->Add(textForegroundColorWarning);
	flex_grid_sizer->Add(inputForegroundColorWarning, 1, wxEXPAND);
	flex_grid_sizer->Add(textWarningTime);
	flex_grid_sizer->Add(inputWarningTime, 1, wxEXPAND);
	flex_grid_sizer->Add(textForegroundColorError);
	flex_grid_sizer->Add(inputForegroundColorError, 1, wxEXPAND);
	flex_grid_sizer->Add(buttonStart);
	flex_grid_sizer->Add(buttonStop, 1, wxEXPAND);
	flex_grid_sizer->Add(buttonHide);
	flex_grid_sizer->AddStretchSpacer();
	flex_grid_sizer->Add(textTimerDisplaying);
	flex_grid_sizer->AddStretchSpacer();
	
	// If we're going to grow vertically, grow the review text area
	flex_grid_sizer->AddGrowableRow(9, 1); // row 3, proportion 1
	// if we're going to grow horizontally, grow the data input column
	flex_grid_sizer->AddGrowableCol(1, 1); // column 1, proportion 1
	
	// put it all together
	horizontal_box->Add(flex_grid_sizer, 1, wxALL | wxEXPAND, 15);
	panel->SetSizer(horizontal_box);
	Center();
}

SettingsFrame::~SettingsFrame()
{
	// labels
	textScreenNumber->Destroy();
	textTimerMinutes->Destroy();
	textBackgroundColor->Destroy();
	textForegroundColorNormal->Destroy();
	textForegroundColorWarning->Destroy();
	textWarningTime->Destroy();
	textForegroundColorError->Destroy();
	textTimerDisplaying->Destroy();
	// text controls
	inputScreenNumber->Destroy();
	inputTimerMinutes->Destroy();
	inputBackgroundColor->Destroy();
	inputForegroundColorNormal->Destroy();
	inputForegroundColorWarning->Destroy();
	inputForegroundColorError->Destroy();
	// buttons
	buttonStart->Destroy();
	buttonStop->Destroy();
	//delete flex_grid_sizer;
	//delete horizontal_box;
	panel->Destroy();
	delete currentTimerFrame;
	delete secondTimer;
}

BEGIN_EVENT_TABLE(SettingsFrame, wxFrame)
EVT_BUTTON (BUTTON_Start, SettingsFrame::OnButtonStart)
EVT_BUTTON (BUTTON_Stop, SettingsFrame::OnButtonStop)
EVT_BUTTON (BUTTON_Hide, SettingsFrame::OnButtonHide)
END_EVENT_TABLE()

void SettingsFrame::OnButtonStart(wxCommandEvent &event)
{
	// validate the information
	long displayNumber = -1;
	
	wxString strValue = inputScreenNumber->GetValue();
	if (!strValue.ToLong(&displayNumber) || displayNumber < 0)
		return;
	int numDisplays = wxDisplay::GetCount();
	if (displayNumber > numDisplays)
		return;
	
	strValue = inputTimerMinutes->GetValue();
	long timerMinutes;
	if (!strValue.ToLong(&timerMinutes))
		return;
	
	
	// we can no longer set the display number
	inputScreenNumber->SetEditable(false);

	// start window (if it is not already there)
	if (currentTimerFrame == nullptr)
		currentTimerFrame = createTimerOnDisplay((int)displayNumber);

	// give me back focus
	this->SetFocus();
	
	// now set time
	currentTimerFrame->SetTimer((int)timerMinutes);
	// set background color
	strValue = inputBackgroundColor->GetValue();
	currentTimerFrame->SetBackgroundColour(wxColour(strValue));
	strValue = inputForegroundColorNormal->GetValue();
	normalColor = new wxColour(strValue);
	currentTimerFrame->SetForegroundColour(*normalColor);
	strValue = inputForegroundColorWarning->GetValue();
	warningColor = new wxColour(strValue);
	strValue = inputForegroundColorError->GetValue();
	errorColor = new wxColour(strValue);
	// start timer
	secondTimer->StartTimer();
	// do the calculations
	this->startTime = secondTimer->GetStartTime();
	this->errorTime = startTime + std::chrono::minutes(timerMinutes);
	strValue = inputWarningTime->GetValue();
	this->warningTime = this->errorTime - getDuration(strValue.ToStdString());
}

void SettingsFrame::OnButtonStop(wxCommandEvent &event)
{
	secondTimer->StopTimer();
}

void SettingsFrame::OnButtonHide(wxCommandEvent &event)
{
	secondTimer->StopTimer();
	currentTimerFrame->Hide();
	delete currentTimerFrame;
	currentTimerFrame = nullptr;
	inputScreenNumber->SetEditable(true);
}

TimerFrame* SettingsFrame::createTimerOnDisplay(int displayNumber)
{
	wxDisplay *chosenDisplay = new wxDisplay((int)displayNumber);
	wxRect* chosenGeometry = new wxRect(chosenDisplay->GetGeometry());
	
	TimerFrame *timerFrame = new TimerFrame(this, secondTimer);
	timerFrame->Move(chosenGeometry->x, chosenGeometry->y);
	timerFrame->SetSize(chosenGeometry->width, chosenGeometry->height);
	timerFrame->Show();
	
	delete chosenGeometry;
	delete chosenDisplay;
	
	return timerFrame;
}

void SettingsFrame::OnTimer(wxTimerEvent &Event)
{
	if (currentTimerFrame != nullptr) {
		// see if we need to change the color
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		wxColour *currentColor = normalColor;
		if (now >= warningTime) {
			if (now >= errorTime)
				currentColor = errorColor;
			else
				currentColor = warningColor;
			currentTimerFrame->SetForegroundColour(*currentColor);
		}
	}
	textTimerDisplaying->SetLabel(SecondTimer::ToString(secondTimer->SecondsSinceStart()));
	Event.Skip();
}

std::chrono::seconds SettingsFrame::getDuration(std::string input)
{
	std::stringstream ss(input);
	std::string minutesString;
	std::string secondsString;
	int minutes = 0, seconds = 0;
	
	if (!std::getline(ss, minutesString, ':'))
		minutesString = "0";
	if (!std::getline(ss, secondsString, ':'))
		secondsString = "0";

	minutes = atoi(minutesString.c_str());
	seconds = atoi(secondsString.c_str());
	
	return std::chrono::seconds(std::chrono::minutes(minutes) + std::chrono::seconds(seconds));
}

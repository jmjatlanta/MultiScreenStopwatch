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
#include <wx/colordlg.h>
#include "IdentifierDialog.hpp"

/**
 * Constructor
 */
SettingsFrame::SettingsFrame(const wxString& window_title, wxPoint* start_point)
: wxFrame(NULL, -1, window_title, *start_point, wxSize(540, 540)), displayingTime(false), startPoint(start_point)
{
	currentTimerFrame = nullptr;
	normalColor = nullptr;
	warningColor = nullptr;
	errorColor = nullptr;
	identifierDialogs = nullptr;
	numIdentifierDialogs = 0;
	secondTimer = new SecondTimer();
	secondTimer->Bind(wxEVT_TIMER, &SettingsFrame::OnTimer, this);
	
	// create a panel that has a BoxSizer that has a FlexGridSizer
	panel = new wxPanel(this, -1);
	horizontal_box = new wxBoxSizer(wxHORIZONTAL);
	flex_grid_sizer = new wxFlexGridSizer(10,3,25,25);
	
	// labels
	textScreenNumber = new wxStaticText(panel, -1, wxT("Screen Number"));
	textTimerMinutes = new wxStaticText(panel, -1, wxT("Timer MM:SS"));
	textBackgroundColor = new wxStaticText(panel, -1, wxT("Background Color"));
	textForegroundColorNormal = new wxStaticText(panel, -1, wxT("Foreground Color Normal"));
	textForegroundColorWarning = new wxStaticText(panel, -1, wxT("Foreground Color Warning"));
	textWarningTime = new wxStaticText(panel, -1, wxT("Time left before warning"));
	textForegroundColorError = new wxStaticText(panel, -1, wxT("Foreground Color Error"));
	textTimerDisplaying = new wxStaticText(panel, -1, SecondTimer::ToString(0));
	// text controls
	inputScreenNumber = new wxTextCtrl(panel, -1);
	inputScreenNumber->SetValue(_T("0"));
	inputTimerMinutes = new wxTextCtrl(panel, -1);
	inputTimerMinutes->SetValue(_T("12:00"));
	inputWarningTime = new wxTextCtrl(panel, -1);
	inputWarningTime->SetValue("1:00");
	inputBackgroundColor = new wxTextCtrl(panel, -1);
	inputBackgroundColor->SetValue("black");
	SetControlColors(inputBackgroundColor);
	inputForegroundColorNormal = new wxTextCtrl(panel, -1);
	inputForegroundColorNormal->SetValue("rgb(156, 156, 156)");
	SetControlColors(inputForegroundColorNormal);
	inputForegroundColorWarning = new wxTextCtrl(panel, -1);
	inputForegroundColorWarning->SetValue("rgb(204, 208, 15)");
	SetControlColors(inputForegroundColorWarning);
	inputForegroundColorError = new wxTextCtrl(panel, -1);
	inputForegroundColorError->SetValue("rgb(175, 0, 20)");
	SetControlColors(inputForegroundColorError);
	// buttons
	buttonStart = new wxButton(panel, BUTTON_Start, _T("Start"));
	buttonStop  = new wxButton(panel, BUTTON_Stop,  _T("Stop"));
	buttonHide  = new wxButton(panel, BUTTON_Hide, _T("Hide"));
	buttonDisplayIdentifier = new wxButton(panel, BUTTON_Display_Identifier, _T("Show Display Identifiers"));
	buttonBackgroundColor = new wxButton(panel, BUTTON_BackgroundColor, _T("C"));
	buttonForegroundColorNormal = new wxButton(panel, BUTTON_ForegroundColorNormal, _T("C"));
	buttonForegroundColorWarning = new wxButton(panel, BUTTON_ForegroundColorWarning, _T("C"));
	buttonForegroundColorError = new wxButton(panel, BUTTON_ForegroundColorError, _T("C"));
	
	// put everything into the wxFlexGridSizer
	// row 0
	flex_grid_sizer->Add(textScreenNumber);
	flex_grid_sizer->Add(inputScreenNumber, 1, wxEXPAND);
	flex_grid_sizer->AddSpacer(0);
	// row 1
	flex_grid_sizer->Add(textTimerMinutes);
	flex_grid_sizer->Add(inputTimerMinutes, 1, wxEXPAND);
	flex_grid_sizer->AddSpacer(0);
	// row 2
	flex_grid_sizer->Add(textWarningTime);
	flex_grid_sizer->Add(inputWarningTime, 1, wxEXPAND);
	flex_grid_sizer->AddSpacer(0);
	// row 3
	flex_grid_sizer->Add(textBackgroundColor);
	flex_grid_sizer->Add(inputBackgroundColor, 1, wxEXPAND);
	flex_grid_sizer->Add(buttonBackgroundColor);
	// row 4
	flex_grid_sizer->Add(textForegroundColorNormal);
	flex_grid_sizer->Add(inputForegroundColorNormal, 1, wxEXPAND);
	flex_grid_sizer->Add(buttonForegroundColorNormal);
	// row 5
	flex_grid_sizer->Add(textForegroundColorWarning);
	flex_grid_sizer->Add(inputForegroundColorWarning, 1, wxEXPAND);
	flex_grid_sizer->Add(buttonForegroundColorWarning);
	// row 6
	flex_grid_sizer->Add(textForegroundColorError);
	flex_grid_sizer->Add(inputForegroundColorError, 1, wxEXPAND);
	flex_grid_sizer->Add(buttonForegroundColorError);
	// row 7
	flex_grid_sizer->Add(buttonStart);
	flex_grid_sizer->Add(buttonStop, 1, wxEXPAND);
	flex_grid_sizer->AddSpacer(0);
	// row 8
	flex_grid_sizer->Add(buttonHide);
	flex_grid_sizer->Add(buttonDisplayIdentifier, 1, wxEXPAND);
	flex_grid_sizer->AddSpacer(0);
	// row 9
	flex_grid_sizer->Add(textTimerDisplaying);
	flex_grid_sizer->AddStretchSpacer();
	flex_grid_sizer->AddSpacer(0);
	
	// If we're going to grow vertically, grow the review text area
	flex_grid_sizer->AddGrowableRow(9, 1); // row 3, proportion 1
	// if we're going to grow horizontally, grow the data input column
	flex_grid_sizer->AddGrowableCol(1, 1); // column 1, proportion 1
	
	// put it all together
	horizontal_box->Add(flex_grid_sizer, 1, wxALL | wxEXPAND, 15);
	panel->SetSizer(horizontal_box);
	Center();
	
}

/***
 * Destructor
 */
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
	buttonHide->Destroy();
	buttonDisplayIdentifier->Destroy();
	buttonBackgroundColor->Destroy();
	buttonForegroundColorNormal->Destroy();
	buttonForegroundColorWarning->Destroy();
	buttonForegroundColorError->Destroy();
	//delete flex_grid_sizer;
	//delete horizontal_box;
	panel->Destroy();
	delete currentTimerFrame;
	delete secondTimer;
}

/**
 * Display the SettingsFrame. This override is so that we move the
 * settings frame to the correct display.
 *
 * @param show true to show, false to hide
 * @returns the results
 */
bool SettingsFrame::Show(bool show) {
	bool retVal = wxFrame::Show(show);
	this->Move(startPoint->x, startPoint->y);
	return retVal;
}

BEGIN_EVENT_TABLE(SettingsFrame, wxFrame)
EVT_BUTTON (BUTTON_Start, SettingsFrame::OnButtonStart)
EVT_BUTTON (BUTTON_Stop, SettingsFrame::OnButtonStop)
EVT_BUTTON (BUTTON_Hide, SettingsFrame::OnButtonHide)
EVT_BUTTON (BUTTON_Display_Identifier, SettingsFrame::OnButtonDisplayIdentifier)
EVT_BUTTON (BUTTON_BackgroundColor, SettingsFrame::OnButtonBackgroundColor)
EVT_BUTTON (BUTTON_ForegroundColorNormal, SettingsFrame::OnButtonForegroundColorNormal)
EVT_BUTTON (BUTTON_ForegroundColorWarning, SettingsFrame::OnButtonForegroundColorWarning)
EVT_BUTTON (BUTTON_ForegroundColorError, SettingsFrame::OnButtonForegroundColorError)
END_EVENT_TABLE()


/**
 * static method - Based on the display number, get the default location for a potential SettingsFrame
 * @param displayNumber which display will the application be put on
 * @returns the point to use to display the SettingsFrame on that display
 */
wxPoint* SettingsFrame::GetDefaultLocation(int displayNumber) {
	// validate the screen number
	int numDisplays = wxDisplay::GetCount();
	if (displayNumber > numDisplays)
		return new wxPoint(-1, -1);
	
	wxDisplay *chosenDisplay = new wxDisplay((int)displayNumber);
	wxRect* chosenGeometry = new wxRect(chosenDisplay->GetGeometry());

	wxPoint* point = new wxPoint(chosenGeometry->x, chosenGeometry->y);
	
	delete chosenGeometry;
	delete chosenDisplay;
	return point;
}

/**
 * Display small dialog boxes on each screen
 */
void SettingsFrame::OnButtonDisplayIdentifier(wxCommandEvent &event) {
	if (identifierDialogs == nullptr) {
		unsigned int numDisplays = wxDisplay::GetCount();
		identifierDialogs = (IdentifierDialog**)malloc(sizeof(IdentifierDialog) * numDisplays);
		numIdentifierDialogs = numDisplays;
		for (int i = 0; i < numDisplays; i++) {
			wxDisplay *currDisplay = new wxDisplay(i);
			wxRect *currentGeometry = new wxRect(currDisplay->GetGeometry());
			wxPoint currentPoint(currentGeometry->x, currentGeometry->y);// = new wxPoint(currentGeometry->x, currentGeometry->y);
			delete currentGeometry;
			delete currDisplay;
			std::stringstream ss;
			ss << "Display Number " << i;
			std::string title = ss.str();
			IdentifierDialog *dlg = new IdentifierDialog(NULL, -1, title, currentPoint, wxSize(150, 25));
			identifierDialogs[i] = dlg;
			// change the text of the button
			buttonDisplayIdentifier->SetLabel("Hide Display Identifiers");
		}
	} else {
		for(int i = 0; i < numIdentifierDialogs; i++) {
			IdentifierDialog *dlg = identifierDialogs[i];
			dlg->Hide();
			delete dlg;
		}
		delete identifierDialogs;
		identifierDialogs = nullptr;
		buttonDisplayIdentifier->SetLabel("Show Display Identifiers");
	}
}

/**
 * The start button was clicked
 * @param event the event that was thrown
 */
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
	std::chrono::seconds timerSeconds(0);
	if (strValue.Contains(":")) {
		std::string s = std::string(strValue.mb_str());
		std::string mins = s.substr(0, s.find(':'));
		std::string secs = s.substr(s.find(':') + 1);
		timerSeconds += std::chrono::minutes(std::stoi(mins));
		timerSeconds += std::chrono::seconds(std::stoi(secs));
	} else {
		timerSeconds += std::chrono::minutes(std::stoi(std::string(strValue.mb_str())));
	}
	
	// we can no longer set the display number
	inputScreenNumber->SetEditable(false);

	// start window (if it is not already there)
	if (currentTimerFrame == nullptr)
		currentTimerFrame = new TimerFrame(this, secondTimer, (int)displayNumber);
 
	displayingTime = false;
	currentTimerFrame->SetDisplayTime(displayingTime);
	
	// give me back focus
	this->SetFocus();
	
	// now set time
	currentTimerFrame->SetTimer(timerSeconds);
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
	this->errorTime = startTime + timerSeconds;
	strValue = inputWarningTime->GetValue();
	this->warningTime = this->errorTime - getDuration(strValue.ToStdString());
}

/***
 * stops the timer, and displays the current time.
 */
void SettingsFrame::OnButtonStop(wxCommandEvent &event)
{
	displayingTime = true;
	if (currentTimerFrame != nullptr)
		currentTimerFrame->SetDisplayTime(displayingTime);
}

/***
 * close down the remote "dialog"
 **/
void SettingsFrame::OnButtonHide(wxCommandEvent &event)
{
	secondTimer->StopTimer();
	if (currentTimerFrame != nullptr) {
		currentTimerFrame->Hide();
		delete currentTimerFrame;
		currentTimerFrame = nullptr;
	}
	inputScreenNumber->SetEditable(true);
}

/**
 * someone clicked the color button to select a background color
 * @param event the event that was thrown
 */
void SettingsFrame::OnButtonBackgroundColor(wxCommandEvent &event) {
	wxColour result;
	OnColorButton(inputBackgroundColor, &result);
	// now set background of controls
	inputForegroundColorNormal->SetBackgroundColour(result);
	inputForegroundColorWarning->SetBackgroundColour(result);
	inputForegroundColorError->SetBackgroundColour(result);
}

/**
 * Someone clicked the color button to select the normal foreground color
 * @param event the event that was thrown
 */
void SettingsFrame::OnButtonForegroundColorNormal(wxCommandEvent &event) {
	OnColorButton(inputForegroundColorNormal);
}

/**
 * Someone clicked the color button to select the warning foreground color
 * @param event the event that was thrown
 */
void SettingsFrame::OnButtonForegroundColorWarning(wxCommandEvent &event) {
	OnColorButton(inputForegroundColorWarning);
}

/**
 * Someone clicked the button to select the error foreground color
 * @param event the event that was thrown
 */
void SettingsFrame::OnButtonForegroundColorError(wxCommandEvent &event) {
	OnColorButton(inputForegroundColorError);
}

/***
 * Sets the color within the control
 **/
void SettingsFrame::SetControlColors(wxTextCtrl *control)
{
	// convert text to wxColor
	wxString str = control->GetValue();
	wxColour color(str);
	
	if (control == inputBackgroundColor) {
		// this is the background color input box. Protect ourselves so that the
		// font is not the same color as the background (and hence, invisible)
		control->SetBackgroundColour(str);
		std::string c = std::string(color.GetAsString().mb_str());
		if (c == "black") {
			control->SetForegroundColour("white");
		}
	} else {
		// this is not the background color input box
		control->SetForegroundColour(color);
		wxString bgs = inputBackgroundColor->GetValue();
		wxColour bg(bgs);
		control->SetBackgroundColour(bg);
	}
}

/***
 * Handles someone clicking a color button
 * @param textControl the control that we're using
 * @param color the place to store the color that was selected by the user (optional)
 **/
void SettingsFrame::OnColorButton(wxTextCtrl* textControl, wxColour* color) {
	bool colorPassed = true;
	if (color == NULL) {
		colorPassed = false;
		color = new wxColour();
	}
	wxString currentSetting = textControl->GetValue();
	wxColour currentColor(currentSetting);
	wxColourData colorData;
	colorData.SetColour(currentColor);
	wxColourDialog dlg(this, &colorData);
	if (dlg.ShowModal() == wxID_OK) {
		wxColourData data = dlg.GetColourData();
		*color = data.GetColour();
		textControl->SetValue(color->GetAsString());
		SetControlColors(textControl);
	}
	if (!colorPassed) {
		delete color;
	}
}

/***
 * The timer threw an event, place the time on the current dialog
 * and possibly change the color of the font on the TimerFrame
 * @param event the event that was thrown
 **/
void SettingsFrame::OnTimer(wxTimerEvent &event)
{
	wxColour *currentColor = normalColor;
	currentTimerFrame->SetForegroundColour(*currentColor);
	if (displayingTime) {
		textTimerDisplaying->SetLabel(SecondTimer::ToString());
	} else {
		if (currentTimerFrame != nullptr) {
			// see if we need to change the color
			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
			if (now >= warningTime) {
				if (now >= errorTime)
					currentColor = errorColor;
				else
					currentColor = warningColor;
				currentTimerFrame->SetForegroundColour(*currentColor);
			}
		}
		textTimerDisplaying->SetLabel(SecondTimer::ToString(secondTimer->SecondsSinceStart()));
	}
	// continue processing other event handlers
	event.Skip(true);
}

/***
 * convert a string as MM:SS or simply MM to seconds
 * @param input a string as MM:SS or simply MM
 * @returns number of seconds of input string. i.e. 1:30 = 90 seconds
 **/
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

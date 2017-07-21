//
//  TextControl.cpp
//  TestWxWidgets
//
//  Created by John Jones on 6/18/17.
//  Copyright © 2017 JMJAtlanta. All rights reserved.
//

#include "TextControl.hpp"
#include <wx/colordlg.h>

TextControl::TextControl(wxWindow *parent) : wxTextCtrl(parent, -1)
{
	dialogUp = false;
}

TextControl::~TextControl()
{
	
}

BEGIN_EVENT_TABLE(TextControl, wxTextCtrl)
EVT_SET_FOCUS(TextControl::OnSetFocus)
EVT_KILL_FOCUS(TextControl::OnKillFocus)
END_EVENT_TABLE()

void TextControl::OnSetFocus(wxFocusEvent &event)
{
	if (!dialogUp) {
		dialogUp = true;
		wxString currentSetting = this->GetValue();
		wxColour currentColor(currentSetting);
		wxColourData colorData;
		colorData.SetColour(currentColor);
		wxColourDialog dlg(this, &colorData);
		if (dlg.ShowModal() == wxID_OK) {
			wxColourData data = dlg.GetColourData();
			wxColour color = data.GetColour();
			this->SetValue(color.GetAsString());
		}
		dialogUp = false;
	}
}

void TextControl::OnKillFocus(wxFocusEvent &event)
{
}

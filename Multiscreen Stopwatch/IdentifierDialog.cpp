//
//  IdentifierDialog.cpp
//  MultiScreenStopwatch
//
//  Created by John Jones on 8/19/17.
//  Copyright © 2017 JMJAtlanta. All rights reserved.
//

#include "IdentifierDialog.hpp"

IdentifierDialog::IdentifierDialog(wxWindow* parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
	: wxFrame(parent, id, title, pos, size, style, name)
{
	wxPanel *panel = new wxPanel(this, -1);
	
	new wxStaticText(panel, -1, title);

	wxBoxSizer *box = new wxBoxSizer(wxHORIZONTAL);

	panel->SetSizer(box);
	Center();
	Move(pos);
	Show();
}

IdentifierDialog::~IdentifierDialog() {
	
}

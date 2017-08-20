//
//  IdentifierDialog.hpp
//  MultiScreenStopwatch
//
//  Created by John Jones on 8/19/17.
//  Copyright © 2017 JMJAtlanta. All rights reserved.
//

#ifndef IdentifierDialog_hpp
#define IdentifierDialog_hpp

#include <stdio.h>
#include "wx/wx.h"

class IdentifierDialog : public wxFrame {
public:
	IdentifierDialog(wxWindow* parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style = wxSTAY_ON_TOP, const wxString &name=wxDialogNameStr);
	~IdentifierDialog();
};

#endif /* IdentifierDialog_hpp */

//
//  TextControl.hpp
//  TestWxWidgets
//
//  Created by John Jones on 6/18/17.
//  Copyright © 2017 JMJAtlanta. All rights reserved.
//

#ifndef TextControl_hpp
#define TextControl_hpp

#include <stdio.h>
#include <wx/wx.h>

class TextControl : public wxTextCtrl
{
public:
	TextControl(wxWindow *parent);
	~TextControl();
	DECLARE_EVENT_TABLE();
private:
	void OnSetFocus(wxFocusEvent &event);
	void OnKillFocus(wxFocusEvent &event);
private:
	bool dialogUp;
};

#endif /* TextControl_hpp */

/**
 * This is an experimental class to pop up a dialog when this control
 * gets focus. It does not work too well, as it pops up when it 
 * shouldn't. More refining is required. Not using for now...
 */
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

#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <wx/wx.h>
#include <wx/textctrl.h>
#include "hardware.h"

class ToolFrame : public wxFrame
{
public:
    ToolFrame(const wxString& title);

    void OnBtnClick(wxCommandEvent & event);

private:
    wxTextCtrl* txtInfo;
};


#endif
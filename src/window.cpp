#include "window.h"

ToolFrame::ToolFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 300))
{
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);

    wxString msg("Lots and lots of text to wrap hopefully. "
        "Lots and lots of text to wrap hopefully. "
        "Lots and lots of text to wrap hopefully. "
        "Lots and lots of text to wrap hopefully. "
        "Lots and lots of text to wrap hopefully. "
        "Lots and lots of text to wrap hopefully. "
    );

    auto myBtn = new wxButton(this, wxID_EXIT, wxT("获取"));
    auto myTxt = new wxTextCtrl(this, wxID_ANY, msg, wxDefaultPosition, wxSize(200, 200), wxTE_MULTILINE);
    // myTxt->SetForegroundColour("white");
    // myTxt->SetBackgroundColour("black");

    topSizer->Add(myBtn, wxSizerFlags().Center());
    topSizer->AddSpacer(40);
    topSizer->Add(myTxt, wxSizerFlags().Center().Border(wxALL, 20));

    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ToolFrame::OnBtnClick));
    myBtn->SetFocus();


    this->SetSizerAndFit(topSizer);
    Layout();
    Centre();
}

void ToolFrame::OnBtnClick(wxCommandEvent & WXUNUSED(event))
{
    Close(true);
}
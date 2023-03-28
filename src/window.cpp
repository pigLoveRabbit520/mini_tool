#include "window.h"

ToolFrame::ToolFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 400))
{
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);

    auto myBtn = new wxButton(this, wxID_EXIT, wxT("获取"));
    auto myTxt = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(500, 500), wxTE_MULTILINE);
    wxFont font = myTxt->GetFont();
    font.SetPointSize(12);
    myTxt->SetFont(font);
    // myTxt->SetForegroundColour("white");
    // myTxt->SetBackgroundColour("black");

    topSizer->AddSpacer(20);
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
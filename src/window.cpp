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
    this->txtInfo = myTxt;
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
    MainBoard* mainBoard = new MainBoard();
    auto res = mainBoard->GetInfo();
    if (res < 0)
    {
        this->txtInfo->AppendText("无法打开注册表项");
        delete mainBoard;
        return;
    }
    auto info = wxString::Format(wxT("主板制造商：%s\r\n主板型号：%s") , 
        mainBoard->BaseBoardManufacturer, 
        mainBoard->BaseBoardProduct
    );
    this->txtInfo->AppendText(info);

    delete mainBoard;
}
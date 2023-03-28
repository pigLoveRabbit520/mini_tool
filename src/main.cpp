#include <wx/wx.h>
#include "window.h"

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

    ToolFrame *btnapp = new ToolFrame(wxT("系统工具"));
    btnapp->Show(true);

    return true;
}
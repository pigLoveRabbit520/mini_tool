#ifndef MAINBOARD_H
#define MAINBOARD_H
#include <wx/wx.h>
#include <windows.h>
#include <comdef.h>
#include <comutil.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "Advapi32.lib")

class MainBoard
{
public:
    int GetInfo();
    wxString BaseBoardManufacturer; // 主板制造商
    wxString BaseBoardProduct; // 主板型号
    wxString CPUName; // CPU名称
    wxString CPUManufacturer; // CPU制造商
    long CPUMaxClockSpeed; // CPU主频
private:
    const int errFailed = -1;

    int getCPUInfo();
};

#endif
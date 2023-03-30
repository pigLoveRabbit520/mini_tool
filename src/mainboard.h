#ifndef MAINBOARD_H
#define MAINBOARD_H
#include <wx/wx.h>
#include <windows.h>

#pragma comment(lib, "Advapi32.lib")

class MainBoard
{
public:
    int GetInfo();
    wxString BaseBoardManufacturer; // 主板制造商
    wxString BaseBoardProduct; // 主板型号
private:
    const int errFailed = -1;
};

#endif
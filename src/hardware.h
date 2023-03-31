#ifndef MAINBOARD_H
#define MAINBOARD_H
#include <wx/wx.h>
#include <windows.h>

#pragma comment(lib, "Advapi32.lib")

// intrinsics
#if defined(__GNUC__)    // GCC
#include <cpuid.h>
#elif defined(_MSC_VER)    // MSVC
#if _MSC_VER >=1400    // VC2005
#include <intrin.h>
#endif    // #if _MSC_VER >=1400
#else
#error Only supports MSVC or GCC.
#endif    // #if defined(__GNUC__)

class Hardware
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
    void cpuid(unsigned int CPUInfo[4], unsigned int InfoType);
    std::string getCpuVendor(); // 取得CPU厂商（Vendor）
    std::string getCpuName();
    void getCPUInfo();
};

#endif
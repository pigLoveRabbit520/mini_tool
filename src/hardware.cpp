#include "hardware.h"

int Hardware::GetInfo()
{
    HKEY hKey;
    LONG result;
    // 打开注册表项
    result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_READ, &hKey);

    if (result != ERROR_SUCCESS)
    {
        return errFailed;
    }

    // 读取主板制造商信息
    wchar_t manufacturer[255];
    DWORD size = sizeof(manufacturer);
    result = RegQueryValueEx(hKey, L"BaseBoardManufacturer", NULL, NULL, (LPBYTE)manufacturer, &size);

    if (result != ERROR_SUCCESS)
    {
        return errFailed;
    }

    this->BaseBoardManufacturer = manufacturer;

    wchar_t model[255];
    size = sizeof(model);
    result = RegQueryValueEx(hKey, L"BaseBoardProduct", NULL, NULL, (LPBYTE)model, &size);

    this->BaseBoardProduct = model;

    // 关闭注册表项
    RegCloseKey(hKey);
    // 再获取CPU信息
    this->getCPUInfo();
    return 0;
}

std::string Hardware::getCpuVendor()
{
    char vendor[13];
    unsigned int dwBuf[4];
    cpuid(dwBuf, 0);
    // save. 保存到pvendor
    *(unsigned int*)&vendor[0] = dwBuf[1];    // ebx: 前四个字符.
    *(unsigned int*)&vendor[4] = dwBuf[3];    // edx: 中间四个字符.
    *(unsigned int*)&vendor[8] = dwBuf[2];    // ecx: 最后四个字符.
    vendor[12] = '\0';
    return vendor;
}

std::string Hardware::getCpuName()
{
    char pbrand[49];
    cpuid((unsigned int*)&pbrand[0], 0x80000002U);    // 前16个字符.
    cpuid((unsigned int*)&pbrand[16], 0x80000003U);    // 中间16个字符.
    cpuid((unsigned int*)&pbrand[32], 0x80000004U);    // 最后16个字符.

    pbrand[48] = '\0';
    return pbrand;
}

void Hardware::cpuid(unsigned int CPUInfo[4], unsigned int InfoType)
{
    __cpuid(InfoType, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]); // gcc函数
}

void Hardware::getCPUInfo()
{
    this->CPUManufacturer = getCpuVendor();
    this->CPUName = getCpuName();
}
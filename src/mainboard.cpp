#include "mainboard.h"

int MainBoard::GetInfo()
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
    return 0;
}
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

int MainBoard::getCPUInfo()
{
    HRESULT hres;

    // 初始化COM库
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
        std::cerr << "Failed to initialize COM library. Error code: 0x" << std::hex << hres << std::endl;
        return errFailed;
    }

    // 设置COM安全性
    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL
    );
    if (FAILED(hres))
    {
        std::cerr << "Failed to initialize security. Error code: 0x" << std::hex << hres << std::endl;
        CoUninitialize();
        return errFailed;
    }

    // 获取WMI服务对象
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        reinterpret_cast<LPVOID*>(&pLoc)
    );
    if (FAILED(hres))
    {
        std::cerr << "Failed to create IWbemLocator object. Error code: 0x" << std::hex << hres << std::endl;
        CoUninitialize();
        return errFailed;
    }

    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        &pSvc
    );
    if (FAILED(hres))
    {
        std::cerr << "Failed to connect to IWbemServices object. Error code: 0x" << std::hex << hres << std::endl;
        pLoc->Release();
        CoUninitialize();
        return errFailed;
    }

    // 设置WMI查询语句
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        _bstr_t("WQL"),
        _bstr_t("SELECT Name, Manufacturer, MaxClockSpeed FROM Win32_Processor"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator
    );
    if (FAILED(hres))
    {
        std::cerr << "Failed to execute WQL query. Error code: 0x" << std::hex << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return errFailed;
    }

    // 解析查询结果
    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    while (pEnumerator)
    {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (uReturn == 0)
        {
            break;
        }

        VARIANT vtProp;
        hres = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres))
        {
            this->CPUName = vtProp.bstrVal;
            VariantClear(&vtProp);
        }

        hres = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres))
        {
            this->CPUManufacturer = vtProp.bstrVal;
            VariantClear(&vtProp);
        }

        hres = pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres))
        {
            this->CPUMaxClockSpeed = vtProp.ulVal;
            VariantClear(&vtProp);
        }

        pclsObj->Release();
    }

    // 释放资源
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();
    return 0;
}
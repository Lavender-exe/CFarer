// CFarer - Red Team Exercise 06
// TOPIC: WMI Process Execution - lateral movement via Win32_Process::Create
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized penetration testing education - lateral movement
//
// WMI (Windows Management Instrumentation) can create processes on local or
// remote machines via the Win32_Process class.  This is used for lateral movement
// because:
//   - No service install required (unlike PsExec)
//   - Runs as SYSTEM by default on remote targets
//   - Appears as WmiPrvSE.exe parent, not attacker's process
//
// COM + WMI API:
//   CoInitializeEx(NULL, COINIT_MULTITHREADED)
//   CoInitializeSecurity(...)
//   CoCreateInstance(CLSID_WbemLocator) -> IWbemLocator
//   IWbemLocator::ConnectServer(L"ROOT\\CIMV2") -> IWbemServices
//   IWbemServices::GetObject(L"Win32_Process") -> IWbemClassObject
//   Win32_Process::GetMethod(L"Create") -> spawn
//   IWbemServices::ExecMethod
//
// Task:
//   Implement local WMI process execution (no remote credentials needed).
//   Create calc.exe via Win32_Process::Create and print the resulting PID.
//
// Compile: cl /nologo /std:c11 rt06_wmi_exec.c /link ole32.lib oleaut32.lib wbemuuid.lib

#define COBJMACROS
#define CINTERFACE
#define _WIN32_DCOM
#include <windows.h>
#include <wbemidl.h>
#include <stdio.h>
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

int main(void) {
    HRESULT hr;

    // TODO 1: CoInitializeEx(NULL, COINIT_MULTITHREADED)
    hr = S_OK; // replace with CoInitializeEx
    if (FAILED(hr)) { fprintf(stderr, "CoInitializeEx: 0x%lx\n", hr); return 1; }

    // TODO 2: CoInitializeSecurity (broad permissions for WMI)
    // CoInitializeSecurity(NULL, -1, NULL, NULL,
    //     RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
    //     NULL, EOAC_NONE, NULL);

    IWbemLocator *pLoc = NULL;
    // TODO 3: CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER,
    //           IID_IWbemLocator, (LPVOID*)&pLoc)
    hr = E_NOTIMPL; // replace
    if (FAILED(hr)) { fprintf(stderr, "CoCreateInstance: 0x%lx\n", hr); goto done; }

    IWbemServices *pSvc = NULL;
    // TODO 4: BSTR ns = SysAllocString(L"ROOT\\CIMV2");
    //         hr = IWbemLocator_ConnectServer(pLoc, ns, NULL, NULL, NULL, 0, NULL, NULL, &pSvc);
    //         SysFreeString(ns);
    hr = E_NOTIMPL;
    if (FAILED(hr)) { fprintf(stderr, "ConnectServer: 0x%lx\n", hr); goto done; }

    // TODO 5: CoSetProxyBlanket on pSvc for proper auth
    // CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
    //     RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

    IWbemClassObject *pClass = NULL, *pMethod = NULL, *pInParams = NULL, *pInParamsInst = NULL;
    // TODO 6: IWbemServices_GetObject(pSvc, L"Win32_Process", 0, NULL, &pClass, NULL)
    // TODO 7: IWbemClassObject_GetMethod(pClass, L"Create", 0, &pMethod, NULL)
    // TODO 8: IWbemClassObject_SpawnInstance(pMethod, 0, &pInParamsInst)
    // TODO 9: set CommandLine parameter: VARIANT v; V_VT(&v)=VT_BSTR;
    //         V_BSTR(&v) = SysAllocString(L"calc.exe");
    //         IWbemClassObject_Put(pInParamsInst, L"CommandLine", 0, &v, 0);
    //         VariantClear(&v);
    // TODO 10: IWbemServices_ExecMethod(pSvc, L"Win32_Process", L"Create", 0, NULL,
    //            pInParamsInst, &pOutParams, NULL)
    // TODO 11: extract ProcessId: IWbemClassObject_Get(pOutParams, L"ProcessId", 0, &vPid, NULL, NULL)

    printf("WMI exec skeleton complete - implement TODOs for calc.exe launch\n");

done:
    if (pSvc)   IWbemServices_Release(pSvc);
    if (pLoc)   IWbemLocator_Release(pLoc);
    CoUninitialize();
    return FAILED(hr) ? 1 : 0;
}

// I AM NOT DONE

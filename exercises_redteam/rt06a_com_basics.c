// CFarer - Red Team Exercise 06A
// TOPIC: COM Basics - the API every Windows tool (WMI, Task Scheduler) sits on
// DIFFICULTY: Beginner-Intermediate  PLATFORM: Windows
// PURPOSE: Authorized penetration testing education
//
// COM (Component Object Model) is how Windows exposes big subsystems:
// WMI (rt06), the Task Scheduler (rt09), shell automation, and more.
// Every COM program follows the same 4-step pattern:
//
//   1. CoInitializeEx        - initialize COM for this thread
//   2. CoCreateInstance      - create an object, get a pointer to its interface
//   3. Call methods via the interface (in C: IFACE_Method(obj, args...))
//   4. Release() the interfaces + CoUninitialize()
//
// Two extras appear in real code and here:
//   CoInitializeSecurity - set the process-wide auth level (once per process)
//   CoSetProxyBlanket    - set auth on one specific interface pointer
//
// Under the hood an interface is a struct of function pointers (a vtable).
// In C we call through the COBJMACROS helpers: IWbemLocator_ConnectServer(pLoc, ...)
// expands to pLoc->lpVtbl->ConnectServer(pLoc, ...). The object itself is always
// passed as the first argument. Strings are wide (BSTR / L"...").
//
// Task:
//   1. CoInitializeEx(NULL, COINIT_MULTITHREADED).
//   2. CoCreateInstance(CLSID_WbemLocator, IID_IWbemLocator, &pLoc).
//   3. IWbemLocator_ConnectServer(pLoc, L"ROOT\\CIMV2", ..., &pSvc).
//   4. CoSetProxyBlanket(pSvc, ...).
//   5. Print success, Release() everything, CoUninitialize().
//
// Compile: gcc -std=c11 rt06a_com_basics.c -lole32 -loleaut32 -lwbemuuid

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
    hr = E_NOTIMPL; // replace
    if (FAILED(hr)) { fprintf(stderr, "CoInitializeEx: 0x%lx\n", hr); return 1; }

    IWbemLocator *pLoc = NULL;
    // TODO 2: CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER,
    //           IID_IWbemLocator, (LPVOID*)&pLoc)
    hr = E_NOTIMPL; // replace
    if (FAILED(hr)) { fprintf(stderr, "CoCreateInstance: 0x%lx\n", hr); goto done; }

    IWbemServices *pSvc = NULL;
    // TODO 3: BSTR ns = SysAllocString(L"ROOT\\CIMV2");
    //         hr = IWbemLocator_ConnectServer(pLoc, ns,
    //                    NULL, NULL, NULL, 0, NULL, NULL, &pSvc);
    //         SysFreeString(ns);
    hr = E_NOTIMPL; // replace
    if (FAILED(hr)) { fprintf(stderr, "ConnectServer: 0x%lx\n", hr); goto done; }

    // TODO 4: CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
    //           RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE)
    hr = E_NOTIMPL; // replace
    if (FAILED(hr)) { fprintf(stderr, "CoSetProxyBlanket: 0x%lx\n", hr); goto done; }

    printf("COM initialized, WbemLocator created, ROOT\\CIMV2 connected\n");
    printf("Ready for rt06 (WMI exec) and rt09 (Task Scheduler)\n");

done:
    if (pSvc) IWbemServices_Release(pSvc);
    if (pLoc) IWbemLocator_Release(pLoc);
    CoUninitialize();
    return FAILED(hr) ? 1 : 0;
}

// I AM NOT DONE

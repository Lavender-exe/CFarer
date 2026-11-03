// CFarer - Red Team Exercise 09
// TOPIC: Scheduled Task Persistence via COM (ITaskService)
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized penetration testing education - persistence
//
// Scheduled tasks run at user login, system startup, or on a timer.
// Harder to detect than Run keys (separate task scheduler database).
// COM interface: ITaskService (taskschd.dll)
//
// Pattern:
//   CoCreateInstance(CLSID_TaskScheduler) -> ITaskService
//   ITaskService::Connect(NULL,NULL,NULL,NULL)  - local machine
//   ITaskService::NewTask(0) -> ITaskDefinition
//   ITaskDefinition::get_Settings() -> ITaskSettings (set hidden, etc.)
//   ITaskDefinition::get_Triggers() -> add logon trigger
//   ITaskDefinition::get_Actions()  -> add exec action (path + args)
//   ITaskService::GetFolder(L"\\") -> ITaskFolder
//   ITaskFolder::RegisterTaskDefinition(name, pTask, ...) -> create task
//   ITaskFolder::DeleteTask(name, 0) - cleanup
//
// Task:
//   1. CoInitializeEx + CoInitializeSecurity.
//   2. CoCreateInstance(CLSID_TaskScheduler, IID_ITaskService).
//   3. ITaskService::Connect(NULL,NULL,NULL,NULL).
//   4. NewTask -> set description "CFarerTest".
//   5. Add TASK_TRIGGER_LOGON trigger.
//   6. Add TASK_ACTION_EXEC with path = current exe.
//   7. RegisterTaskDefinition in "\" folder.
//   8. Print "task created", then immediately DeleteTask to clean up.
//
// Compile: cl /nologo /std:c11 rt09_scheduled_task.c /link ole32.lib oleaut32.lib taskschd.lib

#define COBJMACROS
#define CINTERFACE
#define _WIN32_DCOM
#include <windows.h>
#include <taskschd.h>
#include <stdio.h>
#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

int main(void) {
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) { fprintf(stderr, "CoInit: 0x%lx\n", hr); return 1; }

    // TODO 1: CoInitializeSecurity (broad permissions)
    // CoInitializeSecurity(NULL,-1,NULL,NULL,RPC_C_AUTHN_LEVEL_PKT,
    //   RPC_C_IMP_LEVEL_IMPERSONATE,NULL,0,NULL);

    ITaskService *pSvc = NULL;
    // TODO 2: CoCreateInstance(CLSID_TaskScheduler,NULL,CLSCTX_INPROC_SERVER,
    //           IID_ITaskService,(void**)&pSvc)
    hr = E_NOTIMPL;
    if (FAILED(hr)) { fprintf(stderr, "CoCreateInstance: 0x%lx\n",hr); goto done; }

    // TODO 3: ITaskService_Connect(pSvc, v, v, v, v)  (v = empty VARIANT)
    // VARIANT v; VariantInit(&v);

    ITaskDefinition *pTask = NULL;
    // TODO 4: ITaskService_NewTask(pSvc, 0, &pTask)

    // TODO 5: logon trigger: ITaskDefinition_get_Triggers(pTask, &pTriggers)
    //   -> ITriggerCollection_Create(pTriggers, TASK_TRIGGER_LOGON, &pTrig)
    //   -> ITrigger_QueryInterface(pTrig, IID_ILogonTrigger, (void**)&pLogon)

    // TODO 6: exec action: ITaskDefinition_get_Actions(pTask, &pActions)
    //   -> IActionCollection_Create(pActions, TASK_ACTION_EXEC, &pAct)
    //   -> IAction_QueryInterface(pAct, IID_IExecAction, (void**)&pExec)
    //   char exe[MAX_PATH]; GetModuleFileNameA(NULL,exe,MAX_PATH);
    //   IExecAction_put_Path(pExec, SysAllocString(wchar_version_of_exe));

    ITaskFolder *pFolder = NULL;
    // TODO 7: ITaskService_GetFolder(pSvc, SysAllocString(L"\\"), &pFolder)
    //   ITaskFolder_RegisterTaskDefinition(pFolder, SysAllocString(L"CFarerTest"), pTask,
    //     TASK_CREATE_OR_UPDATE, v, v, TASK_LOGON_INTERACTIVE_TOKEN, v, NULL);
    printf("Task created (implement TODOs)\n");

    // TODO 8: cleanup
    //   ITaskFolder_DeleteTask(pFolder, SysAllocString(L"CFarerTest"), 0);
    printf("Task deleted\n");

done:
    if (pTask)   ITaskDefinition_Release(pTask);
    if (pFolder) ITaskFolder_Release(pFolder);
    if (pSvc)    ITaskService_Release(pSvc);
    CoUninitialize();
    return 0;
}

// LOOKAHEAD: rt10 introduces the CNG crypto API (bcrypt.h) - a new topic.
// Its hints 1-3 give the full open/hash/finish call sequence.

// I AM NOT DONE

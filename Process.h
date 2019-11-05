//Description –this module consists of library includes definitions of important integers and function declarations for proccesses.


#pragma once

#ifndef PROCESS_H
#define PROCESS_H
#include <stdio.h>
#include <windows.h>
#include <tchar.h> /* for TCHAR, _T() */
#include "Thread.h"

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

#define TIMEOUT_IN_MILLISECONDS 10000
#define BRUTAL_TERMINATION_CODE 0x55

//***********argu **pointers_to_threads_prcs;
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr);
DWORD CreateProcessSimpleMain(argu *p_args);
#endif
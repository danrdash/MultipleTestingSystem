
//Description –this module consists of library includes definitions of important integers and function declarations for threads.

#ifndef THREAD_H
#define THREAD_H
#include <windows.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#define FAILED 1
#define SUCCEEDED 0

#define MAX_LINE 100
#define NUM_THREADS 2
#define BRUTAL_TERMINATION_CODE 0x55
#define ERROR_CODE ((int)(-1))
#define MAX_ARG 100
#define MAX_OUTPATH 50
#define MAX_TESTNAME 100
#pragma warning(disable:4996)

typedef struct Arguments {
	char tname[MAX_TESTNAME];
	char outpath[MAX_OUTPATH];
	char **args;
	int arg_num;
	int res;
	int thread_counter; // specifies the thread
	char main_outpath[MAX_OUTPATH];
	DWORD exitc;
} argu;
argu **threads_for_routine; //This array of structs is meant for storing the thread structs in order

// Function Declarations -------------------------------------------------------

BOOL Tester(argu **p_args, int *failed);
DWORD WINAPI Thread(LPVOID lpParam);
HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine, LPVOID arguments, LPDWORD p_thread_id, char *file_outpath);



#endif
//Description –this module consists of functions that create proccesses.



#include "Process.h"
#include "Thread.h"




////** CreateProcessSimple uses the win32 API to create a process that runs the
//* command in 'CommandLine'.it uses the win32 API function CreateProcess()
//* using default values for most parameters.
//*
//* Accepts:
//*--------
//* CommandLine - a windows generic string containing the command that the new
//*               process performs. (See CreateProcess() documentation for more).
//* ProcessInfoPtr - an output parameter, used to return a PROCESS_INFORMATION
//*					structure containing data about the process that was created.
//*					(See CreateProcess() documentation for more).
//*
//* Returns:
//*--------
//* the output of CreateProcess().
//* **//

DWORD CreateProcessSimpleMain(argu *p_args) //This function opens the process of the specific executable and retuens its waitcode
{
	argu *current_pointer = p_args;
	PROCESS_INFORMATION procinfo;
	DWORD				waitcode;
	DWORD				exitcode;
	BOOL				retVal;
	// *****  Define the path to the file including its arguments  *****
	char *path_to_file = NULL;
	path_to_file = (char *)malloc(MAX_TESTNAME * sizeof(char));
	if (NULL == path_to_file)
	{
		ErrorPlan(p_args->main_outpath);
		exit(ERROR_CODE);
	}
	strcpy(path_to_file, current_pointer->tname);
	if (NULL != current_pointer->args) {
		int idx = 0;
		for (idx = 0; idx < current_pointer->arg_num; idx++) {
			strcat(path_to_file, " ");
			strcat(path_to_file, (current_pointer->args)[idx]);
		}
	}
	// *****  End of the file's path definition  *****
	retVal = CreateProcessSimple(path_to_file, &procinfo); //Create a process for the executable file on the predefined path

	free(path_to_file);
	if (retVal == 0)
	{
		printf("Process Creation Failed!\n");
		return FAILED;
	}


	waitcode = WaitForSingleObject(
		procinfo.hProcess,
		TIMEOUT_IN_MILLISECONDS); /* Waiting 10 secs for the process to end */

	

	GetExitCodeProcess(procinfo.hProcess, &exitcode);
	current_pointer->exitc = exitcode;


	CloseHandle(procinfo.hProcess); /* Closing the handle to the process */
	CloseHandle(procinfo.hThread); /* Closing the handle to the main thread of the process */
	
	return waitcode; // Return the waitcode of the specific process
}

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
//Description –a simple function to create a process
//Parameters – commandline, which is what we want to run, *processinfoPtr which contains the pointer in which we store the process informatoin
//Returns – function CreateProcess

BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr)
{
	STARTUPINFO	startinfo = { sizeof(STARTUPINFO), NULL, 0 }; /* <ISP> here we */
															  /* initialize a "Neutral" STARTUPINFO variable. Supplying this to */
															  /* CreateProcess() means we have no special interest in this parameter. */
															  /* This is equivalent to what we are doing by supplying NULL to most other */
															  /* parameters of CreateProcess(). */

	return CreateProcess(NULL, /*  No module name (use command line). */
		CommandLine,			/*  Command line. */
		NULL,					/*  Process handle not inheritable. */
		NULL,					/*  Thread handle not inheritable. */
		FALSE,					/*  Set handle inheritance to FALSE. */
		NORMAL_PRIORITY_CLASS,	/*  creation/priority flags. */
		NULL,					/*  Use parent's environment block. */
		NULL,					/*  Use parent's starting directory. */
		&startinfo,				/*  Pointer to STARTUPINFO structure. */
		ProcessInfoPtr			/*  Pointer to PROCESS_INFORMATION structure. */
	);
}

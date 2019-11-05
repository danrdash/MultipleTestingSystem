
//Description –this module consists of functions that create threads.


#include "Functions.h"
#include "Process.h"
#include "Thread.h"






//Description – This function compares the output of each exe file to the expected result found in a dedicated txt file
//Parameters – pointer to an argu strcuture, also a pointer to an integer flag which indicates whether the compare succeeded or not
//Returns – returns the flag 'continue_flag' which enables the while loop within Thread to terminate

BOOL Tester(argu **p_args, int *failed)
{
	argu *current_pointer = *p_args; //This pointer is meant to deprive mutual exclusion

	char destination[MAX_LINE] = "\0", *cpointer = NULL;
	strcpy(destination, current_pointer->tname);
	int waitcode; //This is the wait code of the called process

	waitcode = (int)CreateProcessSimpleMain(current_pointer);//open the executale file process          maybe & before current_pointer
	if (waitcode != WAIT_OBJECT_0) //if the process was not signaled (timed out or failed), do not continue
	{
		*failed = 2; // The exe file was timed out
		current_pointer->res = *failed;
		return 0;
	}
	if (0 != current_pointer->exitc)
	{
		current_pointer->res = -1; // The process is considered as failed when the exit code is nonzero, 
		return 0;
	}
	
	//Open the txt file with the outputs of the test executable file
	cpointer = strchr(destination, '.');
	strcpy(cpointer, ".txt");
	FILE *fp_test = NULL;
	errno_t pointer1;
	pointer1 = fopen_s(&fp_test, destination, "r+");
	if (NULL == fp_test)
	{
		ErrorPlan((*p_args)->main_outpath);
		exit(1);
	}
	//Open the txt file with the expected outputs of the test executable file
	FILE *fp_expected = NULL;
	errno_t pointer2;
	pointer2 = fopen_s(&fp_expected, current_pointer->outpath, "r+");


	char *test_buff = NULL;
	char *expected_buff = NULL;

	int idx = 0;
	expected_buff = (char *)malloc(MAX_LINE * sizeof(char));
	if (NULL == expected_buff)
	{
		ErrorPlan((*p_args)->main_outpath);
		exit(ERROR_CODE);
	}
	expected_buff[0] = '\0';
	test_buff = (char *)malloc(MAX_LINE * sizeof(char));
	if (NULL == expected_buff)
	{
		ErrorPlan((*p_args)->main_outpath);
		exit(ERROR_CODE);
	}
	test_buff[0] = '\0';


	BOOL continue_flag = true;
	fgets(test_buff, MAX_LINE, fp_test);
	while (1) {//compare both strings (the output of the executable file and the expected output)
		if (NULL != fgets(expected_buff, MAX_LINE, fp_expected)) {
			if (strcmp(expected_buff, test_buff) != 0) {
				(*failed) = 1;
				current_pointer->res = *failed;
				break;
			}

			idx++;
		}
		if (NULL == fgets(test_buff, MAX_LINE, fp_test))
			break;
	}
	free(test_buff);
	free(expected_buff);
	continue_flag = false;
	
	return continue_flag;
}

//Description – The routine of the thread. It acts as the main function of the thread and calls the function'tester' in order to compare the actual result to the expected one
//Parameters – The argument of the thread's routine - in practice it is a pointer to a member of 'argu' struct
//Returns – returns zero when successful
DWORD WINAPI Thread(LPVOID lpParam) 
{
	extern int *test_num;
	static int thread_counter = -1; // The index of the specific thread in the following threads array
	int current_counter;
	extern argu **threads_for_routine;
	BOOL continue_flag = true;
	

	if (NULL == lpParam)
	{
		return ERROR_CODE;
	}
	int failed = 0;
	
	thread_counter++;
	current_counter = thread_counter;
	threads_for_routine[thread_counter] = (argu *) lpParam; // cast the type of lpParam to argu* allocate memory for it
	threads_for_routine[thread_counter]->thread_counter = thread_counter; // specify the thread
	
	while (continue_flag)
	{
		continue_flag = Tester(&threads_for_routine[current_counter], &failed);
	}
	
	return 0;
}
//Description – This function creates a thread
//Parameters – A pointer to the function to be executed by the thread, the arguments of the routine, the thread id, a pointer to the output file.
//Returns – thread handle

HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine, LPVOID arguments, LPDWORD p_thread_id,char *file_outpath)
{ // arguments represent the arguments of the thread's routine

	HANDLE thread_handle;
	if (NULL == p_start_routine)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		ErrorPlan(file_outpath);
		exit(ERROR_CODE);
	}

	if (NULL == p_thread_id)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		ErrorPlan(file_outpath);
		exit(ERROR_CODE);
	}
	thread_handle = CreateThread(
		NULL,            /*  default security attributes */
		0,               /*  use default stack size */
		p_start_routine, /*  thread function */
		arguments,            /*  argument to thread function */
		0,               /*  use default creation flags */
		p_thread_id);    /*  returns the thread identifier */

	if (NULL == thread_handle)
	{
		printf("Couldn't create thread\n");
		ErrorPlan(file_outpath);
		exit(ERROR_CODE);
	}

	return thread_handle;
}








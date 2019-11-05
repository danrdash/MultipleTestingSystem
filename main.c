//Authors – Dan Ram 305015521; Ori Asulin 308459304.
//Project – ex2.
//Description - in this file we included all needed headers, declared global arguments and implemented the main program.

#include "Thread.h"
#include "Process.h"
#include "Functions.h"
//Most Updated!





argu **arguments_array = NULL;
int *test_num = NULL;


int main(int argc, char *argv[])
{
	HANDLE *p_thread_handles;
	DWORD *p_thread_ids;
	
	int i = 0;
	extern argu **pointers_to_threads_prcs;
	extern argu **threads_for_routine;
	extern int *test_num;
	int threadz=0 ;
	int thread_idx = 0; //Define an index for the thread handles' array and set it to 0
	char buff[300], *token = NULL, **args = NULL;
	FILE *fp_write = NULL;
	argu *head = NULL;
	int flag = 0;


	//MEMORY ALLOCATION
	test_num = (int *)malloc(sizeof(int));
	*test_num = 0;


	CountTests(argv[1], test_num);// You should count the number of tests before using it to allocate space


	p_thread_handles = (HANDLE *)malloc(*test_num * sizeof(HANDLE));
	if (NULL == p_thread_handles)
	{
		ErrorPlan(argv[2]);
		return 1;
	}
	p_thread_ids = (DWORD *)malloc(*test_num * sizeof(DWORD));
	if (NULL == p_thread_ids)
	{
		ErrorPlan(argv[2]);
		return 1;
	}
	threads_for_routine = (argu**)malloc(100 * sizeof(argu*));
	if (NULL == threads_for_routine)
	{
		ErrorPlan(argv[2]);
		return 1;
	}
	arguments_array = (argu **)malloc((*test_num) * sizeof(argu *));
	if (NULL == arguments_array)
	{
		ErrorPlan(argv[2]);
		return 1;
	}
	for (int q = 0; q < *test_num; q++)
		arguments_array[q] = (argu *)malloc(sizeof(argu));
	
	//END OF MEMORY ALLOCATION
	OpenThreads(&buff, &head, &arguments_array, &threadz, &thread_idx, argv[1], &p_thread_handles, &p_thread_ids, argv[2]);
	
	WaitForMultipleObjects(*test_num, p_thread_handles, TRUE, INFINITE); // Wait for all threads to signal
	
	PrintErrorType(arguments_array, i, thread_idx, argv[2], flag);
	FreeArgs(arguments_array, threadz);
	
	free(test_num);
	for (i = 0; i < thread_idx; i++) {
		CloseHandle(p_thread_handles[i]);
	}
	free(p_thread_handles);
	free(p_thread_ids);
	
	


}





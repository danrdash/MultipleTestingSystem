
//Description – This module consists of basic useful functions which have nothing to do with threads and processes. but functions that help the program carryout



#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "Functions.h"
#include "Thread.h"


void ErrorPlan(char *filepath)
{	
	FILE *fp_write = NULL;
	fopen_s(&fp_write, filepath, "w");
	printf("There was an Error in allocating memory, could not complete program");
	fprintf(fp_write, "There was an Error in allocating memory, could not complete program");
	fclose(fp_write);
	return NULL;
}

//Description –Prints all arguments in argu structure
//Parameters – pointer to argu structure
//Returns – returns nothing

void PrintArguStruct(argu *head) {
	printf("%s\n", head->tname);
	int i = 0;
	char **arg = head->args;
	for (i = 0; i < head->arg_num; i++) {
		printf("%s\n", *(arg + i));
	}
	printf("%s\n", head->outpath);
	printf("%d\n", head->arg_num);
	printf("This is the result: %d\n", head->res);
	return NULL;
}
//Description –Counts the number of arguments for any give test executable
//Parameters – pointer to file_path string and a pointer to test_num which saves the number of arguments for a given test
//Returns – return the value of number of arguments

int CountTests(char* file_path, int *test_num) {
	char line[300];
	FILE *fp_read = NULL;

	fopen_s(&fp_read, file_path, "r");
	if (fp_read == NULL) return FAILED;
	while (fgets(line, MAX_LINE, fp_read) != NULL)
	{
		(*test_num)++;
	}
	fclose(fp_read);

	return *test_num;
}



//Description –Create a new data structure Argu, and fills all of it's arguments according to buff's contents
//Parameters – pointer to buff which is a string containing test name arguments and outpath name
//Returns – return a pointer to argu structure

argu *CreateAndFillArgument(char **buff) {
	argu *head = NULL;
	char *tname = NULL, **args = NULL, *outpath = NULL, *token = NULL, *d_line = NULL, *res = NULL;
	int j = 0, arg_num = 0;
	head = (argu *)malloc(sizeof(argu));

	args = (char**)malloc(MAX_ARG * sizeof(char*));
	for (j = 0; j < MAX_ARG; j++) {
		*(args + j) = (char*)malloc(MAX_ARG * sizeof(char));
	}

	token = strtok(buff, " ");// read test name
	char **cur = args;
	res = token;

	strcpy(head->tname, token);
	while ((token = strtok(NULL, " ")) != NULL)
	{
		res = token;
		if ((d_line = strchr(res, '\n')) != NULL)
		{
			*d_line = '\0';
			strcpy(head->outpath, token);

		}
		strcpy(*cur, token);
		cur++;
		arg_num++;
	}
	head->args = args;
	head->arg_num = arg_num - 1;
	head->res = 0;
	return head;

}

//Description –Frees an argu, and all the inner arguments that we also allocated memory for
//Parameters – indirect reference to argu strucutre array and number of items in the argu array
//Returns – nothing
void FreeArgs(argu **head, int thread_num)
{
	int i = 0, j =0,arg_num=0;
	char **inner_arg =NULL, cur=NULL;
	for (i = 0; i < thread_num; i++)
	{
		arg_num = (*(head + i))->arg_num;
		inner_arg = (*(head+i))->args;
		for(j=0;j< arg_num;j++ )
		{
			free(*(inner_arg + j));
		}
		free((*(head + i))->args);
		free(*(head + i));
	}
	free(head);
	
}
//Description –prints to file the error type according to results and exitcode inside the array of argu structures
//Parameters – file path to write to, number of items inside the argu array, an integer to count the loop with, and a pointer to an argu structure array
//Returns – returns zero if succeeded
int PrintErrorType(argu **arguments_array, int i,int thread_idx, char filepath[])
{
	FILE *fp_write = NULL;
	fopen_s(&fp_write, filepath, "w+");
	if (fp_write == NULL) return FAILED;
	for (i = 0; i < thread_idx; i++)
	{

		if (2 == arguments_array[i]->res)
			fprintf(fp_write, "test #%d : Timed Out", i + 1);
		else {
			if (0 == arguments_array[i]->res)
				fprintf(fp_write, "test #%d : Succeeded", i + 1);
			if (1 == arguments_array[i]->res)
				fprintf(fp_write, "test #%d : Failed", i + 1);
			if (0 != arguments_array[i]->exitc)
				fprintf(fp_write, "test #%d : Crashed %d", i + 1, arguments_array[i]->exitc);
		}
		if (thread_idx - 1 != i) {
			fprintf(fp_write, "\n");
		}
	}
	fclose(fp_write);
	return SUCCEEDED; // succeeded
}
//Description –reads from file, creates argu strucutres and inserts them into an array, then fills an array of handles using the create thread simple function. and counts. then closes file stream
/*Parameters –
**buff - pointer for a char array used for fgets to read a line into. 
**head - pointer to an argu struct array
***argment_array - pointer to a pointer of an argu struct array
*threadz used to count the unmber of threads
*thread_idx = used to count indexes for p_thread_handles
*file_path - used inorder to open the right file for reading
**p_thread_handles - a pointer to array of handles, we use it to store handles.
**p_thread_ids - a pointer to an array of DWORD type thread_ids, wwe use it to store the threads' id's
*/
//Returns – returns zero if succeeded. 1 if failed. 
int OpenThreads(char **buff,argu **head, argu ***arguments_array, int *threadz, int *thread_idx, char *file_path, HANDLE **p_thread_handles, DWORD **p_thread_ids, char *file_outpath )
{
	FILE *fp_read = NULL;
	fopen_s(&fp_read, file_path, "r");
	if (fp_read == NULL) return FAILED;

	fgets(buff, MAX_LINE, fp_read);


	while (!feof(fp_read)) {
		
		*head = CreateAndFillArgument(buff);
		strcpy((*head)->main_outpath, file_outpath);
		(*arguments_array)[*thread_idx] = *head;
		
		(*p_thread_handles)[*thread_idx] = CreateThreadSimple(Thread, (*arguments_array)[*thread_idx], &(*p_thread_ids)[*thread_idx], file_outpath);//Pass a pointer to the member of the struct argu (head) as an argument for the thread's routine
	
		*threadz = *threadz + 1;

		*thread_idx = *thread_idx + 1;
		
		if (feof(fp_read))
		{
			break;
		}
		fgets(buff, MAX_LINE, fp_read);
	}

	fclose(fp_read);
	return SUCCEEDED;
}
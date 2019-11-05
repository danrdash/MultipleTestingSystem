#pragma once

//Description –this module is the header file for functions, we included all needed libraries and function declarations
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <windows.h>
#include "Thread.h"

void PrintArguStruct(argu *head);
argu *CreateAndFillArgument(char **buff);
int CountTests(char* file_path, int *test_num);
void FreeArgs(argu **head, int arg_num);
int PrintErrorType(argu **arguments_array, int i, int thread_idx, char filepath[]);
int OpenThreads(char **buff, argu **head, argu ***arguments_array, int *threadz, int *thread_idx, char *file_path, HANDLE **p_thread_handles, DWORD **p_thread_ids, char *file_outpath);
#endif
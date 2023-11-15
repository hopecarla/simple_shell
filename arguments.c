#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_ARGS 64
#define MAX_SIZE_INPUT 1024

/**
 * tokenizecmmd - tokenize a command string into args
 * @command: string to be tokenized
 * @args: array to store
 */
void tokenizecmmd(char *command, char *args[])
{
	char *token;
	int i = 0;

	token = strtok(command, " ");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}

/**
 * executeChild - execute the child process
 * @args: array of arguments for the command
 */

void executeChild(char *args[])
{
	if (execvp(args[0], args) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

/**
 * execute_cmmd - execute multiple commands separated by a newline
 * @command: commands to be executed
 */

void execute_cmmd(char *command)
{
	char *commands[MAX_ARGS];
	char *token;
	int j = 0;
	int k;

	char cmd_copy[MAX_SIZE_INPUT];

	strncpy(cmd_copy, command, sizeof(cmd_copy));
	cmd_copy[sizeof(cmd_copy) - 1] = '\0';

	token = strtok(cmd_copy, "\n");
	while (token != NULL)
	{
		if (strlen(token) > 0)
		{
			commands[j++] = token;
		}
		token = strtok(NULL, "\n");
	}
	commands[j] = NULL;
	for (k = 0; k < j; k++)
	{
		char *args[MAX_ARGS];

		tokenizecmmd(commands[k], args);
		executeChild(args);
	}
}

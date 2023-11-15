#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include "shell.h"

extern int setenv_cmmd(const char *variable, const char *value);
extern int unsetenv_cmmd(const char *variable);

#define MAX_ARGS 64
#define MAX_SIZE_INPUT 1024

/**
 * tokenize_Cmmd - tokenize a command string into args
 * @command: string to be tokenized
 * @args: array to store
 */

void tokenize_Cmmd(char *command, char *args[])
{
	char *token;
	int j = 0;

	token = strtok(command, " ");

	while (token != NULL)
	{
		args[j++] = token;

		token = strtok(NULL, " ");
	}
	args[j] = NULL;
}

/**
 * execute_Child - execute the child process
 * @args: array of arguments for the command
 */
void execute_Child(char *args[])
{
	if (execvp(args[0], args) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

/**
 * execute_single_cmmd - executes a single command
 * @command: command to be executed
 */

void execute_single_cmmd(char *command)
{
	char *args[MAX_ARGS];
	int status;

	pid_t pid = fork();

	tokenize_Cmmd(command, args);

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execute_Child(args);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);

			if (exit_status != 0)
			{
			fprintf(stderr, "custom_shell: %s: Exit status %d\n", args[0], exit_status);
			}
		}
	}
}

/**
 * executeCmmd - execute multiple commands separated by a newline
 * @command: commands to be executed
 */

void executeCmmd(char *command)
{
	{
		char *commands[MAX_ARGS];
		char *token;
		int j = 0;
		int k = 0;

		char command_cpy[MAX_SIZE_INPUT];

		strncpy(command_cpy, command, sizeof(command_cpy) - 1);
		command_cpy[sizeof(command_cpy) - 1] = '\0';

		token = strtok(command_cpy, "\n");

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
			execute_single_cmmd(commands[k]);
		}
	}
}

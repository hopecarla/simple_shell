#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"
#define MAX_INPUT 1024

/**
 * main - entry point of the program
 * Return: 0 on Success, or an error if failure
 */

int main(void)
{
	char *input;
	size_t buffer = MAX_INPUT;
	ssize_t r_bytes;
	int active = isatty(STDIN_FILENO);

	while (1)
	{
	if (active)
	printf("($) ");

	r_bytes = getline(&input, &buffer, stdin);

	if (r_bytes == -1)
	{

		perror("getline");
		exit(EXIT_FAILURE);
	}

		if (r_bytes > 1)
		{
			input[r_bytes - 1] = '\0';

				if (strcmp(input, "exit") == 0)
					break;
				executeCmmd(input);
			}
			free(input);
			input = NULL;

			if (!active)
			break;
		}
		free(input);
		return (0);
}

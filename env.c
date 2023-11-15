#include <stdio.h>
#include "shell.h"
/**
 * Env - Handle the "env" built-in command
 */
void Env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

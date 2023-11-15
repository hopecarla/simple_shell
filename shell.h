#ifndef SHELL_H
#define SHELL_H

extern char **environ;

int setenv_cmmd(const char *variable, const char *value);
int unsetenv_cmmd(const char *variable);
void execute_Child(char *args[]);
void executeCmmd(char *command);
void tokenize_Cmmd(char *command, char *args[]);
void tokenizecmmd(char *command, char *args[]);
void executeChild(char *args[]);
void execute_cmmd(char *command);
void execute_single_cmmd(char *command);
void execute_CmmdwithPath(char *command, char *const args[], char *const environ[]);
void Env(void);
void exit_sh(void);
#endif

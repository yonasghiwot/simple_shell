#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

int _putchar(char c);
void _puts(char *str);
int _strlen(char *s);
char *_strdup(char *str);
char *concat_all(char *name, char *sep, char *value);
char **word_list(char *str, const char *delim);
size_t tokenize(char *str,char *delim);
void execute(char **argv);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
extern char **environ;

/**
 * struct list_path - Linked list containing PATH directories
 * @dir: directory in path
 * @p: pointer to next node
 */
typedef struct list_path
{
	char *dir;
	struct list_path *p;
} list_path;


char *_getenv(const char *name);
list_path *add_node_end(list_path **head, char *str);
list_path *linkpath(char *path);
char *_which(char *filename, list_path *head);

/**
 * struct builtin - pointer to function with corresponding builtin command
 * @name: buildin command
 * @func: execute the buildin command
 */
typedef struct builtin
{
	char *name;
	void (*func)(char **);
} builtin;

void(*checkbuiltin(char **arv))(char **arv);
int _atoi(char *s);
void exit_shell(char **arv);
void env(char **arv);
void freearv(char **arv);
void free_list(list_path *head);


#endif

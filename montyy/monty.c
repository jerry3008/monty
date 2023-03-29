#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "monty.h"

char *intData = NULL;
/**
 * main - entry point for monty interpreter
 * @ac: argument counter
 * @av: argument array
 *
 * Return: 0 or 1
 */
int main(int ac, const char *av[])
{
	char *tok = NULL;
	int lineNum = 0, lines = 0, ch = 0;
	FILE *fd, *fp;
	size_t n = 0;
	char *line = NULL, *code = NULL, *ext;
	stack_t *h = NULL;

	if (ac != 2)
	{
		dprintf(2, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	lineNum = 0;
	fp = fopen(av[1], "r");
	ext = strrchr(av[1], '.');
	if (!fp || !(strcmp(".txt", ext) == 0 || strcmp(".m", ext) == 0))
	{
		dprintf(2, "Error: Can't open file %s\n", av[1]);
		fclose(fp);
		exit(EXIT_FAILURE);
	}
	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (ch == '\n')
			lines++;
	}
	fclose(fp);
	fd = fopen(av[1], "r");
	parse_and_exec_montyFile(fd, line, code, tok, lineNum, n, h);
	fclose(fd);
	free(line);
	return (0);
}
/**
 * parse_and_exec_montyFile - parses and interprets the monty file
 * @fd: file descriptor of monty file
 * @line: buffer to contain each line in monty file
 * @code: opdode to be executed
 * @tok: buffer for each token delimited by whitespace in line
 * @lineNum: current line number
 * @n: size of line
 * @h: head of stack
 *
 * Return: Nothing
 */
void parse_and_exec_montyFile(FILE *fd, char *line, char *code,
		char *tok, int lineNum, size_t n, stack_t *h)
{
	int a = 0;
	void (*execute)(stack_t **stack, unsigned int line_number);

	while (getline(&line, &n, fd) != -1)
	{
		lineNum++;
		tok = strtok(line, " ");
		if (tok[strlen(tok) - 1] == '\n')
			code = strndup(tok, strlen(tok) - 1);
		else
			code = strdup(tok);
		intData = strtok(NULL, " ");
		if (!intData)
			free(intData);
		if (*code == '\0' || *code == '\n' || *code == '#')
		{
			continue;
		}
		else if (strcmp(code, "stack") == 0)
		{
			a = 0;
			continue;
		}
		else if (strcmp(code, "queue") == 0)
		{
			a = 1;
			continue;
		}
		if (a == 0)
			execute = getsfunc(code, lineNum);
		else if (a == 1)
			execute = getqfunc(code, lineNum);
		(*execute)(&h, lineNum);
	}
}

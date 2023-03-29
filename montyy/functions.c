#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "monty.h"


/**
 * getsfunc - receives opcode as input and returns corresponding function
 * @opcode: command
 * @lineNum: current line number
 *
 * Return: function pointer
 */
void (*getsfunc(char *opcode, unsigned int lineNum))(stack_t **, unsigned int)
{
	int i;
	instruction_t ins[16] = {
		{"push", push_stack},
		{"pall", print_stack},
		{"pint", print_head},
		{"pop", pop_head},
		{"nop", nop},
		{"swap", swap_head},
		{"add", add_head},
		{"sub", sub_head},
		{"div", div_head},
		{"mul", mul_head},
		{"mod", mod_head},
		{"pchar", print_head_as_char},
		{"pstr", pstr_head},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};
	void (*func)(stack_t **, unsigned int);

	for (i = 0; i < 15; i++)
	{
		if (strcmp(opcode, ins[i].opcode) == 0)
			break;
	}
	if (i == 15)
	{
		dprintf(2, "L%u: unknown instruction %s\n", lineNum, opcode);
		exit(EXIT_FAILURE);
	}
	func = *(ins[i].f);
	return (func);
}
/**
 * getqfunc - receives opcode as input and returns corresponding function
 * @opcode: command
 * @lineNum: current line number
 *
 * Return: function pointer
 */
void (*getqfunc(char *opcode, unsigned int lineNum))(stack_t **, unsigned int)
{
	int i;
	instruction_t ins[16] = {
		{"push", push_stack},
		{"pall", print_stack},
		{"pint", print_head},
		{"pop", pop_head},
		{"nop", nop},
		{"swap", swap_head},
		{"add", add_head},
		{"sub", sub_head},
		{"div", div_head},
		{"mul", mul_head},
		{"mod", mod_head},
		{"pchar", print_head_as_char},
		{"pstr", pstr_head},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};
	void (*func)(stack_t **, unsigned int);

	for (i = 0; i < 15; i++)
	{
		if (strcmp(opcode, ins[i].opcode) == 0)
			break;
	}
	if (i == 15)
	{
		dprintf(2, "L%u: unknown instruction %s\n", lineNum, opcode);
		exit(EXIT_FAILURE);
	}
	func = *(ins[i].f);
	return (func);
}
/**
 * add_to_stack - adds a new node to the beginning of the stack
 * @head: head of stack
 * @n: integer data for new node
 *
 * Return: Nothing
 */
void add_to_stack(stack_t **head, const int n)
{
	stack_t *new;

	new = (stack_t *)malloc(sizeof(stack_t));
	if (new == NULL)
	{
		dprintf(2, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new->prev = NULL;
	new->n = n;
	new->next = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		(*head)->prev = new;
		*head = new;
	}
}
/**
 * add_to_queue - adds a new node to the end of the queue
 * @head: head of queue
 * @n: integer data
 *
 * Return: Nothing
 */
void add_to_queue(stack_t **head, const int n)
{
	stack_t *new, *temp;

	new = (stack_t *)malloc(sizeof(stack_t));
	if (new == NULL)
	{
		dprintf(2, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	temp = *head;
	new->n = n;
	new->next = NULL;
	if (*head == NULL)
	{
		new->prev = NULL;
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		new->prev = temp;
		temp->next = new;
	}
}
/**
 * print_stack - prints the elements of a stack
 * @h: head of linked list
 * @lineNum: current line number
 *
 * Return: number of elements in list
 */
void print_stack(stack_t **h, unsigned int lineNum)
{
	stack_t *current;

	if (*h == NULL || h == NULL)
		return;
	if (lineNum)
		current = *h;
	current = *h;
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}


/**
 * print_head - prints the element at the top of a stack
 * @h: head of linked list
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void print_head(stack_t **h, unsigned int lineNum)
{
	int d = 0;
	stack_t *temp;

	temp = *h;
	while (temp != NULL)
	{
		d++;
		temp = temp->next;
	}
	if (d == 0)
	{
		dprintf(2, "L%u: can't pint, stack empty\n", lineNum);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%d\n", (*h)->n);
	}
}
/**
 * swap_head - swaps the top two elements of the stack
 * @h: head of stack
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void swap_head(stack_t **h, unsigned int lineNum)
{
	int d = 0;
	stack_t *current, *h2;

	current = *h;
	while (current != NULL)
	{
		d++;
		current = current->next;
	}
	if (d < 2)
	{
		dprintf(2, "L%u: Can't swap, stack too short\n", lineNum);
		exit(EXIT_FAILURE);
	}
	h2 = (*h)->next;
	d = (*h)->n;
	(*h)->n = h2->n;
	h2->n = d;
}
/**
 * pop_head -  removes the top element of the stack
 * @h: head of stack
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void pop_head(stack_t **h, unsigned int lineNum)
{
	stack_t *del;

	if (*h == NULL)
	{
		dprintf(2, "L%u: can't pop an empty stack\n", lineNum);
		exit(EXIT_FAILURE);
	}
	del = *h;
	if ((*h)->next  == NULL)
		*h = NULL;
	else
	{
		*h = (*h)->next;
		(*h)->prev = NULL;
	}
	free(del);
}
/**
 * add_head - adds the top two elements of the stack
 * @h: head of stack
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void add_head(stack_t **h, unsigned int lineNum)
{
	stack_t *temp, *h2;
	int i = 0;

	temp = *h;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	if (i < 2)
	{
		dprintf(2, "L%u: can't add, stack to short\n", lineNum);
		exit(EXIT_FAILURE);
	}
	h2 = (*h)->next;
	h2->n += (*h)->n;
	h2->prev = NULL;
	free(*h);
	*h = h2;
}
/**
 * sub_head -  subtracts the top element of the stack from the
 * second top element of the stack
 * @h: head of stack
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void sub_head(stack_t **h, unsigned int lineNum)
{
	stack_t *temp, *h2;
	int i = 0;

	temp = *h;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	if (i < 2)
	{
		dprintf(2, "L%u: can't sub, stack to short\n", lineNum);
		exit(EXIT_FAILURE);
	}
	h2 = (*h)->next;
	h2->n -= (*h)->n;
	h2->prev = NULL;
	free(*h);
	*h = h2;
}
/**
 * div_head - divides the second top element of the stack by
 * the top element of the stack
 * @h: head of stack
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void div_head(stack_t **h, unsigned int lineNum)
{
	stack_t *temp, *h2;
	int i = 0;

	temp = *h;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	if (i < 2)
	{
		dprintf(2, "L%u: can't div, stack to short\n", lineNum);
		exit(EXIT_FAILURE);
	}
	if ((*h)->n == 0)
	{
		dprintf(2, "L%u: division by zero\n", lineNum);
		exit(EXIT_FAILURE);
	}
	h2 = (*h)->next;
	h2->n = h2->n / (*h)->n;
	h2->prev = NULL;
	free(*h);
	*h = h2;
}
/**
 * mul_head -  multiplies the second top element of the stack
 * with the top element of the stack
 * @h: head of stack
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void mul_head(stack_t **h, unsigned int lineNum)
{
	stack_t *temp, *h2;
	int i = 0;

	temp = *h;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	if (i < 2)
	{
		dprintf(2, "L%u: can't mul, stack to short\n", lineNum);
		exit(EXIT_FAILURE);
	}
	h2 = (*h)->next;
	h2->n *= (*h)->n;
	h2->prev = NULL;
	free(*h);
	*h = h2;
}
/**
 * mod_head -  computes the rest of the division of the second
 * top element of the stack by the top element of the stack
 * @h: head of stack
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void mod_head(stack_t **h, unsigned int lineNum)
{
	stack_t *temp, *h2;
	int i = 0;

	temp = *h;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	if (i < 2)
	{
		dprintf(2, "L%u: can't add, stack to short\n", lineNum);
		exit(EXIT_FAILURE);
	}
	if ((*h)->n == 0)
	{
		dprintf(2, "L%u: division by zero\n", lineNum);
		exit(EXIT_FAILURE);
	}
	h2 = (*h)->next;
	h2->n = h2->n % (*h)->n;
	h2->prev = NULL;
	free(*h);
	*h = h2;
}
/**
 * print_head_as_char -  prints the char at the top of
 * the stack followed by a new line
 * @h: head of linked list
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void print_head_as_char(stack_t **h, unsigned int lineNum)
{
	int d = 0;
	stack_t *temp;

	temp = *h;
	while (temp != NULL)
	{
		d++;
		temp = temp->next;
	}
	if (d == 0)
	{
		dprintf(2, "L%u: can't pint, stack empty\n", lineNum);
		exit(EXIT_FAILURE);
	}
	else if ((*h)->n < 0 || (*h)->n > 127)
	{
		dprintf(2, "L%u: can't pchar, value out of range\n", lineNum);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%c\n", (*h)->n);
	}
}
/**
 * pstr_head - prints the  string starting at the top of the stack,
 * followed by a new line
 * @h: head of linked list
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void pstr_head(stack_t **h, unsigned int lineNum)
{
	int d = 0;
	stack_t *temp;

	if (lineNum)
		temp = *h;
	temp = *h;
	while (temp != NULL)
	{
		d++;
		temp = temp->next;
	}
	if (d != 0)
	{
		temp = *h;
		while (temp != NULL)
		{
			if (temp->n == 0 || temp->n < 0 || temp->n > 127)
				return;
			printf("%c", temp->n);
		}
		temp = temp->next;
	}
	printf("\n");
}
/**
 * rotl - rotates the stack to the top i.e the top element of
 * the stack becomes the last one, and the second top
 * element of the stack becomes the first one
 * @h: head of stack
 * @lineNum: current line number
 *
 * Return nothing
 */
void rotl(stack_t **h, unsigned int lineNum)
{
	stack_t *temp;
	int i;

	if (*h == NULL)
		return;
	if (lineNum)
		temp = *h;
	temp = *h;
	i = temp->n;
	while (temp->next != NULL)
	{
		temp->n = temp->next->n;
		temp = temp->next;
	}
	temp->n = i;
}
/**
 * rotr - rotates the stack to the bottom i.e the last element of
 * the stack becomes the top element of the stack
 * @h: head of stack
 * @lineNum: current line number
 *
 * Return: nothing
 */
void rotr(stack_t **h, unsigned int lineNum)
{
	stack_t *temp;
	int i;

	if (*h == NULL)
		return;
	if (lineNum)
		temp = *h;
	temp = *h;
	while (temp->next != NULL)
		temp = temp->next;
	i = temp->n;
	while (temp->prev != NULL)
	{
		temp->n = temp->prev->n;
		temp = temp->prev;
	}
	temp->n = i;
}
/**
 * nop - does nothing
 * @h: head of stack
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void nop(stack_t **h, unsigned int lineNum)
{
	if (h == NULL)
		exit(EXIT_FAILURE + lineNum);
}
/**
 * push_head - pushes an element to the stack
 * @h: head of stack
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void push_stack(stack_t **h, unsigned int lineNum)
{
	int value;

	if (lineNum)
		value = atoi(intData);
	value = atoi(intData);

	add_to_stack(h, value);
}
/**
 * push_queue - pushes an element to the queue
 * @h: head of queue
 * @lineNum: current line number
 *
 * Return: Nothing
 */
void push_queue(stack_t **h, unsigned int lineNum)
{
	int value;

	if (lineNum)
		value = atoi(intData);
	value = atoi(intData);

	add_to_queue(h, value);
}
/**
 * free_stack - frees a stack
 * @head: linked list to be freed
 *
 * Return: nothing
 */
void free_stack(stack_t *head)
{
	stack_t *temp;

	if (head == NULL)
		return;
	while (head != NULL)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

#ifndef MONTY_H
#define MONTY_H
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;
extern char *intData;
extern void parse_and_exec_montyFile(FILE *fd, char *line, char *code, char *tok, int lineNum, size_t n, stack_t *h);
extern int lineNum;
extern void (*getsfunc(char *opcode, unsigned int lineNum))(stack_t **, unsigned int);
extern void (*getqfunc(char *opcode, unsigned int lineNum))(stack_t **, unsigned int);
extern void add_to_stack(stack_t **head, const int n);
extern void add_to_queue(stack_t **head, const int n);
extern void print_stack(stack_t **h, unsigned int lineNum);
extern void print_head(stack_t **h, unsigned int lineNum);
extern void swap_head(stack_t **h, unsigned int linenum);
extern void pop_head(stack_t **h, unsigned int lineNum);
extern void add_head(stack_t **h, unsigned int lineNum);
extern void sub_head(stack_t **h, unsigned int lineNum);
extern void div_head(stack_t **h, unsigned int lineNum);
extern void mul_head(stack_t **h, unsigned int lineNum);
extern void mod_head(stack_t **h, unsigned int lineNum);
extern void print_head_as_char(stack_t **h, unsigned int lineNum);
extern void pstr_head(stack_t **h, unsigned int lineNum);
extern void rotl(stack_t **h, unsigned int lineNum);
extern void rotr(stack_t **h, unsigned int lineNum);
extern void nop(stack_t **h, unsigned int lineNum);
extern void push_stack(stack_t **h, unsigned int lineNum);
extern void push_queue(stack_t **h, unsigned int lineNum);
extern void free_stack(stack_t *head);
#endif

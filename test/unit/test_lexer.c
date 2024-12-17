#include "../../includes/minishell.h"
#include <stdio.h>
#include <assert.h>

void	test_lexer(void)
{
	t_list	*list;

	printf("\nTest1: Simple test\n");
	list = lexer("ls -l");
	print_tokens(list);
	assert(list != NULL);
	assert(ft_lstsize(list) == 2);
	ft_lstclear(&list, free_list);
}

int	main(void)
{
	printf("Unit tests: Lexer\n");
	test_lexer();
	printf("Lexer tests completed\n");
	return (0);
}

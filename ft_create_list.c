#include "minishell.h"
#include <string.h>

void print_list (t_node **lst)
{
	while (*lst)
	{
		printf("content: %s\n", (*lst)->content);
		printf("single_quoted: %d\n", (*lst)->single_quoted);
		printf("double_quoted: %d\n", (*lst)->double_quoted);
		printf("pipe: %d\n", (*lst)->pipe);
		printf("dollar: %d\n", (*lst)->dollar);
		printf("redirection: %d\n", (*lst)->redirection);
		//printf("previous: %s\n", (*lst)->previous->content);
		//printf("next: %s\n", (*lst)->next->content);
		printf("==============================\n");
	}
}

t_node	*ft_new_node(char *content)
{
	t_node *ret;

	ret = malloc(sizeof (t_node));
	memset(ret, 0, sizeof(t_node));
	if (!ret)
		return NULL;
	ret->content = content;
	return (ret);
}

void	ft_add_node_back(t_node **node, t_node *new)
{
	t_node *head;

	head = NULL;
	if (*node)
	{
		head = *node;
		while((*node)->next)
			(*node) = (*node)->next;
		new->previous = *node;
		(*node)->next = new;
		(*node) = head;
	}
	else
		(*node) = new;
}
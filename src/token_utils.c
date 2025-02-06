#include "minishell.h"

t_token	*new_token(char *token, char *backup_token, int token_type, int token_status)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = token;
	node->backup_token = backup_token;
	node->var_exists = false;
	node->type = token_type;
	node->status = token_status;
	node->join = false;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	add_token(t_token **lst, t_token *token)
{
	t_token	*start;

	start = *lst;
	if (start == NULL)
	{
		*lst = token;
		return ;
	}
	if (lst && *lst && token)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = token;
		token->prev = start;
	}
}

void	delete_token(t_token *lst, void (*del)(void *))
{
	if (del && lst && lst->token)
	{	
		(*del)(lst->token);
		lst->token = NULL;
	}
	if (del && lst && lst->backup_token)
	{	
		(*del)(lst->backup_token);
		lst->backup_token = NULL;
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	free_ptr(lst);
}

void	clear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		delete_token(*lst, del);
		*lst = tmp;
	}
}

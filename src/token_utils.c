#include "minishell.h"

t_token	*new_token(char *token, char *backup_token, int type, int status)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = token;
	node->str_backup = backup_token;
	node->var_exists = false;
	node->type = type;
	node->status = status;
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
		*lst = new_node;
		return ;
	}
	if (lst && *lst && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

void	delete_token(t_token *lst, void (*del)(void *))
{
	if (del && lst && lst->str)
	{	
		(*del)(lst->str);
		lst->str = NULL;
	}
	if (del && lst && lst->str_backup)
	{	
		(*del)(lst->str_backup);
		lst->str_backup = NULL;
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
		lstdelone_token(*lst, del);
		*lst = tmp;
	}
}

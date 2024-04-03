/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_make_environ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:08:05 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/04/01 12:22:21 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_environ	*new_list(char *envp)
{
	t_environ	*new;
	char		**tmp;

	new = malloc(sizeof(t_environ));
	if (!new)
		function_error("malloc");
	tmp = ft_split(envp, '=');
	new->key = tmp[0];
	new->value = tmp[1];
	new->next = NULL;
	free(tmp);
	return (new);
}

bool	ft_search_pwd(char **envp)
{
	int		i;

	i = 0;
	if (envp == NULL)
		return (false);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD", 3) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	list_add_back(t_environ **list, t_environ *new)
{
	t_environ	*head;

	head = *list;
	while (head->next != NULL)
		head = head->next;
	head->next = new;
}

t_environ	*create_list(void)
{
	t_environ	*list;
	t_environ	*new;
	t_environ	*next_new;
	char		new_pwd[PATH_MAX];

	list = NULL;
	list = malloc(sizeof(t_environ));
	if (!list)
		function_error("malloc");
	list->key = x_strdup("OLDPWD");
	list->value = x_strdup("\\");
	new = malloc(sizeof(t_environ));
	new->key = x_strdup("PWD");
	new->value = x_strdup(getcwd(new_pwd, sizeof(new_pwd)));
	new->next = NULL;
	list->next = new;
	next_new = malloc(sizeof(t_environ));
	if (!next_new)
		function_error("malloc");
	next_new->key = x_strdup("SHLVL");
	next_new->value = x_strdup("1");
	next_new->next = NULL;
	new->next = next_new;
	return (list);
}

t_environ	*make_environ(char **envp)
{
	t_environ	*list;
	t_environ	*copy_pwd;
	t_environ	*current;

	list = NULL;
	if (ft_search_pwd(envp) == false)
		list = create_list();
	if (list == NULL)
		list = new_list(*envp++);
	while (*envp)
	{
		list_add_back(&list, new_list(*envp));
		envp++;
	}
	copy_pwd = malloc(sizeof(t_environ));
	if (!copy_pwd)
		function_error("malloc");
	copy_pwd->key = x_strdup("COPYPWD");
	current = list;
	while (ft_strcmp(current->key, "PWD") != 0)
		current = current->next;
	copy_pwd->value = x_strdup(current->value);
	list_add_back(&list, copy_pwd);
	return (list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/09 14:35:54 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/08/10 13:58:27 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_option(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	 || (c >= '0' && c <= '9'))
	 	return (OPTION);
}


int	lexer_word(char c)
{
	if (c == '%' || c == '=' || c == '+' || c == 34 || c == 39 || c == 92 \
	 || c == '$' || c == '/' || c == '$' || c == '_' || c == '-' || c == '.' \
	 || c == '?' || c == '*' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	 || (c >= '0' && c <= '9'))
		return(WORD);
}

void	list_print(t_node *list)
{
	while (list)
	{
		printf("\n%s - ", list->content);
		printf("%d\n\n", list->token);
		list = list->next;
	}
}

void	list_print_command(t_node *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("\ncontent %d:  ", i);
		printf("%s", list->content);
		printf("\ntoken %d:  ", i);
		printf("%d\n", list->token);
		list = list->next;
		i++;
	}
}

static int	find_token(char *split)
{
	if (split[0] == '-' && split[1] != '\0')
		return (lexer_option(split[1]));
	if (split[0] == '<' && split[1] == '\0')
		return (LESS);
	if (split[0] == '>' && split[1] == '\0')
		return (GREAT);
	if (split[0] == '|' && split[1] == '\0')
		return (PIPE);
	if (split[0] == '&' && split[1] == '\0')
		return (AMPERSAND);
	if (split[0] == 92 && split[1] == 'n' && split[2] == '\0')
		return (NEWLINE);
	if (split[0] == '>' && split[1] == '>' && split[2] == '\0')
		return (GREATGREAT);
	if (split[0] == '>' && split[1] == '&' && split[2] == '\0')
		return (GREATAMPERSAND);
	else
		return (lexer_word(split[0]));
}


void	lexer(char **split, char **envp)
{
	t_node			*list;
	t_node			*temp;

	int				i;
	int				k;

	list = create_list(split[0]);
	i = 1;
	while (split[i] != '\0')
	{
		lstadd_back(&list,split[i], 0);
		i++;
	}
	i = 0;
	temp = list;
	while (temp != NULL)
	{
		temp->token = find_token(split[i]);
		temp = temp->next;
		i++;
	}
	make_command_table(list, envp);
	make_command_table_pipe(list, envp);
}
	
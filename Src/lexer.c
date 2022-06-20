/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/09 14:35:54 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/06/20 14:02:06 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lexer_option(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	 || (c >= '0' && c <= '9'))
	 	return ("OPTION");
}


char	*lexer_word(char c)
{
	if (c == '%' || c == '=' || c == '+' || c == 34 || c == 39 || c == 92 \
	 || c == '$' || c == '/' || c == '$' || c == '_' || c == '-' || c == '.' \
	 || c == '?' || c == '*' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	 || (c >= '0' && c <= '9'))
		return("WORD");
}

void	list_print(t_node *list)
{
	while (list)
	{
		printf("\n%s - ", list->content);
		printf("%s\n\n", list->token);
		list = list->next;
	}
}


static char	*find_token(char *split)
{
	int 			i;
	char			*lexer_token;

	i = 0;
	while (split[i] != '\0')
	{
		if (split[0] == '-' && split[1] != '\0')
		{
			lexer_token = lexer_option(split[1]);
			break;
		}
		if (split[0] == '<' && split[1] == '\0')
			lexer_token = ft_strdup("LESS");
		if (split[0] == '>' && split[1] == '\0')
			lexer_token = ft_strdup("GREAT");
		if (split[0] == '|' && split[1] == '\0')
			lexer_token = ft_strdup("PIPE");
		if (split[0] == '&' && split[1] == '\0')
			lexer_token = ft_strdup("AMPERSAND");
		if (split[0] == 92 && split[1] == 'n' && split[2] == '\0')
		{
			lexer_token = ft_strdup("NEWLINE");
			break;
		}
		if (split[0] == '>' && split[1] == '>' && split[2] == '\0')
			lexer_token = ft_strdup("GREATGREAT");
		if (split[0] == '>' && split[1] == '&' && split[2] == '\0')
			lexer_token = ft_strdup("GREATAMPERSAND");
		else
			lexer_token = lexer_word(split[i]);
		i++;
	}
	return(lexer_token);
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
		lstadd_back(&list,split[i]);
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
	list_print(list);
	commands(split, envp);
}
	
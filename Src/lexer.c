/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/09 14:35:54 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/06/13 12:39:49 by qfrederi      ########   odam.nl         */
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
		printf("%s\n", list->content);
		printf("%s\n\n", list->token);
		list = list->next;
	}
}


void	lexer()
{
	char			*input;
	t_node			*list;
	char			**split;
	char			*lexer_token;
	int				i;
	int				k;

	i = 0;
	input = readline("Minishell QR1.0: ");
	split = ft_split(input, ' ');
	list = create_list(split[0]);

	while (split[i] != '\0')
	{
		if (i != 0)
		{
			lstadd_back(&list,split[i]);
		}
		k = 0;
		while(split[i][k] != '\0')
		{
			if (split[i][0] == '-' && split[i][1] != '\0')
				lexer_token = lexer_option(split[i][k]);
			if (split[i][0] == '<' && split[i][1] == '\0')
				lexer_token = ft_strdup("LESS");
			if (split[i][0] == '>' && split[i][1] == '\0')
				lexer_token = ft_strdup("GREAT");
			if (split[i][0] == '|' && split[i][1] == '\0')
				lexer_token = ft_strdup("PIPE");
			if (split[i][0] == '&' && split[i][1] == '\0')
				lexer_token = ft_strdup("AMPERSAND");
			if (split[i][0] == 92 && split[i][1] == 'n' && split[i][2] == '\0')
			{
				lexer_token = ft_strdup("NEWLINE");
				break;
			}
			if (split[i][0] == '>' && split[i][1] == '>' && split[i][2] == '\0')
				lexer_token = ft_strdup("GREATGREAT");
			if (split[i][0] == '>' && split[i][1] == '&' && split[i][2] == '\0')
				lexer_token = ft_strdup("GREATAMPERSAND");
			else
				lexer_token = lexer_word(split[i][k]);
			k++;
		}
		// list->token = lexer_token;
		i++;		
	}
	printf("%s\n\n", lexer_token);
	list_print(list);
}
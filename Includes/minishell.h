/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:42:30 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/06/20 14:59:54 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>

typedef struct s_node
{
	char			*content;
	char			*token;

	struct s_node	*next;
}	t_node;

void	lexer();
char	*lexer_option(char c);
char	*lexer_word(char c);

void	make_command_table(t_node *list);

void	list_print(t_node *list);
void	list_print_command(t_node *list);

t_node	*create_head(char *first);
void	lstadd_back(t_node **lst, char *split);
t_node	*create_list(char *head);

#endif

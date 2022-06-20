/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:42:30 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/06/20 11:17:34 by rharing       ########   odam.nl         */
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

typedef struct s_simple_command
{
	int		number_of_available_arguments;
	int		number_of_arguments;
	char	**arguments;
	struct	s_simple_command		*next;
}               t_simple_command;

typedef struct command_table
{
	int					number_of_available_simplecommands;
	int					number_of_simplecommands;
	t_simple_command	**simple_commands;
	char				*outfile;
	char				*inputfile;
	char				*errfile;
}				command_table;

typedef struct s_node
{
	char			*content;
	char			*token;

	struct s_node	*next;
}	t_node;

void	lexer();
char	*lexer_option(char c);
char	*lexer_word(char c);

void	lstadd_back(t_node **lst, char *split);
t_node	*create_list(char *head);

#endif

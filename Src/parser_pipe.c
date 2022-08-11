/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_pipe.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 12:54:35 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/08/10 14:49:58 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  char    *find_word_option(t_node *list, char *string)
{
    string = ft_strjoin(string, list->content);
    string = ft_strjoin(string, " ");
    return (string);
}

static int is_word_command(t_node *list)
{

    if (ft_strncmp("echo", list->content, 4) == 0)
        return(COMMAND);
    else
        return (0);
}

static void    fill_command_table_with_data(t_node *command_table, char *string, int string_token)
{
    if (ft_strncmp(string, "", 1) != 0)
    {
        lstadd_back(&command_table, string, string_token);
    }
}

// t_node  *create_head_parser_pipe(t_node **list, t_node *command_table, int string_token, char *string)
// {
// 	 if (list == NULL)
//         return (NULL);
//     string = ft_strdup("");
// 	while ((*list)->token != PIPE)
// 	{
// 		string = find_word_option(*list, string);
// 		string_token = is_word_command(*list);
// 		if ((*list)->next == NULL)
// 		{
// 			*list = (*list)->next;
// 			break;
//         }
// 		else 
// 			*list = (*list)->next;
// 	}
// 	command_table = create_head(string, string_token);
//     string = NULL;
//     return (command_table);
// }

// void	make_command_table_pipe(t_node *list, char **envp)
// {
// 	t_node	*command_table;
//     char    *string;
//     int     string_token;

//     string = NULL;
//     string_token = 0;
//     command_table = create_head_parser_pipe(&list, command_table, string_token, string);
// 	while (list != NULL)
// 	{
// 		string = ft_strdup("");
//         string_token = 0;
// 		if (list->token == PIPE)
// 		{
// 			if (list->next == NULL)
// 				break;
// 			else
//             	list = list->next;
// 		}
// 		while ((list)->token != PIPE)
// 		{
// 			string = find_word_option(list, string);
// 			string_token = is_word_command(list);
// 			if ((list)->next == NULL)
// 			{
// 				list = (list)->next;
// 				break;
// 			}
// 			else 
// 				list = (list)->next;
// 		}
// 		fill_command_table_with_data(command_table, string, string_token);
// 	}
// 	list_print_command(command_table);
	
// }

t_node  *create_head_parser_pipe(t_node **list, t_node *command_table, int string_token, char *string)
{
	 if (list == NULL)
        return (NULL);
    string = ft_strdup("");
	while ((*list)->token != PIPE)
	{
		if ((*list)->token == LESS)
    	{
			string_token = INFILE;
			*list = (*list)->next;
			string = ft_strjoin(string, (*list)->content);
			string = ft_strjoin(string, " ");
			*list = (*list)->next;
    	}
		if ((*list)->token == GREAT)
		{
			string_token = OUTFILE;
			*list = (*list)->next;
			string = ft_strjoin(string, (*list)->content);
			string = ft_strjoin(string, " ");
			*list = (*list)->next;
    	}
		else
		{
			string = find_word_option(*list, string);
			string_token = is_word_command(*list);
			if ((*list)->next == NULL)
			{
				*list = (*list)->next;
				break;
        	}
			else 
			 	*list = (*list)->next;
		}
	}
	command_table = create_head(string, string_token);
    string = NULL;
    return (command_table);
}

void	make_command_table_pipe(t_node *list, char **envp)
{
	t_node	*command_table;
    char    *string;
    int     string_token;

    string = NULL;
    string_token = 0;
    command_table = create_head_parser_pipe(&list, command_table, string_token, string);

	while (list != NULL)
	{
		string = ft_strdup("");
        string_token = 0;
		if (list->token == PIPE)
		{
			if (list->next == NULL)
				break;
			else
            	list = list->next;
		}
		while (list->token != PIPE)
		{
			if (list->token == LESS)
			{
				string_token = INFILE;
				list = (list)->next;
				string = ft_strjoin(string, list->content);
				string = ft_strjoin(string, " ");
				list = (list)->next;
				// break;
			}
			if ((list)->token == GREAT)
			{
				string_token = OUTFILE;
				list = (list)->next;
				string = ft_strjoin(string, list->content);
				string = ft_strjoin(string, " ");
				list = (list)->next;
			}
			else
			{
				string = find_word_option(list, string);
				string_token = is_word_command(list);
				if (list->next == NULL)
				{
					list = (list)->next;
					break;
				}
				else
					list = (list)->next;
			}
		}
		fill_command_table_with_data(command_table, string, string_token);
	}
	list_print_command(command_table);

}



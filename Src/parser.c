/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 13:59:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/06/27 17:23:26 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_command_table(t_node *list, char **envp)
{
	t_node	*command_table;
    char    *string;
    char    *string_token;

    if (list != NULL)
	{
        string = ft_strdup("");
        string_token = ft_strdup("");
        // printf("token: %s\n", list->token);
        while (list != NULL)
		{
            if (ft_strncmp(list->token, "WORD", 4) == 0 || ft_strncmp(list->token, "OPTION", 6) == 0)
            {
                string = ft_strjoin(string, list->content);
                string = ft_strjoin(string, " ");
                list = list->next;
            }
            else if (ft_strncmp(list->token, "LESS", 4) == 0)
            {
                // string = ft_strjoin(string, list->content);
                string_token = ft_strdup("INFILE");
                list = list->next;
                string = ft_strjoin(string, list->content);
                list = list->next;
                break;

            }
            else if (ft_strncmp(list->token, "GREAT", 5) == 0)
            {
                // string = ft_strjoin(string, list->content);
                string_token = ft_strdup("OUTFILE");
                list = list->next;
                string = ft_strjoin(string, list->content);
                list = list->next;
                break;

            }
            else
                break;
		}
        command_table = create_head(string, string_token);
        string = NULL;
        string_token = NULL;
	}
    while (list != NULL)
    {
        if (string == NULL)
        {
            string = ft_strdup("");
            string_token = ft_strdup("");
        }
        if (ft_strncmp(list->token, "PIPE", 4) == 0)
            list = list->next;
        while (list)
        {
            if (ft_strncmp(list->token, "WORD", 4) == 0 || ft_strncmp(list->token, "OPTION", 6) == 0)
            {
                string = ft_strjoin(string, list->content);
                string = ft_strjoin(string, " ");
                list = list->next;
                // if (ft_strncmp(list->token, "WORD", 4) != 0 || ft_strncmp(list->token, "OPTION", 6) != 0)
                // {
                //     printf("%s\n %d", list->token, ft_strncmp(list->token, "WORD", 4));
                //     break;
                // }
                if (ft_strncmp(list->token, "GREAT", 4) == 0)
                {
                    break;
                }
            }
            else if (ft_strncmp(list->token, "LESS", 4) == 0)
            {
                // list = list->next;
                // string = ft_strjoin(string, list->content);
                string_token = ft_strdup("INFILE");
                list = list->next;
                string = ft_strjoin(string, list->content);
                list = list->next;
                break;
            }
            else if (ft_strncmp(list->token, "GREAT", 5) == 0)
            {
                string_token = ft_strdup("OUTFILE");
                list = list->next;
                string = ft_strjoin(string, list->content);
                list = list->next;
                break;
            }
            else 
                break;
        }
        if (ft_strncmp(string, "", 1) != 0)
        {
            lstadd_back(&command_table, string, string_token);
            string = NULL;
            string_token = NULL;
        }
    }
	list_print_command(command_table);
	// commands_built(command_table, envp);
    // pipex_start(command_table, envp);
}
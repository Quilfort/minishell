/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 13:59:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/06/22 12:53:31 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_command_table(t_node *list)
{
	t_node	*command_table;
    char    *string;

    if (list != NULL)
	{
        string = ft_strdup("");
        // printf("token: %s\n", list->token);
        while (list != NULL)
		{
            if (ft_strncmp(list->token, "WORD", 4) == 0 || ft_strncmp(list->token, "OPTION", 6) == 0)
            {
                string = ft_strjoin(string, list->content);
                string = ft_strjoin(string, " ");
                // command_table->arguments = ft_strdup(list->content);
                list = list->next;
            }
            else
                break;
		}
        command_table = create_head(string);
        string = NULL;
	}
    while (list != NULL)
    {
        if (string == NULL)
        {
            string = ft_strdup("");
        }
        list = list->next;
        while (list)
        {
            if (ft_strncmp(list->token, "WORD", 4) == 0 || ft_strncmp(list->token, "OPTION", 6) == 0)
            {
                string = ft_strjoin(string, list->content);
                string = ft_strjoin(string, " ");
                list = list->next;
            }
            else 
                break;
        }
        if (ft_strncmp(string, "", 1) != 0)
        {
            lstadd_back(&command_table, string);
            string = NULL;
        }
    }
  
    // printf("string:%s\n", string);
	list_print_command(command_table);
}
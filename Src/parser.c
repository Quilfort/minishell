/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 13:59:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/08/10 14:34:00 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


// 
// https://www.geeksforgeeks.org/enumeration-enum-c/
// gebruiken inplaats van strings volgens job want hij snapte niet waarom we nog haar hadden en niet aller eruit getrokken hebben XD
// 
#include "minishell.h"

static  char    *find_great(t_node *list, char *string, char *string_token)
{
    string = ft_strjoin(string, list->content);
    return (string);
}

static  char    *find_less(t_node *list, char *string, char *string_token)
{
    string = ft_strjoin(string, list->content);
    return (string);
}

static  char    *find_word_option(t_node *list, char *string)
{
    string = ft_strjoin(string, list->content);
    string = ft_strjoin(string, " ");
    return (string);
}

int is_word_command(t_node *list)
{

    if (ft_strncmp("echo", list->content, 4) == 0)
        return(COMMAND);
    else
        return (0);
}

t_node  *create_head_parser(t_node **list, t_node *command_table, int string_token, char *string)
{
    if (list == NULL)
        return (NULL);
    string = ft_strdup("");
   
    if ((*list)->token == LESS)
    {
        string_token = INFILE;
        *list = (*list)->next;
        string = ft_strjoin(string, (*list)->content);
    }
    if ((*list)->token == GREAT)
    {
        string_token = OUTFILE;
        *list = (*list)->next;
        string = ft_strjoin(string, (*list)->content);
    }
    while ((*list)->token == WORD || (*list)->token == OPTION)
    {
        string = find_word_option(*list, string);
        string_token = is_word_command(*list);
        if ((*list)->next != NULL)
             *list = (*list)->next;
        else
        {
             *list = (*list)->next;
            break;
        }


    }
    command_table = create_head(string, string_token);
    string = NULL;
    return (command_table);
}

void    fill_command_table_with_data(t_node *command_table, char *string, int string_token)
{
    if (ft_strncmp(string, "", 1) != 0)
    {
        lstadd_back(&command_table, string, string_token);
        // string = NULL;
        // string_token = NULL;
    }
}

void	make_command_table(t_node *list, char **envp)
{
	t_node	*command_table;
    char    *string;
    int     string_token;

    string = NULL;
    string_token = 0;
    command_table = create_head_parser(&list, command_table, string_token, string);
    while (list != NULL)
    {
        string = ft_strdup("");
        string_token = 0;
        if (list->token == PIPE)
            list = list->next;
        while (list != NULL)
        {
            printf("FILLSTRING: listtoken: %d\n", list->token);
            if (list->token == WORD|| list->token == OPTION)
            {
                while (list->token == WORD || list->token == OPTION)
                {
                    string = find_word_option(list, string);
                    string_token = is_word_command(list);
                    if (list->next != NULL)
                        list = list->next;
                    else
                    {
                        list = list->next;
                        break;
                    }
                }
                break;
            }
            if (list->token == LESS)
            {
                string_token = INFILE;
                list = list->next;
                string = ft_strjoin(string, list->content);
                list = list->next;
                break;
            }
            if (list->token == GREAT)
            {
                string_token = OUTFILE;
                list = list->next;
                string = ft_strjoin(string, list->content);
                list = list->next;
                break;
            }
            break;
        }
        fill_command_table_with_data(command_table, string, string_token);
    }
    printf(".....\n\ncommand: table: \n");
    list_print_command(command_table);
    printf("\n\n..........\n\n");
	// commands_built(command_table, envp);
    // pipex_start(command_table, envp);
}
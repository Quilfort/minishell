/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 13:59:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/08/08 14:21:59 by qfrederi      ########   odam.nl         */
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

char    *is_word_command(t_node *list)
{
    char *string_token;

    if (ft_strncmp("echo", list->content, 4) == 0)
        string_token = ft_strdup("COMMAND");
    else
        string_token = ft_strdup("");
    return (string_token);
}

t_node  *create_head_parser(t_node *list, t_node *command_table, char *string_token, char *string)
{
    if (list == NULL)
        return (NULL);
    string = ft_strdup("");
    string_token = ft_strdup("");
    if (ft_strncmp(list->token, "WORD", 4) == 0 || ft_strncmp(list->token, "OPTION", 6) == 0)
    {
        string = find_word_option(list, string);
        string_token = is_word_command(list);
    }
    else if (ft_strncmp(list->token, "LESS", 4) == 0)
    {
        string_token = ft_strdup("INFILE");
        string = ft_strjoin(string, list->next->content);
    }
    else if (ft_strncmp(list->token, "GREAT", 5) == 0)
    {
        string_token = ft_strdup("OUTFILE");
        string = ft_strjoin(string, list->next->content);
    }
    command_table = create_head(string, string_token);
    string = NULL;
    string_token = NULL;
    return (command_table);
}

void    fill_command_table_with_data(t_node *command_table, char *string, char *string_token)
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
    char    *string_token;

    string = NULL;
    string_token = NULL;
    command_table = create_head_parser(list, command_table, string_token, string);
    printf("head commandtable:%s\n\n\n.....\n", command_table->content);
    if (ft_strncmp(command_table->token, "INFILE", 6) == 0 || ft_strncmp(command_table->token, "OUTFILE", 7) == 0 )
        list = list->next;
    list = list->next;
    while (list != NULL)
    {
        string = ft_strdup("");
        string_token = ft_strdup("");
        if (ft_strncmp(list->token, "PIPE", 4) == 0)
            list = list->next;
        while (list != NULL)
        {
            printf("FILLSTRING: listtoken: %s\n", list->token);
            if (ft_strncmp(list->token, "WORD", 4) == 0 || ft_strncmp(list->token, "OPTION", 6) == 0)
            {
                string = find_word_option(list, string);
                string_token = is_word_command(list);
                list = list->next;
                break;
            }
            if (ft_strncmp(list->token, "LESS", 4) == 0)
            {
                string_token = ft_strdup("INFILE");
                list = list->next;
                string = ft_strjoin(string, list->content);
                list = list->next;
                break;
            }
            if (ft_strncmp(list->token, "GREAT", 5) == 0)
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
        fill_command_table_with_data(command_table, string, string_token);
    }
    printf(".....\n\ncommand: table: \n");
    list_print_command(command_table);
    printf("\n\n..........\n\n");
	// commands_built(command_table, envp);
    // pipex_start(command_table, envp);
}
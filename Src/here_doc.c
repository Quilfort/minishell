/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 10:56:36 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/15 14:29:55 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *env_var_here_doc(char *input, t_envp *env)
{
	char	*output;
	char	*var;
	char	**split;
	int		i;

	i = 0;
	output = ft_strdup("");
	split = ft_split(input, ' ');
	
	while (split[i] != NULL)
	{
		if (split[i][0] == '$')
		{
			var = ft_substr(split[i], 1, ft_strlen(split[i]));
			var = env_var(env, var);
			output = ft_strjoin(output, var);
		}
		else
			output = ft_strjoin(output, split[i]);
			output = ft_strjoin(output, " ");
		i++;	
	}
	return (output);
}

int list_heredoc(t_node **temp, char **pipe_split, int i, t_envp *env)
{
	char	*delimiter;
	char	*input;
	int		flag;
	char	*in_operator;

	in_operator = "<<";
	flag = 0;
	list_word(temp, in_operator);
	if (pipe_split[i][2])
		delimiter = &pipe_split[i][2];
	else if (pipe_split[i + 1] != NULL)
	{
		i++;
		delimiter = pipe_split[i];
	}
	else
		return (i);
	while (flag == 0)
	{
		input = readline("> ");
		if (ft_strncmp(input, delimiter, ft_strlen(input)) == 0 && ft_strlen(input) != 0 \
			&& ft_strlen(delimiter) == ft_strlen(input))
			flag = 1;
		else
		{
			input = env_var_here_doc(input, env);
			(*temp)->heredoc = ft_strjoin((*temp)->heredoc, input);
			(*temp)->heredoc = ft_strjoin((*temp)->heredoc, "\n");
		}
	}
	return (i);
}

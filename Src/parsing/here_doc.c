/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 10:56:36 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/28 15:50:53 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_var_here_doc(char *input, t_envp *env)
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

int	list_heredoc(t_node **temp, char *split, int i, t_envp *env)
{
	char	*delimiter;
	int		flag;
	int		start;
	char	*input;

	flag = 0;
	i = i + 2;
	if (split[i] != ' ')
		start = i;
	else if (split[i] == ' ')
	{
		i++;
		start = i;
	}
	else
		return (i);
	while (split[i] != ' ')
		i++;
	delimiter = ft_substr(split, start, (i - start));
	while (flag == 0)
	{
		input = readline("> ");
		if (input == NULL)
			flag = 1;
		else if (ft_strncmp(input, delimiter, ft_strlen(input)) == 0 && \
			ft_strlen(input) != 0 && ft_strlen(delimiter) == ft_strlen(input))
			flag = 1;
		else
		{
			input = env_var_here_doc(input, env);
			(*temp)->heredoc = ft_strjoin((*temp)->heredoc, input);
			(*temp)->heredoc = ft_strjoin((*temp)->heredoc, "\n");
		}
	}
	if (split[i] == ' ')
			i++;
	return (i);
}

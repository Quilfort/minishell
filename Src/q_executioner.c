// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   executioner.c                                      :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: rharing <rharing@student.42.fr>              +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2022/03/07 12:16:31 by qfrederi      #+#    #+#                 */
// /*   Updated: 2022/08/10 15:36:16 by rharing       ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"

static int	lstsize(t_node *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}


static void	q_preform_cmd(t_node *command_table, char**envp, t_vars *vars)
{
	if (!command_table->command)
		print_error(vars);
	right_path(vars, command_table);
	if (vars->my_path == NULL)
		pexit("nee", 1);
	if (execve(vars->my_path, command_table->command, envp) < 0)
		print_error(vars);
}


// returnd de node met token infile om die door te geven aan open
static char	*q_find_token_infile(t_node *command_table, t_vars *vars)
{
	t_node	*temp;
	
	vars->no_infile = 0;
	temp = command_table;
	while (temp)
	{
		if (ft_strncmp(temp->infile , "", 1) != 0)
			return (temp->infile);
		temp = temp->next;
	}
	vars->no_infile = 1;	
	return ("");
}

// returnd node met token outfile om die door te geven aan open
static char	*q_find_token_outfile(t_node *command_table, t_vars *vars)
{
	t_node	*temp;
	
	vars->no_outfile = 0;
	temp = command_table;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->outfile , "", 1) != 0)
			return (temp->outfile);
		temp = temp->next;
	}
	vars->no_outfile = 1;
	return ("");
}


void	init_pipes(t_vars *vars, int (*fd)[vars->com - 2][2])
{
	int x;

	x = 0;
	while (x < (vars->com - 1))
	{
		if (pipe((*fd)[x]) == -1)
			print_error(vars);
		x++;
	}
}

void	close_pipes(t_vars *vars, int (*fd)[vars->com - 2][2])
{
	int j;

	j = 0;
	while (j < (vars->com - 1))
	{
		close((*fd)[j][0]);
		close((*fd)[j][1]);
		j++;
	}
}

void	first_child(t_vars *vars, t_node *command_table, int (*fd)[vars->com][2], char **envp)
{
	int pid1 = fork();
    if (pid1 < 0) 
        print_error(vars);
    if (pid1 == 0) 
	{
		if(vars->no_infile == 0)
		{
			if (dup2(vars->f1, STDIN_FILENO) == -1)
				print_error(vars);
		}
		dup2((*fd)[0][1], STDOUT_FILENO);
		close_pipes(vars, fd);
        q_preform_cmd(command_table, envp, vars);
    }
}

void	middle_child(t_vars *vars, t_node *command_table, int (*fd)[vars->com][2], char **envp)
{
	int pid = fork();
	if (pid < 0)
		print_error(vars);
	if (pid == 0) 
	{
		dup2((*fd)[vars->com_count - 1][0], STDIN_FILENO);
		dup2((*fd)[vars->com_count][1], STDOUT_FILENO);
		close_pipes(vars, fd);
		q_preform_cmd(command_table, envp, vars);
	}
}

void	last_child(t_vars *vars, t_node *command_table, int (*fd)[vars->com][2], char **envp)
{
    int pid3 = fork();
    if (pid3 < 0)
       print_error(vars);
    if (pid3 == 0) 
	{
		if (vars->no_outfile == 0)
		{
			if (dup2(vars->f2, STDOUT_FILENO) == -1)
				print_error(vars);
		}
        dup2((*fd)[vars->com_count - 1][0], STDIN_FILENO);
		close_pipes(vars, fd);
        q_preform_cmd(command_table, envp, vars);
    }
}

void	ft_wait(t_vars *vars)
{
	int x;

	x = 0;
	while (x < vars->com)
	{
		wait(NULL);
		x++;
	}
}

void	multiple_fork(t_node *command_table, char **envp, t_vars *vars)
{
	int fd[vars->com - 1][2];
	
	vars->com_count = 1;
	init_pipes(vars, &fd);
    find_path(envp, vars);
	first_child(vars, command_table, &fd, envp);
	command_table = command_table->next;
	while (vars->com_count < (vars->com - 1))
	{
		middle_child(vars, command_table, &fd, envp);
		vars->com_count++;
		command_table = command_table->next;
	}
	last_child(vars, command_table, &fd, envp);
	close_pipes(vars, &fd);
	ft_wait(vars);
}

// is er geen outfile en infile en een command dan no_inoutfile functie
void	no_inoutfile(t_node *command_table, char **envp, t_vars *vars)
{
	find_path(envp, vars);
	vars->pid = fork();
	if (vars->pid == -1)
		print_error(vars);
	if (vars->pid == 0)
		q_preform_cmd(command_table, envp, vars);
	else 
		wait(&vars->pid);
}

void	just_infile_fork_process(t_node *command_table, char **envp, t_vars *vars)
{	
	find_path(envp, vars);
	vars->pid = fork();
	if (vars->pid == -1)
		print_error(vars);
	if (vars->pid == 0)
	{
		if (dup2(vars->f1, STDIN_FILENO) == -1)
			print_error(vars);
		q_preform_cmd(command_table, envp, vars);
	}
	else 
		wait(&vars->pid);
}

// is er een infile en 1 command dan  open en justinfilefunctie
// is er een infile en meerdere commands dan open en multiplefork
void	just_infile_multiple_fork_process(t_vars *vars, t_node *command_table, char **envp)
{
	vars->f1 = open(vars->string_infile, O_RDONLY, 0644);
	if (vars->f1 < 0)
		print_error(vars);
	if (vars->com == 1)
		just_infile_fork_process(command_table, envp, vars);
	if (vars->com > 1)
		multiple_fork(command_table, envp, vars);	
	close(vars->f1);
}

void	just_outfile_fork_process(t_node *command_table, char **envp, t_vars *vars)
{	
	find_path(envp, vars);
	vars->pid = fork();
		if (vars->pid == 0)
		{
			if (dup2(vars->f2, STDOUT_FILENO) == -1)
				print_error(vars);
			q_preform_cmd(command_table, envp, vars);
		}
		else 
			wait(&vars->pid);
}

// is er een outfile en 1 command dan open en justoutfilefunctie
// is er een outfile en meerdere commands dan open en multiplefork
void	just_outfile_multiple_fork_process(t_vars *vars, t_node *command_table, char **envp)
{
	vars->f2 = open(vars->string_outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->f2 < 0)
		print_error(vars);
	if (vars->com == 1)
		just_outfile_fork_process(command_table, envp, vars);
	if (vars->com > 1)
		multiple_fork(command_table, envp, vars);	
	close(vars->f2);
}

// is er een infile en outfile en meerdere commands open allebei en multiplefork
void	in_out_file_fork_process(t_vars *vars, t_node *command_table, char **envp)
{
	vars->f1 = open(vars->string_infile, O_RDONLY, 0644);
	if (vars->f1 < 0)
		print_error(vars);
	vars->f2 = open(vars->string_outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->f2 < 0)
		print_error(vars);
	multiple_fork(command_table, envp, vars);
	close(vars->f1);
	close(vars->f2);
}

void	q_pipex_start(t_node *command_table, char **envp)
{
	t_vars	vars;

	vars.string_infile = q_find_token_infile(command_table, &vars);
	vars.string_outfile = q_find_token_outfile(command_table, &vars);
	vars.com = lstsize(command_table);
	if (vars.no_infile == 1 && vars.no_outfile == 1 && vars.com == 1)
		no_inoutfile(command_table, envp, &vars);
	if (vars.no_infile == 1 && vars.no_outfile == 1 && vars.com > 1)
		multiple_fork(command_table, envp, &vars);	
	if (vars.no_infile == 0 && vars.no_outfile == 1)
		just_infile_multiple_fork_process(&vars, command_table, envp);
	if (vars.no_infile == 1 && vars.no_outfile == 0)
		just_outfile_multiple_fork_process(&vars, command_table, envp);
	if (vars.no_infile == 0 && vars.no_outfile == 0)
		in_out_file_fork_process(&vars, command_table, envp);
}

	/*
		de logica:
			-	is er een infile en 1 command dan  open en justinfilefunctie
			- 	is er een infile en meerdere commands dan open en multiplefork
			- 	is er een outfile en 1 command dan open en justoutfilefunctie
			- 	is er een outfile en meerdere commands dan open en multiplefork
			-	is er een infile en outfile en meerdere commands open allebei en multiplefork
			-	is er een infile en outfile en een command open en wat dan??
			-	is er geen outfile en infile en een command dan no_inoutfile functie
			- 	is er geen outfile en infile en meerdere commands dan multiplefork
	*/

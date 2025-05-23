/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:38:41 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/26 22:10:09 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*get_cmd_node(t_ast *ast)
{
	while (ast)
	{
		if (ast->type == COMMAND)
			return (ast);
		ast = ast->next_left;
	}
	return (NULL);
}

int	setup_pipe(t_exec *exec)
{
	if (exec->has_pipe)
	{
		if (pipe(exec->pipefd) < 0)
		{
			ft_dprintf(2, "Giraffeshell: %s: %s\n", "pipe", strerror(errno));
			return (FAIL);
		}
	}
	return (SUCCESS);
}

int	setup_fork(t_exec *exec)
{
	exec->pid = fork();
	if (exec->pid < 0)
	{
		ft_dprintf(2, "Giraffeshell: %s: %s\n", "fork", strerror(errno));
		if (exec->has_pipe)
		{
			if (close(exec->pipefd[0]) == -1)
				perror("close");
			if (close(exec->pipefd[1]) == -1)
				perror("close");
		}
		return (FAIL);
	}
	else
	{
		exec->last_pid = exec->pid;
	}
	return (SUCCESS);
}

void	setup_child_pipe_fds(t_minishell *mshell, t_exec *exec)
{
	if (exec->prev_fd != -1)
	{
		if (safe_dup2(exec->prev_fd, STDIN_FILENO) == FAIL)
		{
			delete_minishell(mshell);
			exit(FAIL);
		}
		if (close(exec->prev_fd) == -1)
			perror("close");
	}
	if (exec->has_pipe)
	{
		if (close(exec->pipefd[0]) == -1)
			perror("close");
		if (safe_dup2(exec->pipefd[1], STDOUT_FILENO) == FAIL)
		{
			delete_minishell(mshell);
			exit(FAIL);
		}
		if (close(exec->pipefd[1]) == -1)
			perror("close");
	}
}

void	setup_parent_pipe_fds(t_minishell *mshell, t_exec *exec)
{
	exec->command_count++;
	mshell->in_child = 0;
	if (exec->prev_fd != -1)
	{
		if (close(exec->prev_fd) == -1)
			perror("close");
	}
	if (exec->has_pipe)
	{
		if (close(exec->pipefd[1]) == -1)
			perror("close");
		exec->prev_fd = exec->pipefd[0];
	}
}

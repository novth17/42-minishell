/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:45:07 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/27 13:43:26 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_cleanup_error(t_minishell *mshell, char *msg)
{
	delete_minishell(mshell);
	perror(msg);
	exit(1);
}

void	exit_error(t_minishell *mshell, char *msg)
{
	if (mshell)
		delete_minishell(mshell);
	ft_dprintf(2, msg);
	exit(2);
}

void	print_error(char *msg, char *token, t_token_type type)
{
	if (token)
		ft_dprintf(2, "%s%s\n", msg, token);
	if (type)
	{
		if (type == REDIR_IN)
			ft_dprintf(2, "%s%s\n", msg, INFILE_ERROR);
		else if (type == REDIR_OUT)
			ft_dprintf(2, "%s%s\n", msg, OUTFILE_ERROR);
		else if (type == REDIR_APPEND)
			ft_dprintf(2, "%s%s\n", msg, APPENDFILE_ERROR);
		else if (type == HERE_DOC)
			ft_dprintf(2, "%s%s\n", msg, HEREDOC_ERROR);
		else if (type == PIPE)
			ft_dprintf(2, "%s%s\n", msg, PIPE_ERROR);
		else
			ft_dprintf(2, UNREACHABLE);
	}
	else if (token == NULL && type == 0)
		ft_dprintf(2, "%s", msg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:06:10 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/27 18:29:22 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	t_minishell	mshell;
	t_ast		*ast;
	t_input		input;

	if (ac != 1)
		exit_error(NULL, AC);
	if (init_minishell(&mshell, envp, &ast, av) != SUCCESS)
		exit_error(&mshell, "Giraffeshell: Initialization failed\n");
	run_minishell(&mshell, &input, &ast);
	delete_minishell(&mshell);
	return (0);
}

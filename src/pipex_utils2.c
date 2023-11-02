/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:00:19 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/02 20:01:19 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(t_info *info, char **cmd)
{
	if (ft_strncmp("cd", cmd[0], 2) == 0 && cmd[0][2] == '\0')
		return (cd(info, cmd));
	else if (ft_strncmp("echo", cmd[0], 4) == 0 && cmd[0][4] == '\0')
		return (echo(cmd));
	else if (ft_strncmp("env", cmd[0], 3) == 0 && cmd[0][3] == '\0')
		return (env(info, cmd));
	else if (ft_strncmp("exit", cmd[0], 4) == 0 && cmd[0][4] == '\0')
		return (exit1(info, cmd));
	else if (ft_strncmp("export", cmd[0], 6) == 0 && cmd[0][6] == '\0')
		return (export(info, cmd));
	else if (ft_strncmp("pwd", cmd[0], 3) == 0 && cmd[0][3] == '\0')
		return (pwd(cmd));
	else if (ft_strncmp("unset", cmd[0], 5) == 0 && cmd[0][5] == '\0')
		return (unset(info, cmd));
	return (COMMAND_NOT_FOUND);
}

int	ft_builtin(t_info *info, t_cmd *node)
{
	int	og_stdout;
	int	status;

	og_stdout = dup(STDOUT);
	status = 0;
	if (node->fd_in != NO_FD && node->fd_in != STDIN)
	{
		if (dup2(node->fd_in, STDIN) < 0)
			return (ft_print_error(REDIR_ERROR));
		close(node->fd_in);
	}
	if (node->fd_out != NO_FD && node->fd_out != STDOUT)
	{
		if (dup2(node->fd_out, STDOUT) < 0)
			return (ft_print_error(REDIR_ERROR));
		close(node->fd_out);
	}
	status = ft_exec_builtin(info, node->command);
	dup2(og_stdout, STDOUT);
	close(og_stdout);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitstatus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:05:47 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 11:20:52 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exitestatus(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	else
	{
		return (WEXITSTATUS(status));
	}
}

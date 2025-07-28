/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitstatus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:05:47 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 09:05:48 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exitestatus(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
		return (128 + WTERMSIG(status));
	}
	else
	{
		return (WEXITSTATUS(status));
	}
}

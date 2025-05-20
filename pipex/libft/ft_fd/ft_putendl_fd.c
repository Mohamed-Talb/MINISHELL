/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:53:51 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:26:30 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 2);
}
// #include <fcntl.h>
// #include <sys/stat.h>

// int main()
// {

//     int fd = open("dscp.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
//     if (fd == -1)
// 	{
//         return (1);
//     }
//     printf("The file descriptor is: %d\n", fd);
//     ft_putendl_fd("hello I am in that file", fd);
//     return (0);
// }
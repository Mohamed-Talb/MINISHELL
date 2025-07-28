/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:38:18 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 10:40:05 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANER_H
# define CLEANER_H

# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cleaner
{
	struct s_cleaner	*next;
	void				*adress;
}						t_cleaner;

t_cleaner				**gethead(void);
void					free_all_adresses(void);
void					ft_free(void *ptr);

#endif
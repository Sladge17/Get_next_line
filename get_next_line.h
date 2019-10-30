/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:10:24 by jthuy             #+#    #+#             */
/*   Updated: 2019/10/02 11:20:30 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# define BUFF_SIZE 32
# define RETURN_ERROR_CURSOR(x) if (!x) return (1);
# define RETURN_FIND_N(x) if (x == 1) return (1);
# define DEFINE_REM(x, y) if ((x = y) == -1) return (-1);
# define RETURN_END_FILE(x, y) if (x || y) return (0);

typedef struct		s_str
{
	int				num;
	char			*str;
	struct s_str	*next;
}					t_str;

int					get_next_line(const int fd, char **line);
int					cursor_position(t_str **head, t_str **cursor, int fd);
t_str				*create_node(int fd);
int					build_unistr(t_str **cursor, char **unistr, char **line);
void				rd_unistr(t_str **cursor, char **unistr);

#endif

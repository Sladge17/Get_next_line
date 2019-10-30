/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:09:50 by jthuy             #+#    #+#             */
/*   Updated: 2019/10/02 11:28:15 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	int				rem;
	char			buf[BUFF_SIZE + 1];
	static t_str	*head;
	t_str			*cursor;
	char			*unistr;

	if (!line || fd == -1 || cursor_position(&head, &cursor, fd))
		return (-1);
	unistr = NULL;
	while (1)
	{
		if (cursor->str == NULL)
		{
			DEFINE_REM(rem, read(fd, buf, BUFF_SIZE));
			if (!rem)
			{
				RETURN_END_FILE(!unistr, *unistr == '\0');
				*line = unistr;
				return (1);
			}
			buf[rem] = '\0';
			cursor->str = ft_strdup(buf);
		}
		RETURN_FIND_N(build_unistr(&cursor, &unistr, line));
	}
}

int		cursor_position(t_str **head, t_str **cursor, int fd)
{
	t_str			*new_node;

	if (!*head)
	{
		*head = create_node(fd);
		RETURN_ERROR_CURSOR(*head);
		*cursor = *head;
		return (0);
	}
	*cursor = *head;
	while ((*cursor)->num != fd)
	{
		if ((*cursor)->next == NULL)
		{
			new_node = create_node(fd);
			RETURN_ERROR_CURSOR(new_node);
			(*cursor)->next = new_node;
			*cursor = new_node;
			break ;
		}
		*cursor = (*cursor)->next;
	}
	return (0);
}

t_str	*create_node(int fd)
{
	t_str			*new_node;

	new_node = (t_str *)malloc(sizeof(t_str));
	if (!new_node)
		return (NULL);
	new_node->num = fd;
	new_node->str = NULL;
	new_node->next = NULL;
	return (new_node);
}

int		build_unistr(t_str **cursor, char **unistr, char **line)
{
	char			*trash;

	if (*unistr == NULL)
		*unistr = ft_strnew(0);
	if (ft_strchr((*cursor)->str, '\n'))
	{
		*(ft_strchr((*cursor)->str, '\n')) = '\0';
		rd_unistr(cursor, unistr);
		trash = (*cursor)->str;
		(*cursor)->str = ft_strdup(ft_strchr((*cursor)->str, '\0') + 1);
		free(trash);
		*line = *unistr;
		return (1);
	}
	rd_unistr(cursor, unistr);
	free((*cursor)->str);
	(*cursor)->str = NULL;
	return (0);
}

void	rd_unistr(t_str **cursor, char **unistr)
{
	char			*trash;

	trash = *unistr;
	*unistr = ft_strjoin(*unistr, (*cursor)->str);
	free(trash);
}

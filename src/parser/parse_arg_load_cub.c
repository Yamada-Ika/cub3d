/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_load_cub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:41 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 01:57:41 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	*join_str(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

static char	*read_to_string(const int fd)
{
	char	*read_line;
	char	*whole_line;

	whole_line = ft_strdup("");
	if (whole_line == NULL)
		return (NULL);
	while (true)
	{
		read_line = get_next_line(fd);
		if (read_line == NULL)
			break ;
		whole_line = join_str(whole_line, read_line);
		if (whole_line == NULL)
			break ;
	}
	return (whole_line);
}

t_error	load_cub(t_config *config, const char *path)
{
	int		fd;
	char	*read_line;
	char	*whole_line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (CUB_FILE_READ_ERR);
	whole_line = read_to_string(fd);
	close(fd);
	if (whole_line == NULL)
		return (MEM_ERR);
	config->cub = ft_split2(whole_line, '\n');
	free(whole_line);
	if (config->cub == NULL)
		return (MEM_ERR);
	return (NO_ERR);
}

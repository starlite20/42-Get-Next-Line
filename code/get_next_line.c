/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssujaude <ssujaude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:17:45 by ssujaude          #+#    #+#             */
/*   Updated: 2025/12/06 19:04:54 by ssujaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



// char *check_linebreak(char *read_so_far)
// {
// 	int i;

// 	i = 0;
// 	while(r(read_so_far[i]!='\n') && (read_so_far[i]!='\0'))
// 		i++;
	
// }

char *get_next_line_process(int fd, char *buffer_line)
{
	int bytes_read;

	bytes_read = read(fd, buffer_line, BUFFER_SIZE);
	if(bytes_read <= 0)
	{	
		free(buffer_line);
		return (NULL);
	}

	return(buffer_line);
}

char *get_next_line(int fd)
{
	static char *buffer_line;

	if(fd == -1)
		return (NULL);

	buffer_line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if(!buffer_line)
	{
		free(buffer_line);
	}

	get_next_line_process(fd, buffer_line);
	// buffer_line = check_linebreak(bytes_read);
	//printf("\n @fd %d => read %d = [%s]\n", fd, bytes_read, buffer_line);
	return(buffer_line);
}

int main()
{
	int fd;
	char *line_read;

	fd = open("longtext.txt", O_RDONLY);
	printf("\n== > file descriptor id : %d\n*****************\n\n", fd);

	if(fd == -1)
		return (0);
	line_read = get_next_line(fd);
	while(line_read)
	{
		printf("\n [%s] ", line_read);
		line_read = get_next_line(fd);
	}

	free(line_read);
	close(fd);

	printf("\n \n== > file closed");
	return(0);
}
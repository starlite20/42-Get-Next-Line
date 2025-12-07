/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssujaude <ssujaude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:17:45 by ssujaude          #+#    #+#             */
/*   Updated: 2025/12/07 17:02:18 by ssujaude         ###   ########.fr       */
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






int has_line_termination(char *text_loaded, int len)
{
	int i;

	i=0;
	while(i < len)
	{
		if((text_loaded[i] == '\n') || (text_loaded[i] == '\0'))
			return(i);
		i++;
	}
	return (-1);
}


char *process_next_line(char *buffer_stash, int fd)
{
	char *active_line;
	int bytes_read;
	int flag_terminator;

	//printf("\n\n\t\t==> gnlp : [[%s]]", buffer_stash);

	bytes_read = read(fd, buffer_stash, BUFFER_SIZE);

	if(bytes_read <= 0)
	{	
		free(buffer_stash);
		return (NULL);
	}

	printf("\n\tS=>[%s]",buffer_stash);
	active_line = ft_strjoin_and_free(active_line, "");

	//verify if \n or \0 is present inside the read data.
	// if(has_line_termination(buffer_stash, bytes_read))
	// 	printf("\n\n\t\t==> this has line terminator");
	flag_terminator = has_line_termination(buffer_stash, bytes_read);
	while (flag_terminator == -1)
	{
		bytes_read = read(fd, buffer_stash, BUFFER_SIZE);
		if(bytes_read <= 0)
		{	
			free(buffer_stash);
			return (NULL);
		}
		active_line = ft_strjoin_and_free(active_line, buffer_stash);
		flag_terminator = has_line_termination(buffer_stash, bytes_read);
	}	

	return(active_line);
}


char *get_next_line(int fd)
{
	static char *buffer_stash;
	char *active_line;
	int bytes_read;

	if(fd == -1)
		return (NULL);

	buffer_stash = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if(!buffer_stash)
		return (NULL);

	active_line = process_next_line(buffer_stash, fd);
	
	return(active_line);
}

int main()
{
	int fd;
	char *line_read;

	fd = open("text.txt", O_RDONLY);
	printf("\n== > file descriptor id : %d\n*****************\n\n", fd);

	if(fd == -1)
		return (0);
	line_read = get_next_line(fd);
	while(line_read)
	{
		printf("\n- [%s] -\n", line_read);
		line_read = get_next_line(fd);
	}

	free(line_read);
	close(fd);

	printf("\n \n== > file closed");
	return(0);
}
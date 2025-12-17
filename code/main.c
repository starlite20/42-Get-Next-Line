#include "get_next_line.h"


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((s1[i] != s2[i]) || (s1[i] == '\0') || (s2[i] == '\0'))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}


int main()
{
	int fd;
	char *line_read = "";
	int ctr;

	ctr = 0;
	fd = open("big_line_with_nl", O_RDONLY);
	printf("\n== > file descriptor id : %d\n*****************\n\n", fd);

	if(fd == -1)
		return (0);
	while(line_read)
	{

		line_read = get_next_line(fd);
		if(line_read)
		{
			// if(ft_strncmp(line_read, "\n", ft_strlen(line_read)) == 0)
			// 	printf("\n passed slash n case");
			// else if(line_read == NULL)
			// 	printf("\n passed NULL");
			// else 			
					ctr++;
				printf("\n ##[%s]", line_read);
			free(line_read);
		}
	}

	close(fd);

	printf("\n \n== > file closed : lines read %d", ctr);
	return(0);
}
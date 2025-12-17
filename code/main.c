#include "get_next_line.h"

int main()
{
	int fd;
	char *line_read = "";

	fd = open("only_nl.txt", O_RDONLY);
	printf("\n== > file descriptor id : %d\n*****************\n\n", fd);

	if(fd == -1)
		return (0);
	while(line_read)
	{
		line_read = get_next_line(fd);
		if(line_read)
		{
			printf("\n ##MAIN## \t\t LINE FOUND - [%s] -\n", line_read);
			free(line_read);
		}
	}

	close(fd);

	printf("\n \n== > file closed");
	return(0);
}
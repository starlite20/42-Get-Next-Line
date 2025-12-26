_This project has been created as part of the 42 curriculum by ssujaude@student.42abudhabi.ae_

# Get Next Line

## Description
__get_next_line__ is a project focused on creating the functionality to be able to read a line from a given file. This is done by reading through the file descriptor, one call at a time. The core of the project lies in managing the state between function calls through the use of a static variable.

The function returns the line extracted based on finding the terminating character. The terminating character are determined by newline character (\n), and  the end of the file. 

Additionally, the code must be handle different buffer sizes efficiently and also, be able to read from different file descriptors.

For the bonus part, the function is enhanced to manage multiple file descriptors at the same time, keeping track of the reading state for each one independently. 

---
---
## Instructions

### Pre-requisite
Before compilation of the code files, create the following files:
- Sample Text file 
- main.c (File containing the main to run the code with the sample text file)
	Sample Main File
	```
	#include "get_next_line.h"
	#include <stdio.h>
	
	int main(void)
	{
		int    fd;
		char  *line;

		fd = open("test.txt", O_RDONLY);
		if (fd == -1)
			return (1);

		line = get_next_line(fd);
		while (line)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd);
		}
		
		close(fd);
		return (0);
	}
	```

### Compilation

The project uses a variable buffer size. Default Buffer size has been set to 5. This can be modified by defining during compilation time using the -D BUFFER_SIZE=n flag. If not provided, default buffer size defined in the code will be used. 

Compilation command sample:
```
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```
Replace 42 with any buffer size you wish to test. 

### Execution 
Sample Main 
Run the executable, by running <code>./a.out</code>

---
---
## Resources
 - man read
 -  Static Variables In C Programming Language (https://www.youtube.com/watch?v=MVeN3GDwjUg)

---
---

## Algorithm and Technical Choices 

The solution is built around a single state-preserving mechanism through static variables. The funcationality is  is handled by three distinct phases helper functions. 

- __State Preservation with a Static Variable__ : The core challenge is to remember data between function calls without using global variables. We need to keep track of how far we read. 

	This is solved using a static char variable named *stashed_data. This helps ensure the value persists across function calls until the current runtime is active. This variable acts as a "stash" for all data read from the file descriptor that has not yet been returned as a line.  

- __The Read Loop__ : As we pass a buffer size to the read function, so that we can read the file in parts, we require a loop. The loop continues to read from the file descriptor into a temporary buffer (temp_reader) as long as the stashed_data does not contain a newline character (\n).
	
	This ensures we read the minimum amount of data required to find the next line. The newly read data is appended to the stashed_data using the <code>ft_str_join_and_free</code> function, which is crucial for preventing memory leaks during this accumulation phase.  

- __Post-Read Processing__ : Once the loop finishes, it means either a newline was found or read returns, which means end of line has been reached, or its an error. This is when we call the <code>post_read_processing</code> function. This function first handles potential read errors by cleaning up the stash and then, if data is available, begins line extraction using the function <code>find_and_extract_line</code>.  

- __Line Extraction and Stash Updation__ : 
	- <code>find_and_extract_line</code>: This function locates the newline character (\n) in the stashed_data. Then, it calls <code>separate_line_from_stash</code> to perform the actual split.
	- <code>separate_line_from_stash</code>: This function takes the stashed_data and a pointer to the newline character and performs two distinct operations:
		- If a newline is found, it allocates and returns the line via the <code>full_line</code> double-pointer. Then, it allocates new memory for the new stashed_data containing everything after the newline, and frees the old stash. At the end, it returns the new stashed data.
		- If no newline is found, it indicates we reached the end of file. It allocates and returns the remaining stashed_data as the final line. It frees the old stash and returns NULL, ensuring the next call to get_next_line will correctly return NULL.
          
- __Bonus Part : Managing Multiple File Descriptors__
	- In order to handle multiple file descriptors, static array of pointers has been utilized. 

	- The core line extraction logic remains identical, but the state preservation mechanism is adapted. Instead of a single static char *, the solution uses: 
	```static char *stashed_data[MAX_FILES];```
  
	- MAX_FILES has been defined as a constant in the header file. The file descriptor (fd) is used directly as an index into this array to store and retrieve the unique stashed_data for each file descriptor. 

---
---
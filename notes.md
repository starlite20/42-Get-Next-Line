# Running Valgrind



Verify if it exists using
valgrind --version

Install Valgrind through
sudo apt update
sudo apt-get install valgrind

Compile your C Program, and retrieve the output file

Run Valgrind Command
valgrind ./outputfile [args]


valgrind --leak-check=full ./myprogram



for me, i had this issue on ubuntu
valgrind: failed to start tool 'memcheck' for platform 'amd64-linux': No such file or directory

Even after several re-installations.
Inorder to resolve, I ran the valgrind commands with sudo permissions, and it works.

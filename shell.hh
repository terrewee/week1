#include <iostream>
#include <unistd.h>  // syscall()
#include <syscall.h> // SysCall nummers
#include <fcntl.h>   // O_RDONLY
#include <vector>
#include <sys/wait.h>
#include <sys/types.h>

int main();
void new_file();
void list();
void find();
void python();
void src();
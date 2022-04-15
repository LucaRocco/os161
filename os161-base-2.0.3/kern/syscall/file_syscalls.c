#include <types.h>
#include <kern/unistd.h>
#include <clock.h>
#include <copyinout.h>  
#include <syscall.h>
#include <lib.h>

int sys_read(int fd, userptr_t buf_ptr, size_t size) {
    int i;
    char* buffer = (char*)buf_ptr;

    if (fd != STDIN_FILENO)
    {
        kprintf("Only stdout and stdin are supported");
        return -1;
    }

    for (i = 0; i < (int)size; i++)
    {
        buffer[i] = getch();
        if (buffer[i] < 0)
        {
            return i;
        }
        
    }

    return (int)size;
}

int sys_write(int fd, userptr_t buf_ptr, size_t size) {
    int i;
    char* chars_to_print = (char*)buf_ptr;

    if (fd != STDOUT_FILENO && fd != STDERR_FILENO)
    {
        kprintf("Only stdout and stdin are supported");
        return -1;
    }

    for (i = 0; i < (int)size; i++)
    {
        putch(chars_to_print[i]);
    }

    return (int)size;
}
#include "include/so_long.h"

#include <fcntl.h>   // For open()
#include <stdio.h>   // For printf()
#include <stdlib.h>  // For exit()

int main(int argc, char **argv)
{
    char    *line;
    int     fd;

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return (1);
    }

    // Open the file
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }

    // Read lines using get_next_line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line); // Print the line
        free(line);         // Free the memory allocated for the line
    }

    // Close the file descriptor
    close(fd);
    return (0);
}


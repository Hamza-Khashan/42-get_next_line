*This project has been created as part of the 42 curriculum by hkhashan.*

# Get Next Line

## Description
The **Get Next Line** (GNL) project is a function that reads a single line from a file descriptor (`fd`), one at a time, until the end of the file is reached. The goal of this project is to introduce the concept of static variables in C and to manage dynamic memory allocation efficiently. 

Repeated calls to the `get_next_line` function allow a program to read a text file completely, returning each line ending with a newline character (`\n`), or the remaining text if the file ends without a newline. It handles arbitrary buffer sizes and ensures no memory leaks occur during the reading process.

## Instructions

### Compilation
The project requires the `BUFFER_SIZE` macro to be defined at compile time. This dictates how many bytes the `read()` function will fetch in a single call.

To compile the project files alongside a `main.c` testing file, run:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o test
```

(You can change 42 to any positive integer).

### Usage
Include the header in your C file:
```bash
C
#include "get_next_line.h"
```
Example main.c execution:
```bash
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); // Ensure you free the returned line!
    }
    close(fd);
    return (0);
}
```
Run the compiled executable:

```Bash
./test
```
## Algorithm Explanation & Justification
### The Algorithm
The project uses a Chunk-Based Reading and Static Accumulation Algorithm.

Reading: The function uses read() to fetch chunks of data of size BUFFER_SIZE into a temporary buffer.

Accumulation: It joins this newly read chunk onto a static char *leftover string.

Checking: After every read, it checks if a newline character (\n) exists in the leftover string. If not, it loops and reads again.

Extraction: Once a \n is found (or EOF is reached), the algorithm splits the leftover string into two parts:

The line to be returned (everything up to and including the \n).

The new leftover string (everything strictly after the \n), which is saved for the next time the function is called.

### Justification
This approach was selected because the length of a line is unpredictable, and read() does not stop automatically at \n. We must read arbitrary byte chunks based on BUFFER_SIZE.

Why a static variable? Global variables are forbidden. A static variable is the only standard C mechanism to persist data (the remaining characters read past the newline) across multiple function calls.

Why dynamic extraction? By dynamically allocating strings and immediately freeing the old static pointer once updated, the algorithm remains strictly leak-free, regardless of whether BUFFER_SIZE is 1 or 10,000,000.

## Resources
### References:

man 2 read – System call for reading from a file descriptor.

man 3 malloc / man 3 free – Dynamic memory management.

C Static Variables Explained – Understanding scope and lifetime of static variables.

### AI Usage:
AI was utilized during the development of this project for the following tasks:

Debugging Memory Leaks: AI assisted in analyzing the custom ft_strjoin function to identify why the previous leftover string was not being freed, and how to safely pass an uninitialized static pointer (NULL) into string manipulation functions.

Edge Case Analysis: Used to clarify the expected behavior of EOF without a terminating newline character, ensuring the returned string format perfectly aligned with the project subject requirements.

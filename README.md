# Get Next Line

*This project has been created as part of the 42 curriculum by aouassar*

## Description

A function that reads and returns one line at a time from a file descriptor. The main challenge is efficiently managing a static variable to preserve data between function calls when the buffer doesn't align with line boundaries.

**Key learnings:** static variables, memory management, file I/O with `read()`, and buffer handling.

## Compilation & Usage

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Test with different buffer sizes by changing the `BUFFER_SIZE` value (try 1, 42, 9999).

### Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd = open("test.txt", O_RDONLY);
    char    *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Algorithm

**Core concept:** Use a static variable to store leftover data between function calls.

1. Read BUFFER_SIZE bytes and append to static buffer
2. Search for `\n` in the buffer
3. Extract line (up to and including `\n`) and return it
4. Keep remainder in static buffer for next call
5. At EOF, return remaining data or NULL if empty

**Why static?** It persists between calls, allowing the function to "remember" leftover data when a read operation captures more than one line or only part of a line.

### Function Prototype
```c
char *get_next_line(int fd);
```
- Returns next line (with `\n` if present), or NULL at EOF/error
- Uses: `read()`, `malloc()`, `free()`

## Files

**Mandatory:**
- `get_next_line.c` - Main function
- `get_next_line_utils.c` - Helper functions  
- `get_next_line.h` - Header file

**Bonus:**
- `get_next_line_bonus.c`
- `get_next_line_utils_bonus.c`
- `get_next_line_bonus.h`

Bonus handles multiple file descriptors simultaneously with one static variable (array indexed by FD).

## Resources

**Documentation:** [read(2) man page](https://man7.org/linux/man-pages/man2/read.2.html), static variables in C

**AI Usage:** Used for understanding concepts (static variables, file I/O), debugging, and documentation. Not used for writing the complete solution—learning came from hands-on implementation, testing, and peer discussion.

## Constraints

- **Allowed:** `read()`, `malloc()`, `free()`, one static variable
- **Forbidden:** `libft`, `lseek()`, global variables
- **Compilation:** `-Wall -Wextra -Werror -D BUFFER_SIZE=n`
- Must follow 42 Norm, no memory leaks, no crashes
- Line includes `\n` (except at EOF without newline)

## Testing

**Key test cases:**
- Various BUFFER_SIZE values (1, 42, 9999)
- Empty files, files without final newline, very long lines
- Multiple FDs (bonus)

**Check for memory leaks:**
```bash
valgrind --leak-check=full ./your_test
```

---

**aouassar** | 42 School

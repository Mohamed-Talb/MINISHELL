/*
                                      WAIT3 FUNCTION
WAIT3 FUNCTION: The `wait3` function is a more advanced version of `wait`, allowing the parent process to wait for child termination while also collecting resource usage information about the child. This function can be useful for monitoring child processes’ resource consumption.

FEATURES:
- Waits for any child process to terminate, like `wait`.
- Collects resource usage information for the terminated child (via `rusage`).
- Provides detailed information about the child's resource consumption (e.g., CPU time, memory usage).

FUNCTION PROTOTYPE:
    pid_t wait3(int *status, int options, struct rusage *rusage);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Parent calls wait3()         Parent waits for a child to terminate and collects resource data.
    Returns child's PID         Returns the PID of the terminated child process.
    Collects resource data      Collects resource usage details (CPU, memory) if requested.
    Options can be used         Options can specify behavior like non-blocking.

USAGE SCENARIOS:
- Useful in system monitoring tools or programs that need detailed child process information.
- Can be used in long-running applications where resource consumption needs to be tracked over time.

COMPILATION:
No special linking required for `wait3`.

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0) // Child process
    {
        printf("Child process running\n");
        exit(0);
    }
    else // Parent process
    {
        int status;
        struct rusage usage;
        wait3(&status, 0, &usage); // Parent waits and gets resource usage info
        printf("Parent process: Child terminated\n");
        printf("CPU time used by child: %ld.%06ld seconds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    }

    return 0;
}

/*
                                      WAIT4 FUNCTION
WAIT4 FUNCTION: The `wait4` function is similar to `wait3`, but it provides even more flexibility by allowing the parent to wait for a specific child process and obtain detailed information about the child’s resource usage, including memory, CPU time, etc.

FEATURES:
- Waits for a specific child process to terminate, like `waitpid`.
- Provides detailed resource usage information (similar to `wait3`).
- Can specify additional options for behavior, such as non-blocking mode.

FUNCTION PROTOTYPE:
    pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Parent calls wait4()         Parent waits for a specific child to terminate and collects resource data.
    Returns child's PID         Returns the PID of the terminated child process.
    Collects resource data      Collects resource usage details (CPU, memory) if requested.
    Options can be used         Options can specify behavior like non-blocking.

USAGE SCENARIOS:
- Useful when monitoring resource usage of specific child processes.
- Provides more control over which child to wait for, compared to `wait3`.

COMPILATION:
No special linking required for `wait4`.

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
        wait4(pid, &status, 0, &usage); // Parent waits for specific child with resource usage info
        printf("Parent process: Child terminated\n");
        printf("CPU time used by child: %ld.%06ld seconds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    }

    return 0;
}

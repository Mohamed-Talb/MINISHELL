/*
                                      WAIT FUNCTION
WAIT FUNCTION: The `wait` function is used to make a parent process wait until one of its child processes terminates. It is a simpler form of waiting compared to `waitpid`, as it waits for any child process to exit.

FEATURES:
- Waits for any child process to terminate.
- Blocks the parent process until a child process exits.
- Returns the process ID of the terminated child process.
- Can be used for handling simple child termination scenarios.

FUNCTION PROTOTYPE:
    pid_t wait(int *status);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Parent calls wait()         Parent process calls wait to wait for child processes.
    Waits for child termination Waits for any child to finish (or an error occurs).
    Returns child's PID         Returns the PID of the child process that terminated.
    Status can be checked       If `status` is not NULL, it provides termination status.

USAGE SCENARIOS:
- Used in simple scenarios where the parent wants to wait for any child process.
- Can be used to ensure proper cleanup or handling of resources after child termination.
- Often used in shell programs or command-line tools.

COMPILATION:
No special linking required for `wait`.

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
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
        wait(&status); // Parent waits for child to terminate
        printf("Parent process: Child terminated\n");
    }

    return 0;
}

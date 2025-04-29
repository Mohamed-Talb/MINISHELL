/*
                                      WAITPID FUNCTION
WAITPID FUNCTION: The `waitpid` function allows a parent process to wait for a specific child process to terminate. Unlike `wait`, `waitpid` provides more control, such as waiting for a particular child or specifying non-blocking behavior.

FEATURES:
- Waits for a specific child process, identified by its PID.
- Provides more control over which child process to wait for.
- Can be used with options to make it non-blocking or to return immediately if no child has terminated.

FUNCTION PROTOTYPE:
    pid_t waitpid(pid_t pid, int *status, int options);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Parent calls waitpid()       Parent specifies the PID of the child to wait for.
    Blocks or returns immediately Waits for child termination or returns immediately based on options.
    Returns child's PID         Returns the PID of the terminated child or error.
    Status can be checked       If `status` is provided, it gives the termination status.

USAGE SCENARIOS:
- Used when the parent needs to wait for a specific child process.
- Useful in more complex applications with multiple children or when a parent needs to process the termination of specific children.
- Can be used with options like `WNOHANG` for non-blocking behavior.

COMPILATION:
No special linking required for `waitpid`.

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
        waitpid(pid, &status, 0); // Parent waits for the specific child to terminate
        printf("Parent process: Child terminated\n");
    }

    return 0;
}

/*
                                      SIGACTION FUNCTION
SIGACTION FUNCTION: The `sigaction` function provides more advanced signal handling than `signal`. It allows you to specify signal handling behaviors with greater control, such as signal masking and signal flags.

FEATURES:
- Provides more control over signal handling than `signal`.
- Allows you to specify custom flags (e.g., `SA_RESTART`, `SA_SIGINFO`).
- Allows you to mask signals and control signal delivery during execution.
- More reliable and portable than `signal`.

FUNCTION PROTOTYPE:
    int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Process defines a sigaction struct Process defines a struct `sigaction` with the signal handler and flags.
    Calls sigaction()             The process calls `sigaction` to set the new signal handler and other behaviors.
    Signal sent to process       When the signal is sent, the handler executes with the specified behavior.

USAGE SCENARIOS:
- Used in more complex applications that need fine-grained control over signal handling.
- Common in system-level programming where you need to manage multiple signals and use additional flags.
- Allows more advanced features like handling signal info (`SA_SIGINFO`).

COMPILATION:
No special linking required for `sigaction`.



*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int signum)
{
    printf("Caught signal %d\n", signum);
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;  // Set flags (e.g., SA_RESTART)
    sigemptyset(&sa.sa_mask);  // No signals blocked during execution of handler
    sigaction(SIGINT, &sa, NULL);  // Handle Ctrl+C (SIGINT)
    while (1);  // Infinite loop to wait for signal
    return 0;
}

/*
                                      SIGNAL FUNCTION
SIGNAL FUNCTION: The `signal` function is used to set a handler for a specific signal. Signals are used in Unix-like systems to notify processes about events, like interrupts or segmentation faults. The `signal` function allows you to associate a signal with a custom handler.

FEATURES:
- Sets a custom handler for a specific signal.
- Can handle signals like `SIGINT`, `SIGTERM`, `SIGSEGV`, etc.
- Can specify the default action for a signal.
- Simplified interface for signal handling.

FUNCTION PROTOTYPE:
    void (*signal(int signum, void (*handler)(int)))(int);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Process calls signal()       The process calls `signal` to register a handler for a signal.
    Signal sent to process       A signal is sent to the process, e.g., pressing Ctrl+C sends `SIGINT`.
    Handler executed            If the signal is caught, the associated handler is executed.

USAGE SCENARIOS:
- Used in simple applications where you want to handle signals, such as user interrupts (`SIGINT`).
- Often used in programs that need to perform cleanup or custom actions when they receive certain signals.

LIMITATIONS:
- The `signal` function is not as flexible as `sigaction` and may not work as expected in certain environments.

COMPILATION:
No special linking required for `signal`.

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
    signal(SIGINT, handler);  // Handle Ctrl+C (SIGINT)
    while (1);  // Infinite loop to wait for signal
    return 0;
}

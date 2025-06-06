/*
                                      SIGADDSET FUNCTION
SIGADDSET FUNCTION: The `sigaddset` function adds a signal to an existing signal set, making it part of the set of signals to be blocked, unblocked, or handled.

FEATURES:
- Adds a signal to an existing signal set.
- Can be used to specify which signals should be blocked or handled.
- Useful in controlling which signals are blocked during critical sections of code.

FUNCTION PROTOTYPE:
    int sigaddset(sigset_t *set, int signum);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call sigaddset()            The function adds the signal identified by `signum` to the signal set.
    Used with sigprocmask()      The signal set can later be used with `sigprocmask` to block or unblock signals.
    Signal handling behavior    Helps control which signals are handled by the process.

USAGE SCENARIOS:
- Used in combination with `sigprocmask` to block specific signals during certain critical sections of code.
- Often used to control the flow of signals in multi-threaded programs.

COMPILATION:
No special linking required for `sigaddset`.

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>

int main()
{
    sigset_t set;
    sigemptyset(&set);  // Initialize the signal set to be empty
    sigaddset(&set, SIGINT);  // Add SIGINT to the set (e.g., Ctrl+C)

    // The set now contains SIGINT and can be used to block or handle that signal

    return 0;
}

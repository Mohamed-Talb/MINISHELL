/*
                                      TTYSLOT FUNCTION
TTY SLOT FUNCTION: The `ttyslot` function returns the slot number for the terminal associated with the current process.

FEATURES:
- Returns an integer representing the terminal's slot number.
- Useful for identifying terminal positions in a multi-user or multi-session environment.

FUNCTION PROTOTYPE:
    int ttyslot(void);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call ttyslot()              The function retrieves the terminal's slot number for the current process.
    Return value                Returns an integer slot number, or -1 on error.

USAGE SCENARIOS:
- Used in multi-user systems or environments with multiple terminals to identify a specific terminal.
- Commonly used in terminal management utilities.

COMPILATION:
No special linking required for `ttyslot`.
*/
#include <stdio.h>
#include <unistd.h>

int main() {
    int slot = ttyslot();

    if (slot == -1) {
        printf("No terminal slot found.\n");
    } else {
        printf("The terminal slot number is: %d\n", slot);
    }

    return 0;
}

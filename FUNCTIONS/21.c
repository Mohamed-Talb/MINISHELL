/*
                                      GETENV FUNCTION
GETENV FUNCTION: The `getenv` function retrieves the value of an environment variable.

FEATURES:
- Returns the value of an environment variable as a string.
- Can be used to fetch system-wide or user-specific environment configurations.
- Useful in programs that need to adapt to different environments or system configurations.

FUNCTION PROTOTYPE:
    char *getenv(const char *name);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call getenv()               The function retrieves the value of the environment variable `name`.
    Return value                Returns the environment variable value as a string, or `NULL` if not found.

USAGE SCENARIOS:
- Common in programs that rely on system configurations, such as setting paths or preferences.
- Used to retrieve variables like `PATH`, `HOME`, `USER`, etc.

COMPILATION:
No special linking required for `getenv`.
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *path = getenv("PATH");

    if (path) {
        printf("The PATH is: %s\n", path);
    } else {
        printf("PATH environment variable not found.\n");
    }

    return 0;
}

/*
                                      IOCTL FUNCTION
IOCTL FUNCTION: The `ioctl` function performs device-specific input/output operations on file descriptors.

FEATURES:
- Provides a way to manipulate device parameters using file descriptors.
- Can be used for a wide variety of device operations, such as setting terminal modes, querying device states, or configuring hardware.
- Typically used for devices that need special configuration beyond standard file operations.

FUNCTION PROTOTYPE:
    int ioctl(int fd, unsigned long request, ...);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call ioctl()                The function sends a control command to a device associated with the file descriptor `fd`.
    Return value                Returns 0 on success, or -1 on failure.

USAGE SCENARIOS:
- Used in low-level device programming, including interacting with terminals, serial ports, or network devices.
- Common in system-level programming to configure or query device settings.

COMPILATION:
You may need to link with `-lutil` or include specific headers depending on the device being interacted with.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

int main() {
    struct termios term;
    int fd = fileno(stdout);  // Example: Getting terminal attributes

    if (ioctl(fd, TCGETS, &term) == 0) {
        printf("Successfully fetched terminal attributes.\n");
    } else {
        perror("ioctl");
    }

    return 0;
}

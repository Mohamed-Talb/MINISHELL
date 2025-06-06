#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <linux/limits.h>

extern ssize_t readlink (const char *__restrict __path,
			 char *__restrict __buf, size_t __len)
     __THROW __nonnull ((1, 2)) __wur
     __fortified_attr_access (__write_only__, 2, 3);

void print_open_file_descriptors(void) {
    DIR *dir = opendir("/proc/self/fd");
    if (!dir) {
        fprintf(stderr, "Failed to open /proc/self/fd: %s\n", strerror(errno));
        return;
    }

    struct dirent *entry;
    char path[PATH_MAX], target[PATH_MAX];
    ssize_t len;

    fprintf(stderr, "Open file descriptors:\n");

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')  // skip "." and ".."
            continue;

        snprintf(path, sizeof(path), "/proc/self/fd/%s", entry->d_name);
        len = readlink(path, target, sizeof(target) - 1);
        if (len >= 0) {
            target[len] = '\0';
            fprintf(stderr, "  FD %s -> %s\n", entry->d_name, target);
        } else {
            fprintf(stderr, "  FD %s -> [unreadable]: %s\n", entry->d_name, strerror(errno));
        }
    }

    closedir(dir);
}
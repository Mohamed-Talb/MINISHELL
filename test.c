// #include <stdio.h>
// #include <string.h>

void my_printf(const char* fmt, char** strings, int* ints) 
{
    int int_i = 0, str_i = 0;
    for (int i = 0; fmt[i]; ++i) {
        if (fmt[i] == '%' && fmt[i + 1]) {
            if (fmt[i + 1] == 'd') {
                printf("%d", ints[int_i++]);
                i++; // skip the format specifier
            } else if (fmt[i + 1] == 's') {
                printf("%s", strings[str_i++]);
                i++;
            } else {
                putchar(fmt[i]);
            }
        } else {
            putchar(fmt[i]);
        }
    }
}

// // int main() {
// //     my_printf("%d, %s, %d, %s\n", (char*[]){"first", "second"}, (int[]){9, 2});
// //     my_printf("%s, %s\n", (char*[]){"first", "second"}, NULL);
// //     return 0;
// // }

// // int main(int argc, char *argv[]) {
// //     printf("argc = %d\n", argc);
// //     for (int i = 0; i < argc; i++) {
// //         printf("argv[%d] = '%s'\n", i, argv[i]);
// //     }
// //     return 0;
// // }

// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// // int main() {
// //     rl_instream = fopen("/dev/tty", "r");
// //     rl_outstream = fopen("/dev/tty", "w");

// //     char *line = readline("$ ");
// //     printf("You typed: %s\n", line);
// //     return 0;
// // }

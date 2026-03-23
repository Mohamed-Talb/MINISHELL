
## **PROJECT STRUCTURE**

```
MINISHELL/
  |-- Makefile
  |-- minishell        (BINARY / EXECUTABLE)
  |-- minishell.c      (MAIN SOURCE FILE)
  |-- minishell.h      (MAIN PROJECT API)
  |-- macros.h         (GLOBAL MACRO DEFINITIONS)
  |-- builtin/         (BUILTIN SHELL COMMAND IMPLEMENTATIONS)
  |-- duplication/     (DUPLICATION UTILITIES)
  |-- env_tools/       (ENVIRONMENT VARIABLE MANAGEMENT)
  |-- execution/       (CORE COMMAND EXECUTION LOGIC)
  |-- grammere/        (GRAMMAR PARSING / CHECKING)
  |-- helpers/         (UTILITY / HELPER FUNCTIONS)
  |-- heredoc/         (HEREDOC LOGIC / FILES)
  |-- libft/           (CUSTOM OR SCHOOL-PROVIDED LIBC FUNCTIONS)
  |-- parsing/         (COMMAND LINE PARSING / TOKENIZING)
```


## **HOW THE SHELL WORKS**

**MINISHELL** follows a structured command processing flow. It reads input, parses it, validates grammar, handles heredocs, and executes BUILTIN or EXTERNAL commands.

### **COMMAND PROCESSING FLOW**

```
User Input
            |
            v
+---------------------------+
|        READLINE           |   (PROMPT USER, READ INPUT LINE)
+---------------------------+
            |
            v
+---------------------------+
|        TOKENIZER          |   (PARSING / TOKENIZING INPUT)
+---------------------------+
            |
            v
+---------------------------+
|       GRAMMAR CHECK       |   (GRAMMERE/: SYNTAX / GRAMMAR VALIDATION)
+---------------------------+
            |
            v
+---------------------------+
|     HANDLE HEREDOCS       |   (HEREDOC/: MANAGE << REDIRECTIONS)
+---------------------------+
            |
            v
+---------------------------+
|   BUILTIN DETECTION       |   (BUILTIN/: CHECK IF COMMAND IS A SHELL BUILTIN)
+---------------------------+
            |               \
            |                \
            v                 v
+----------------+     +------------------+
|   EXECUTE      |     |   EXECUTE        |
| BUILTIN CMDS   |     | EXTERNAL CMDS    |
+----------------+     +------------------+
                              |
                              v
                   +--------------------+
                   |   COMMAND FORKING  |
                   |   (EXECUTION/:     |
                   |    PIPES, EXEC,    |
                   |     WAITING)       |
                   +--------------------+
                              |
                              v
                      OUTPUT / ERROR
```


## **STARTUP**

`main()` in `minishell.c` initializes the program state with the current ENVIRONMENT (`init_data(penv)`), then launches the main SHELL loop.


## **MAIN LOOP (`minishell()`)**

The SHELL enters an infinite loop:

* Configures SIGNAL HANDLING
* Resets transient state from previous commands
* Prompts the user using `prompter()` (with `READLINE`)
* If input is empty or EOF, it exits


## **INPUT PROCESSING**

* Parses the input with `parser()`
* Validates grammar with `grammer()`
* Handles HEREDOCS (`openallherdocs()`)
* On parsing failure, loop continues for next command


## **COMMAND EXECUTION**

* BUILTIN commands execute in the current process
* Non-BUILTIN or COMPOUND commands fork using `parent()`
* Handles PIPES, INPUT / OUTPUT REDIRECTIONS, ENVIRONMENT VARIABLES, and ERRORS


## **EXIT**

* Clears COMMAND HISTORY
* Frees all allocated MEMORY
* Returns the last exit STATUS


## **MAIN API (`minishell.h`)**

* **INITIALIZATION:** `init_data`, `init_cmds`, `reset_data`
* **PARSING:** `parser`, `expand`, `handle_arg`, `redirection`
* **EXECUTION:** `parent`, `child`, `builtin`, `check_builtin`
* **BUILTIN COMMANDS:** `ft_cd`, `ft_pwd`, `ft_env`, `ft_exit`, `ft_echo`, `ft_unset`, `ft_export`
* **HELPERS:** `mprintf`, `errors`, `ft_lst*` utilities, `signals`, `grammer`
* **HEREDOC:** `get_data`, `openallherdocs`, `fill_herdoc`


## **DATA STRUCTURES**

* `t_data`: Global program state (input line, ENV, exit code, command table, etc.)
* `t_cmds`: Parsed command with arguments, pipes, and status flags
* `t_list`: Generic linked list for tokens or commands


## **DIRECTORY DESCRIPTIONS**

* **builtin/**: BUILTIN command implementations
* **duplication/**: DUPLICATE file descriptors helpers
* **env_tools/**: ENVIRONMENT VARIABLES utilities (`export`, `unset`, `getenv`)
* **execution/**: EXECUTION engine (fork, execve, wait)
* **grammere/**: SYNTAX / GRAMMAR validation
* **helpers/**: Utility functions (PRINT, ERROR MANAGEMENT, EXIT STATUS)
* **heredoc/**: HEREDOC (`<<`) support
* **libft/**: LIBFT library functions
* **parsing/**: TOKENIZE and ANALYZE input to produce command structures


## **HOW TO BUILD & RUN**

```bash
cd MINISHELL
make
./minishell
```


## **NOTE**

This MINISHELL was built for EDUCATIONAL PURPOSES, focusing on:

* SYSTEM-LEVEL PROGRAMMING
* PROCESS CONTROL
* MEMORY MANAGEMENT (with custom GARBAGE COLLECTOR)
* SIGNAL HANDLING (CTRL-C, CTRL-D)
* BUILTIN AND EXTERNAL COMMAND EXECUTION

Consult the **project subject** and **norm.pdf** for exact requirements.
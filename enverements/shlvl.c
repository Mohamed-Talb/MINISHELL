#include "../minishell.h"

char **adjust_shell_level(char **env, int change) 
{
    char *new_level;
    char *old_SHLVL;
    int shell_level;
    long old_level;

    old_SHLVL = ft_getenv(env, "SHLVL");
    if (old_SHLVL == NULL || old_SHLVL[0] == '\0' || !atoi_sign(old_SHLVL))
        old_level = 0;
    else
        old_level = ft_atoi(old_SHLVL);
    shell_level = old_level + change;
    if (shell_level < 0)
        shell_level = 0;
    else if (shell_level >= 1000)
    {
        eputf("minishell: warning: shell level (%i) too high, resetting to 1\n", shell_level);
        shell_level = 1;
    }
    new_level = ft_itoa(shell_level);
    new_level = ft_strjoin_fc("SHLVL=", new_level, 2);
    return (envup(env, new_level));
}
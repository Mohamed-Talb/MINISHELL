#include "../libft.h"

int ft_close(int fd)
{
    if (fd != -1)
        return (close(fd));
    return (-1);
}

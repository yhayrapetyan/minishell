#include "minishell.h"

int	is_white_space(char ch)
{
	if ((ch > 8 && ch < 14) || ch == 32)//need to check range
		return (1);
	return (0);
}

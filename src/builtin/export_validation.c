#include "../../includes/builtin.h"

int	builtin_export_validation(char *arg)
{
	int	i;

	if (!arg)
	{
		minishell_error("export", "NULL", "not a valid identifier\n");
		return (EXIT_FAILURE);
	}
	if ((arg[0] != '_') && (ft_isdigit(arg[0]) || !ft_isalpha(arg[0])))
	{
		minishell_error("export", arg, "not a valid identifier\n");
		return (EXIT_FAILURE);
	}
	i = 1;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]))
		{
			if (arg[i] == '=') // When we meet first '=', we just quit with SUCCESS
				return (EXIT_SUCCESS);
			minishell_error("export", arg, "not a valid identifier\n");
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
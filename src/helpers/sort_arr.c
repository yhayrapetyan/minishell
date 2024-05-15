#include "minishell.h"

void sort_arr(char **export)
{
	int 	count;
	char	*temp;
	int 	i;
	int 	j;

	count = 0;
	while (export[count] != NULL) {
		count++;
	}
	i = 0;
	while (i < count - 1) {
		j = 0;
		while (j < count - i - 1) {
			if (ft_strcmp(export[j], export[j + 1]) > 0) {
				temp = export[j];
				export[j] = export[j + 1];
				export[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

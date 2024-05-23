#include "minishell.h"

/* not proud of all of this above */
static int my_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static char	*new_heredoc_content(t_data *data, char *str, int *index)
{
	char	*var_value;
	t_token *tmp_token;
	char	*tmp_content;
	int 	status;

	tmp_token = NULL;
	tmp_content = ft_strdup(str);
	if (!tmp_content)
		return (NULL);
	var_value = get_variable_value(data, str + *index);
	tmp_token = add_token(tmp_token, &tmp_content, WORD, DEFAULT);
	if (!tmp_token)
	{
		free(var_value);
		return (NULL);
	}
	status = update_content(data, var_value, *index);
	(*index) += my_strlen(var_value);
	free(var_value);
	if (status == -1)
		return (clean_tokens(tmp_token));
	tmp_content = ft_strdup(tmp_token->content);
	if (!tmp_content)
		return (clean_tokens(tmp_token));
	clean_tokens(tmp_token);
	return (tmp_content);
}

static char	*expand(t_data *data, char *str)
{
	int 	i;
	char	*temp;
	int 	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			temp = new_heredoc_content(data, str, &i);
			if (!temp)
				return (NULL);
			if (flag == 1)
				free(str);
			if (!flag)
				flag = 1;
			str = temp;
		}
		else
			i++;
	}
	return (str);
}

char	*expand_heredoc(t_data *data, char **line)
{
	char	**words;
	char	*tmp;
	int		i;

	words = ft_split(*line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			tmp = expand(data, words[i]);
			if (!tmp)
				return (free_arr(words));
			free(words[i]);
			words[i] = tmp;
		}
		i++;
	}
	return (arr_join(&words));
}

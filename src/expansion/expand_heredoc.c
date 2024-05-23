#include "minishell.h"

/* not proud of all of this above */
static t_token	*get_helper_token(t_data *data, char *str, int *index, char **tmp_content)
{
	char	*var_value;
	t_token *tmp_token;
	int 	status;
	t_data tmp_data;

	tmp_token = NULL;
	tmp_token = add_token(tmp_token, tmp_content, ENV, DEFAULT);
	if (!tmp_token)
		return (NULL);
	tmp_data.tokens = tmp_token;
	tmp_data.env = ft_arrdup(data->env);
	if (!tmp_data.env)
		return (clean_tokens(tmp_token));
	var_value = get_variable_value(data, str + *index);
	status = update_content(&tmp_data, var_value, *index);
	if (!var_value)
		(*index) += get_var_key_len(str + *index);
	else
		(*index) += ft_strlen(var_value);
	free(var_value);
	free_arr(tmp_data.env);
	if (status == -1)
		return (clean_tokens(tmp_token));
	return (tmp_token);
}

static char	*new_heredoc_content(t_data *data, char *str, int *index)
{
	char	*res;
	t_token *tmp_token;
	char	*tmp_content;

	tmp_content = ft_strdup(str);
	if (!tmp_content)
		return (NULL);
	tmp_token = get_helper_token(data, str, index, &tmp_content);
	if (!tmp_token)
	{
		free(tmp_content);
		return (NULL);
	}
	res = ft_strdup(tmp_token->content);
	clean_tokens(tmp_token);
	return (res);
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

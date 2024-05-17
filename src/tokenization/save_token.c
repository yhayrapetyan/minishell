#include "minishell.h"

int	save_word(t_data *data, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (1);
	while (start < end)
	{
		word[i] = data->input[start];
		start++;
		i++;
	}
	word[i] = '\0';
	data->tokens = add_token(data->tokens, word, WORD, DEFAULT);
	if (!data->tokens)
	{
		free(word);
		return (0);
	}
	return (1);
}

int	save_separator(t_data *data, int index, int type)
{
	int 	i;
	char	*sep;
	int 	len;

	len = 1;
	if (type == HEREDOC || type == APPEND)
		len++;
	sep = (char *)malloc(sizeof(char) * (len + 1));
	if (!sep)
		return (0);
	i = 0;
	while (i < len )
	{
		sep[i] = data->input[index + i];
		i++;
	}
	sep[i] = '\0';
	data->tokens = add_token(data->tokens, sep, type, DEFAULT);
	if (!data->tokens)
	{
		free(sep);
		return (0);
	}
	return (1);
}

int save_token(t_data *data, int start, int *end)
{
	int type;

	type = is_separator(data->input, *end);
	if (type)
	{
		if (*end != 0 && !is_separator(data->input, *end - 1))
		{
			if (!save_word(data, start, *end))
				return (-1);
		}
		if (!(type == SPACES || type == END))
		{
			if (!save_separator(data, *end, type))
				return (-1);
			if (type == HEREDOC || type == APPEND)
				(*end)++;
		}
		start = *end + 1;
	}
	return (start);
}

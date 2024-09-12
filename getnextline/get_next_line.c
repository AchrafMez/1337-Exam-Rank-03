#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	int	i = 0;
	char *ret;

	if (!str)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i = 0;
	int		j = 0;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	while (s1[i] && s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] && s2[j] != '\0')
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (free(s1), s1 = NULL, result);
}

int	contains_nl(char *sbuff)
{
	int	i = 0;
	if (!sbuff)
		return (-1);
	while (sbuff[i] && sbuff[i] != '\0')
	{
		if (sbuff[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*copy_until_nl(char *sbuff)
{
	char	*line;
	int		i;

	i = 0;
	if (!sbuff[0])
		return (NULL);
	while (sbuff[i] && sbuff[i] != '\n')
		i++;
	if (sbuff[i] && sbuff[i] == '\n')
		i += 1;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (sbuff[i] && sbuff[i] != '\n')
	{
		line[i] = sbuff[i];
		i++;
	}
	if (sbuff && sbuff[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*copy_after_nl(char *sbuff)
{
	char	*ret;
	int		i = 0;
	int		j = 0;

	if (!sbuff)
		return (NULL);
	while (sbuff[i] && sbuff[i] != '\n')
		i++;
	if (!sbuff[i])
	{
		free(sbuff);
		return (NULL);
	}
	ret = malloc((ft_strlen(sbuff) - i) + 1);
	i++;
	if (!ret)
		return (NULL);
	while (sbuff[i] != '\0')
		ret[j++] = sbuff[i++];
	ret[j] = '\0';
	return (free(sbuff), ret);
}

char	*ft_read(int fd, char *sbuff, char *buffer)
{
	int	bytes_read = BUFFER_SIZE;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(sbuff);
			free(buffer);
			buffer = NULL;
			sbuff = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		sbuff = ft_strjoin(sbuff, buffer);
		if (contains_nl(sbuff) == 1)
			break ;
	}
	return (free(buffer), buffer = NULL, sbuff);
}

char	*get_next_line(int fd)
{
	char		*buffer = NULL;
	static char	*sbuff=  NULL;
	char		*line = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	sbuff = ft_read(fd, sbuff, buffer);
	if (!sbuff)
		return (NULL);
	line = copy_until_nl(sbuff);
	sbuff = copy_after_nl(sbuff);
	return (line);
}

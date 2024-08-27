#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define BUFFER_SIZE 10000
int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}

char *ft_strdup(char *str)
{
    if(!str)
        return NULL;
    char *ret = malloc(ft_strlen(str) + 1);
    if(!ret)
        return NULL;
    int i = 0;
    while(str[i])
    {
        ret[i] = str[i];
        i++;
    }
    ret[i] = '\0';
    return ret;
}

char *ft_strjoin(char *s1, char *s2)
{
    if(!s1 && !s2)
        return NULL;
    if(!s1 && s2)
        return (ft_strdup(s2));
    int i = 0;
    int j = 0;
    char *ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if(!ret)
        return NULL;
    while(s1[i])
    {
        ret[i] = s1[i];
        i++;
    }
    while(s2[j])
    {
        ret[i + j] = s2[j];
        j++;
    }
    ret[i + j] = '\0';
    free(s1);
    return ret;
}

int countain_newline(char *str)
{
    int i = 0;
    if(!str)
        return 1;
    while(str[i])
    {
        if(str[i] == '\n')
            return 0;
        i++;
    }
    return 1;
}

char *copy_until_newline(char *str)
{
    int i = 0;
    if(!str)
        return NULL;
    while(str[i] && str[i] != '\n')
        i++;
    if(str[i] == '\n')
        i++;
    char *ret = malloc(i + 1);
    if(!ret)
        return NULL;
    i = 0;
    while(str[i] && str[i] != '\n')
    {
        ret[i] = str[i];
        i++;
    }
    if(str[i] == '\n')
        ret[i++] = '\n';
    ret[i] = '\0';
    return ret;
}

char *copy_after_newline(char *str)
{
    if(!str)
        return NULL;
    int i = 0;
    while(str[i] && str[i] != '\n')
        i++;
    if(!str[i])
    {
        free(str);
        return NULL;
    }
    char *ret = malloc(ft_strlen(str) - (i + 1));
    if(!ret)
        return NULL;
    i++;
    int j = 0;
    while(str[i] != '\0')
    {
        ret[j] = str[i];
        i++;
        j++;
    }
    ret[j] = '\0';
    free(str);
    return ret;
}

char *get_next_line(int fd)
{
    static char *sbuffer = NULL;
    char *buffer = NULL;
    char *line = NULL;
    int bytes_read = BUFFER_SIZE;
    if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return NULL;
    buffer = malloc(BUFFER_SIZE + 1);
    while(bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if(bytes_read == -1)
        {
            free(buffer);
            buffer = NULL;
            return NULL;
        }
        buffer[bytes_read] = '\0';
        sbuffer = ft_strjoin(sbuffer, buffer);
        if(!sbuffer || *sbuffer == '\0')
            return NULL;
        if(countain_newline(sbuffer) == 0)
            break ;
    }
    if(buffer){
        free(buffer);
        buffer = NULL;
    }
    line = copy_until_newline(sbuffer);
    sbuffer = copy_after_newline(sbuffer);
    return line;
}

int main()
{
    int fd = open("subject.txt", O_RDWR);
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    close(fd);
}
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int				ft_strlen(char *str);
void			*ft_memmove(void *dst, const void *src, size_t len);


static const char		*help(char *p, const char *s, int i)
{
	while (i-- > 0)
		*p++ = *s++;
	*p = '\0';
	return (s);
}

static int				build(char const *s, char c, char **q)
{
	int			i;
	char		*p;
	int			n;

	n = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			n++;
			i = 0;
			while (s[i] != c && s[i] != '\0')
				i++;
			p = (char*)malloc((i + 1) * sizeof(char));
			if (!p)
				return (-n);
			*q++ = p;
			s = help(p, s, i);
		}
		if (*s != '\0')
			s++;
	}
	*q = 0;
	return (n);
}

static void				clearall(char **q, char **q1, int i)
{
	int j;

	j = 0;
	while (j++ < i)
	{
		free(*q);
		(*q)++;
	}
	free(*q);
	free(q);
	free(q1);
}

char					**ft_split(char const *s, char c)
{
	char		**q;
	int			i;
	char		**q1;

	if (!s)
		return (NULL);
	q = (char**)malloc((ft_strlen((char*)s) + 1) * sizeof(char*));
	if (!q)
		return (q);
	i = build(s, c, q);
	q1 = (char**)malloc((i + 1) * sizeof(char*));
	if (i < 0 || !q1)
	{
		i *= -1;
		clearall(q, q1, i);
		return (NULL);
	}
	ft_memmove(q1, q, ((i + 1) * sizeof(char*)));
	free(q);
	return (q1);
}


#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int				ft_strlen(char *str)
{
	int			i;

	i = 0;
	while (str[i++]);
	return (i);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp0;
	char		*tmp1;

	tmp0 = (char *)src;
	tmp1 = (char *)dst;
	if (!tmp0 && !tmp1)
		return (NULL);
	if (tmp0 == tmp1)
		return (dst);
	if (tmp0 < tmp1)
	{
		tmp0 += len - 1;
		tmp1 += len - 1;
		while (len--)
			*tmp1-- = *tmp0--;
	}
	else
		while (len--)
			*tmp1++ = *tmp0++;
	return (dst);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	char	*q;

	if (!s1 || !s2)
		return (NULL);
	p = (char*)malloc((ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1) * sizeof(char));
	if (!p)
		return (p);
	q = p;
	while (*s1 != '\0')
		*p++ = *s1++;
	while (*s2 != '\0')
		*p++ = *s2++;
	*p = '\0';
	return (q);
}

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	unsigned char		*s;
	unsigned char		*ss;

	s = (unsigned char *)s1;
	ss = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s[i] != ss[i])
			return (s[i] - ss[i]);
		if (!s[i])
			return (0);
		i++;
	}
	return (0);
}
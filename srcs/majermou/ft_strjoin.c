#include "../includes/minishell.h"

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
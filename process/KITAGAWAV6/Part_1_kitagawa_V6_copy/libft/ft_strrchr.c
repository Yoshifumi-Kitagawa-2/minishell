/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:19:56 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/13 12:37:41 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ans;
	char	*tmp;

	i = ft_strlen(s);
	ans = (char *)s;
	tmp = NULL;
	if ((char)c == '\0')
		return ((ans + i));
	while (*ans)
	{
		if (*ans == (char)c)
			tmp = ans;
		ans++;
	}
	if (tmp)
		return (tmp);
	return (NULL);
}

// #include <stdio.h>
// #include <strings.h>
// int main(void)
// {
// 	char *s = "libft-test-tokyo";
// 	printf("%s\n", ft_strrchr(s, 0));
// 	printf("%s\n", 	strrchr(s, 0));
// 	return (0);
// }
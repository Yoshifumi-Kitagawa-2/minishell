/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:32:40 by matsushimak       #+#    #+#             */
/*   Updated: 2022/12/27 13:26:19 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*first;
	char	*last;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	first = (char *)s1;
	last = (char *)(s1 + ft_strlen(s1) - 1);
	while (*first && ft_strchr(set, *first))
			first++;
	while (last != first && ft_strchr(set, *last))
			last--;
	return (ft_substr(s1, (first - s1), (last - first + 1)));
}

// #include <stdio.h>
// int main(void)
// {
// 	// char s1[] = "1234AA1A123432";
// 	// char set[] = "1234";
// 	// printf("%s\n", ft_strtrim(s1, set));
// 	printf("%s\n", ft_strtrim("abcdba", "acb"));
// 	// printf("%s\n", "");
// 	return (0);
// }
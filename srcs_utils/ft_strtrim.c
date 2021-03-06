/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:42:15 by adbenoit          #+#    #+#             */
/*   Updated: 2020/07/05 22:22:55 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_len(int *count1, int *count2, char const *s1,
												char const *set)
{
	int	j;
	int	i;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[*count1] == set[j])
				(*count1)++;
			if (s1[*count2] == set[j])
				(*count2)--;
			j++;
		}
		i++;
	}
	if ((*count2 - *count1 + 1) < 0)
		return (1);
	return (*count2 - *count1 + 1);
}

char		*ft_strtrim(char *s1, char const *set, int size)
{
	int		i;
	int		len;
	int		count1;
	int		count2;
	char	*str;

	if (s1 == NULL || set == NULL)
		return (NULL);
	count1 = size;
	count2 = ft_strlen(s1) - 1;
	len = ft_len(&count1, &count2, s1, set);
	i = 0;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (count1 <= count2)
	{
		str[i] = s1[count1];
		i++;
		count1++;
	}
	str[i] = 0;
	free(s1);
	return (str);
}

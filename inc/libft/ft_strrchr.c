/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:40:45 by namenega          #+#    #+#             */
/*   Updated: 2020/01/10 15:24:09 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)s;
	i = 0;
	j = -5;
	if (c == '\0')
		return (str + ft_strlen(s));
	while (str[i] != 0)
	{
		if (str[i] == c)
			j = i;
		i++;
	}
	if (j == -5)
		return (NULL);
	return (str + j);
}

/*
** return un pointeur sur last occurrence de c ds s
*/

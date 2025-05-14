/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathan <Nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 17:26:45 by namenega          #+#    #+#             */
/*   Updated: 2021/03/16 17:29:24 by Nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	new_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_s)
		return (NULL);
	while (i < len)
	{
		new_s[i] = s[start + i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

/*
** malloc et return une str qui commence par start, max taille len
*/

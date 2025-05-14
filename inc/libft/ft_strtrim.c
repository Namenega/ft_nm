/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathan <Nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 19:26:47 by namenega          #+#    #+#             */
/*   Updated: 2021/03/16 17:28:56 by Nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** check si char set = celui ds str
*/

static int	ft_check(char c, const char *set)
{
	int		i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
** count le nbr de char set ds s1, au debut
*/

static int	ft_begin(char const *s1, char const *set)
{
	int		i;
	int		count_begin;

	i = 0;
	count_begin = 0;
	while (s1[i] != '\0')
	{
		if (ft_check(s1[i], set) == 1)
		{
			count_begin++;
			i++;
		}
		else
			return (count_begin);
	}
	return (count_begin);
}

/*
** compte nbr de char set ds s1, a la fin
*/

static int	ft_end(char const *s1, char const *set)
{
	int		i;
	int		count_end;

	i = 0;
	count_end = 0;
	while (s1[i] != '\0')
		i++;
	i -= 1;
	while (i > 0)
	{
		if (ft_check(s1[i], set) == 1)
		{
			count_end++;
			i--;
		}
		else
			return (count_end);
	}
	return (count_end);
}

/*
** si x -y -y est neg, return malloc[\0]
*/

static char	*ft_strneg(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

/*
** s1 - debut - fin >> si neg > ft_neg
** malloc new_str
** i = count_debut pour all length
*/

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		length;
	int		beginning;
	char	*str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	beginning = ft_begin(s1, set);
	length = ft_strlen(s1) - beginning - ft_end(s1, set);
	if (length < 0)
		return (ft_strneg());
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	while (length-- > 0)
		str[i++] = s1[beginning++];
	str[i] = '\0';
	return (str);
}

/*
** retourne une copie de s1 sans les char set (debut et fin)
*/

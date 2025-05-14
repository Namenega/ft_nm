/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:27:35 by namenega          #+#    #+#             */
/*   Updated: 2020/01/16 16:35:47 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** compter le nbr de char sans c
*/

static int	ft_malloc_s(char const *s, char c)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			counter++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (counter);
}

/*
** free
*/

static void	ft_free(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/*
** copier chaque chaine a l'endroit grace a substr
*/

static char	*ft_write_eachstr(const char *s, char c, char **tab)
{
	size_t	i;
	char	*dest;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	dest = ft_substr(s, 0, i);
	if (dest == NULL)
		ft_free(tab);
	return (dest);
}

/*
** malloc new str
** copie chaque char
*/

char		**ft_split(char const *s1, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (NULL);
	if (!(tab = malloc((ft_malloc_s(s1, c) + 1) * sizeof(char *))))
		return (NULL);
	while (s1[i])
	{
		while (s1[i] == c)
			i++;
		if (s1[i] && s1[i] != c)
		{
			tab[j++] = ft_write_eachstr(&s1[i], c, tab);
			while (s1[i] && s1[i] != c)
				i++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

/*
** tab de str separee par c
*/

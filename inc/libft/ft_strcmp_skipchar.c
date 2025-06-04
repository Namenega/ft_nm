#include "libft.h"

int ft_strcmp_skipchar(const char *s1, const char *s2, int c) {

	// TO REMOVE - only for ft_nm project
	s1 += 19;
	s2 += 19;

	while (*s1 == c)
		s1++;

	while (*s2 == c)
		s2++;

	while (*s1 && (*s1 == *s2)) {
		s1++;
		s2++;
	}

	return ((unsigned char)*s1 - (unsigned char)*s2);
}

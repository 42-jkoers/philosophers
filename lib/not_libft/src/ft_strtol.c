#include "libft.h"

// @return
// ""						false
// "-" | "+"				false
// " 1"						false
// "1a"						false
// "9999999999999999999999"	false (overflow)
// "1 2"					false
// "1 "						false
// "+1" | "-1" 				true
// "01"		 				true

bool	ft_strtol_safe(long *num, const char *str)
{
	size_t	digits;
	long	num_prev;
	char	*s;

	s = (char *)str;
	if (str[0] == '-' || str[0] == '+')
		s++;
	digits = 0;
	*num = 0;
	while (ft_isdigit(s[digits]))
	{
		num_prev = *num;
		*num *= 10;
		*num -= s[digits] - '0';
		if (*num > num_prev)
			return (false);
		digits++;
	}
	if (str[0] != '-')
		*num *= -1;
	return (digits > 0 && str[digits] == '\0');
}

bool	ft_strtol_clamp(long *num, const char *str, long min, long max)
{
	if (!ft_strtol_safe(num, str))
		return (false);
	return (*num >= min && *num <= max);
}

// @return
// ""						false
// "-" | "+"				false
// " 1"						false
// "1a"						false
// "9999999999999999999999"	false (overflow)
// "1 2"					false
// "1 "						false
// "+1" 	 				true
// "01"						true
// "-0" | "-000"			true

bool	ft_strtoul_safe(unsigned long *num, const char *str)
{
	size_t			digits;
	unsigned long	num_prev;
	char			*s;

	s = (char *)str;
	if (s[0] == '+' || s[0] == '-')
		s++;
	digits = 0;
	*num = 0;
	while (ft_isdigit(s[digits]))
	{
		num_prev = *num;
		*num *= 10;
		*num += s[digits] - '0';
		if (*num < num_prev)
			return (false);
		digits++;
	}
	if (str[0] == '-' && *num != 0)
		return (false);
	return (digits > 0 && s[digits] == '\0');
}

bool	ft_strtoul_clamp(
	unsigned long *num, const char *str, unsigned long min, unsigned long max)
{
	if (!ft_strtoul_safe(num, str))
		return (false);
	return (*num >= min && *num <= max);
}

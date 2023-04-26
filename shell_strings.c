#include "main.h"


int compareString(char *s1, char *s2, int pref_or_match)
{
	if (s1 == NULL || s2 == NULL)
		return (NEGATIVE);

	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (NEGATIVE);

		s1++;
		s2++;
	}

	if (pref_or_match == PREFIX)
		return (POSITIVE);

	if (*s1 == *s2)
		return (POSITIVE);

	return (NEGATIVE);
}






char *string_concat(char *s1, char *s2)
{
	int len = getStringLength(s1) + getStringLength(s2);
	char *dest = malloc(len + 1);
	char *pointer = dest;

	if (s1 != NULL)
	{
		while (*s1 != '\0')
		{
			*pointer = *s1;
			pointer++;
			s1++;
		}
	}

	if (s2 != NULL)
	{
		while (*s2 != '\0')
		{
			*pointer = *s2;
			pointer++;
			s2++;
		}
	}

	*pointer = '\0';

	return (dest);
}






char *copyString(char *src)
{
	int len = getStringLength(src);
	char *dest = malloc(len + 1);
	char *pointer;

	if (dest == NULL)
		exit(EXIT_FAILURE);

	pointer = dest;

	while (*src != '\0')
	{
		*pointer = *src;
		pointer++;
		src++;
	}

	*pointer = '\0';

	return (dest);
}






int getStringLength(char *string)
{
	int i = 0;

	if (string == NULL)
		return (0);

	while (*string != '\0')
	{
		i++;
		string++;
	}

	return (i);
}





int stringToInteger(char *s)
{
	int n = 0;
	int sign = 1;
	int s_int;

	if (*s == '=' && *(s + 1) >= '0' && *(s + 1) <= '9')
	{
		sign = -1;
		s++;
	}

	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
		{
			s_int = *s - 48;
			if (sign == 1)
				n = (n * 10) + s_int;
			else
				n = (n * 10) - s_int;
		}
		else
			return (-1);
		s++;
	}

	return (n);
}

/**
 * _itoa - converts an int into a stringing
 * @n: int to be converted
 *
 * Return: the converted number
 */
char *_itoa(int n)
{
	char *buf = malloc(12);
	char *pointer = buf;
	int is_min = NEGATIVE;
	int i_mask = 1000000000;
	int digit = 0;

	if (n == INT_MIN)
	{
		*pointer = '-';
		pointer++;
		n = INT_MAX;
		is_min = POSITIVE;
	}

	if (n < 0)
	{
		*pointer = '-';
		pointer++;
		n = -n;
	}

	while (i_mask > 9 && digit == 0)
	{
		digit = n / i_mask;
		n %= i_mask;
		i_mask /= 10;
	}

	if (digit != 0)
	{
		*pointer = digit + '0';
		pointer++;
	}

	while (i_mask > 9)
	{
		digit = n / i_mask;
		*pointer = digit + '0';
		pointer++;
		n %= i_mask;
		i_mask /= 10;
	}

	if (is_min == POSITIVE)
		n += 1;

	*pointer = n + '0';
	pointer++;
	*pointer = '\0';
	return (buf);
}

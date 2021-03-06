#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>

int nbrlen(long nbr, int base)
{
	int len = 1;
	while (nbr >= base)
	{
		nbr = nbr / base;
		len++;
	}
	return (len);
}

void	putnbr(long nbr, int base, char *base_c)
{
	if (nbr >= base)
		putnbr(nbr / base, base, base_c);
	write(1, &base_c[nbr % base], 1);
}

int ft_printf(char *format, ...)
{
	va_list vlist;
	int		ret = 0;
	long	nbr;
	int		len;
	char	*str;
	char	*s;
	int		prec;
	int		neg;
	int		width;
	int		spaces;
	int		zeroes;


	va_start(vlist, format);
	str = (char *)format;

	while (*str)
	{
		if (*str == '%')
		{
			str++;
			len = 0;
			nbr = 0;
			prec = -1;
			width = 0;
			spaces = 0;
			zeroes = 0;
			neg = 0;

			while (*str >= '0' && *str <= '9')
			{
				width = width * 10 + (*str - '0');
				str++;
			}

			if (*str == '.')
			{
				str++;
				prec = 0;
				while (*str >= '0' && *str <= '9')
				{
					prec = prec * 10 + (*str - '0');
					str++;
				}
			}

			if (*str == 's')
			{
				s = va_arg(vlist, char *);
				if (!s)
					s = "(null)";
				while (s[len])
					len++;
			}

			if (*str == 'd')
			{
				nbr = va_arg(vlist, int);
				if (nbr < 0)
				{
					neg = 1;
					nbr = -nbr;
				}
				len = nbrlen(nbr, 10) + neg;
			}

			if (*str == 'x')
			{
				nbr = va_arg(vlist, unsigned);
				len = nbrlen(nbr, 16);
			}

			if (prec >= len && *str != 's')
				zeroes = prec - len + neg;
			else if (prec < len && prec != -1 && *str == 's')
				len = prec;
			else if (prec == 0 && (*str == 's' || nbr == 0))
				len = 0;

			spaces = width - zeroes - len;
			while (spaces-- > 0)
				ret += write (1, " ", 1);
			if (neg == 1)
				write(1, "-", 1);
			while (zeroes-- > 0)
				ret += write(1, "0", 1);

			if (*str == 's')
				write(1, s, len);
			else if (*str == 'd')
				putnbr(nbr, 10, "0123456789");
			else if (*str == 'x')
				putnbr(nbr, 16, "0123456789abcdef");
			ret += len;
		}
		else
			ret += write(1, str, 1);
		str++;
	}

	va_end(vlist);
	return ret;
}

#include <stdio.h>
int main()
{

}

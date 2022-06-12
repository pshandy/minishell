#include <stdarg.h>
#include <unistd.h>

int	nbrlen(long nbr, int base)
{
	int len = 1;
	while (nbr >= base)
	{
		nbr = nbr / base;
		len++;
	}
	return (len);
}

void	putnbr(long nbr, int base, char *str)
{
	if (nbr >= base)
		putnbr(nbr / base, base, str);
	write(1, &str[nbr % base]);
}

int ft_printf(char *format, ...)
{
	va_list vlist;
	char *str;
	char *s;
	int ret = 0;
	int	len = 0;
	int prec = -1;
	int width;
	int spaces;
	int zeroes;
	int neg;
	long nbr;

	va_start(vlist, format);
	str = (char *)format;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			width = 0;
			prec = -1;
			len = 0;
			nbr = 0;
			zeroes = 0;
			spaces = 0;

			while (*str >= '0' && *str <= '9')
			{
				width = width * 10 + (*str - '0');
				str++;
			}

			if (*str == '.')
			{
				str++;
				prec = -1;
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
				while (str[len])
					len++;
			}

			if (*str == 'd')
			{
				nbr = va_arg(vlist, int);
				if (nbr < 0)
				{
					nbr = -nbr;
					neg = 1;
				}
				len = nbrlen(nbr) + neg;
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
				ret += write(1, " ", 1);
			if (neg == 1)
				write(1, "-", 1);
			while (zeroes-- > 0)
				ret += write(1, "0", 1);

			if (*str == 's')
				write(1, s, len);
			else if (*str == 'd')
				putnbr(nbr, 10, "0123456789");
			else if (*str == 'x')
				putnbt(nbr, 16, "0123456789abcdef");

			ret += len;
		}
		else
			ret += write(1, str, 1);
		str++;
	}

	va_end(vlist);
	return (ret);
}

#include "libft.h"

/* Custom implementation of putchar */
static int pf_putchar(char c) {
    return write(1, &c, 1);
}

/* Custom implementation of puts */
static int pf_putstr(const char *s) {
    int len = 0;
    if (!s)
        s = "(null)";
    while (*s)
        len += pf_putchar(*s++);
    return len;
}

/* Custom implementation of putnbr */
static int pf_putnbr(int n) {
    int len = 0;
    
	if (n == -2147483648)
        return pf_putstr("-2147483648");
    if (n < 0) {
        len += pf_putchar('-');
        n = -n;
    }
    if (n >= 10)
        len += pf_putnbr(n / 10);
    len += pf_putchar((n % 10) + '0');
    
	return len;
}

/* Custom implementation of putnbr_unsigned */
static int pf_putnbr_unsigned(unsigned int n) {
    int len = 0;
    
	if (n >= 10)
        len += pf_putnbr_unsigned(n / 10);
    len += pf_putchar((n % 10) + '0');
    
	return len;
}

/* Custom implementation of putnbr_hex */
static int pf_puthex_width(unsigned long n, int width, int uppercase, char pad) {
    char buffer[32];
    char *base = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    int i = 0, len = 0;

    if (n == 0)
        buffer[i++] = '0';
    else {
        while (n > 0) {
            buffer[i++] = base[n % 16];
            n /= 16;
        }
    }

    while (i < width)
        buffer[i++] = pad;

    while (i--)
        len += pf_putchar(buffer[i]);

    return len;
}

/* Custom implementation of putptr */
static int pf_putptr(unsigned long n) {
    int len = 0;
    len += pf_putstr("0x");
    len += pf_puthex_width(n, 0, 0, '0');
    return len;
}

/* Custom implementation of ft_printf */
int ft_printf(const char *format, ...) {
    va_list args;
    int i = 0, len = 0;

    va_start(args, format);
    while (format[i]) {
        if (format[i] == '%' && format[i + 1]) {
            i++;
            int zero_pad = 0, width = 0, long_mod = 0;
            
            if (format[i] == '0') {
                zero_pad = 1;
                i++;
            }
            // Field width
            while (format[i] >= '0' && format[i] <= '9') {
                width = width * 10 + (format[i] - '0');
                i++;
            }

            // Long modifier
            if (format[i] == 'l') {
                long_mod = 1;
                i++;
            }
            
            if (format[i] == 'c')
                len += pf_putchar(va_arg(args, int));
            else if (format[i] == 's')
                len += pf_putstr(va_arg(args, char *));
            else if (format[i] == 'd' || format[i] == 'i')
                len += pf_putnbr(va_arg(args, int));
            else if (format[i] == 'u')
                len += pf_putnbr_unsigned(va_arg(args, unsigned int));
            else if (format[i] == 'x' || format[i] == 'X') {
                int upper = (format[i] == 'X');
                if (long_mod)
                    len += pf_puthex_width(va_arg(args, unsigned long), width, upper, zero_pad ? '0' : ' ');
                else
                    len += pf_puthex_width(va_arg(args, unsigned int), width, upper, zero_pad ? '0' : ' ');
			}
            else if (format[i] == 'p') {
                len += pf_putstr("0x");
                len += pf_putptr((unsigned long)va_arg(args, void *));
            }
            else if (format[i] == '%')
                len += pf_putchar('%');
            else
                len += pf_putchar(format[i]);
        } else
            len += pf_putchar(format[i]);
        i++;
    }
    va_end(args);
    return len;
}


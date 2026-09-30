#include <stdarg.h>
#include <stddef.h>
#include "printf.h"
#include "utility_print_config.h"

const char hex_asc_table[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'a', 'b',
    'c', 'd', 'e', 'f' };

static void printf_str(char *str)
{
    while (str && (*str != (char)'\0'))
        printf_char(*str++);
}

static void printf_hex(unsigned int val, unsigned int width)
{
    int i = 0;
    char hex_val = 0, asc = 0;

    if ((width > 8) || (width == 0))
        width = 8;

    for (i = width - 1; i >= 0; i--) {
        hex_val = (val & (0x0F << (i << 2))) >> (i << 2);
        asc = hex_asc_table[(int)hex_val];
        printf_char(asc);
    }
}

static void printf_dec(unsigned int val)
{
    unsigned char buf[16];
    char asc = 0;
    int i = 0;

    while (1) {
        buf[i] = val % 10;
        val = val / 10;
        i++;
        if (val == 0)
            break;
    }

    for (; i > 0; i--) {
        asc = hex_asc_table[buf[i - 1]];
        printf_char(asc);
    }
}

void PRINTF(const char *fmt, ...)
{
    char c;
    unsigned int width = 0;
    va_list argptr;

    va_start(argptr, fmt);
    do {
        c = *fmt;
        if (c != '%') {
            printf_char(c);
        } else {
            while (1) {
                c = *++fmt;
                if ((c == 'd') || (c == 'x') || (c == 'X') || (c == 's') || (c == 'c')) {
                    if ((c == 'x') || (c == 'X')) {
                        if (*(fmt - 1) == '%')
                            width = 8;
                        else
                            width = *(fmt - 1) - '0';
                    }
                    break;
                }
            }

            switch (c) {
            case 'd':
                printf_dec(va_arg(argptr, int));
                break;
            case 'x':
                printf_hex((va_arg(argptr, int)), width);
                break;
            case 's':
                printf_str(va_arg(argptr, char *));
                break;
            case 'c':
                printf_char(va_arg(argptr, int));
                break;
            default:
                break;
            }
        }
        ++fmt;
    } while (*fmt != '\0');

    va_end(argptr);
}


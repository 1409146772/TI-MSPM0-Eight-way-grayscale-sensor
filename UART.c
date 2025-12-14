#include "ti_msp_dl_config.h"
#include <stdio.h>
#include <stdint.h>

/* Redirect stdio output to UART0 (blocking, no CRLF translation) */
int fputc(int c, FILE *f)
{
    (void)f;
    DL_UART_Main_transmitDataBlocking(UART_0_INST, (uint8_t)c);
    return c;
}

int fputs(const char *s, FILE *f)
{
    (void)f;
    while (*s) {
        DL_UART_Main_transmitDataBlocking(UART_0_INST, (uint8_t)(*s++));
    }
    return 0;
}

int puts(const char *s)
{
    int rc = fputs(s, stdout);
    fputc('\n', stdout);
    return rc;
}

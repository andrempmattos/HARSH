/*
 * sys_log.c
 *
 * MIT License
 *
 * Copyright (c) 2020 André Mattos
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/**
 * \brief System log implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.0.2
 * 
 * \date 22/02/2019
 * 
 * \addtogroup sys_log
 * \{
 */

#include <math.h>

#include <FreeRTOS.h>
#include <task.h>

#include <version.h>

#include "sys_log.h"
#include "sys_log_config.h"

int sys_log_init()
{
    if (sys_log_uart_init())
    {
        sys_log_new_line();

        sys_log_print_license_msg();

        sys_log_print_splash_screen();

        sys_log_print_msg("===================================================================");
        sys_log_new_line();
        sys_log_print_msg("Version:\t");
        sys_log_print_firmware_version();
        sys_log_new_line();

        sys_log_print_msg("Status:\t\t");
        sys_log_print_msg(FIRMWARE_STATUS);
        sys_log_new_line();

        sys_log_print_msg("Author:\t\t");
        sys_log_print_msg(FIRMWARE_AUTHOR);
        sys_log_print_msg(" <");
        sys_log_print_msg(FIRMWARE_AUTHOR_EMAIL);
        sys_log_print_msg(">");
        sys_log_new_line();
        sys_log_print_msg("===================================================================");
        sys_log_new_line();
        sys_log_new_line();
        sys_log_new_line();

        sys_log_mutex_create();

        return 0;
    }
    else
    {
        return -1;
    }
}

void sys_log_set_color(uint8_t color)
{
    switch(color)
    {
        case SYS_LOG_COLOR_BLACK:
            sys_log_print_msg("\033[1;30m");
            break;
        case SYS_LOG_COLOR_RED:
            sys_log_print_msg("\033[1;31m");
            break;
        case SYS_LOG_COLOR_GREEN:
            sys_log_print_msg("\033[1;32m");
            break;
        case SYS_LOG_COLOR_YELLOW:
            sys_log_print_msg("\033[1;33m");
            break;
        case SYS_LOG_COLOR_BLUE:
            sys_log_print_msg("\033[1;34m");
            break;
        case SYS_LOG_COLOR_MAGENTA:
            sys_log_print_msg("\033[1;35m");
            break;
        case SYS_LOG_COLOR_CYAN:
            sys_log_print_msg("\033[1;36m");
            break;
        case SYS_LOG_COLOR_WHITE:
            sys_log_print_msg("\033[1;37m");
            break;
        default:
            sys_log_reset_color();
    }
}

void sys_log_reset_color()
{
    sys_log_print_msg("\033[0m");
}

void sys_log_print_event(uint8_t type, const char *event)
{
    //sys_log_mutex_take();

    sys_log_print_system_time();
    sys_log_print_msg(" ");

    switch(type)
    {
        case SYS_LOG_INFO:
            break;
        case SYS_LOG_WARNING:
            sys_log_set_color(SYS_LOG_WARNING_COLOR);
            break;
        case SYS_LOG_ERROR:
            sys_log_set_color(SYS_LOG_ERROR_COLOR);
            break;
        default:
            break;
    }

    sys_log_print_msg(event);
}

void sys_log_print_event_from_module(uint8_t type, const char *module, const char *event)
{
    //sys_log_mutex_take();

    sys_log_print_system_time();

    sys_log_set_color(SYS_LOG_MODULE_NAME_COLOR);
    sys_log_print_msg(" ");
    sys_log_print_msg(module);
    sys_log_reset_color();
    sys_log_print_msg(": ");

    switch(type)
    {
        case SYS_LOG_INFO:
            break;
        case SYS_LOG_WARNING:
            sys_log_set_color(SYS_LOG_WARNING_COLOR);
            break;
        case SYS_LOG_ERROR:
            sys_log_set_color(SYS_LOG_ERROR_COLOR);
            break;
        default:
            break;
    }

    sys_log_print_msg(event);
}

void sys_log_print_msg(const char *msg)
{
    uint16_t i = 0;
    while(msg[i] != '\0')
    {
        sys_log_print_byte(msg[i]);
        i++;
    }
}

void sys_log_new_line()
{
    sys_log_reset_color();
    sys_log_print_msg("\n\r");
    //sys_log_mutex_give();
}

void sys_log_print_digit(uint8_t digit)
{
    if (digit < 0x0A)
    {
        sys_log_print_byte(digit + 0x30);    /* 0x30 = ascii 0 */
    }
    else if (digit <= 0x0F)
    {
        sys_log_print_byte(digit + 0x37);    /* 0x37 = ascii 7 */
    }
    else
    {
        sys_log_print_byte('N');
    }
}

void sys_log_print_str(char *str)
{
    uint16_t i = 0;
    while(str[i] != '\0')
    {
        sys_log_print_byte(str[i]);
        i++;
    }
}

void sys_log_print_dec(uint32_t dec)
{
    if (dec == 0)
    {
        sys_log_print_digit(0);
    }
    else
    {
        uint8_t dec_str[10];                /* 32-bits = decimal with 10 digits */

        uint8_t digits = log10(dec) + 1;

        uint8_t i = 0;
        for(i=0; i<digits; ++i, dec /= 10)
        {
            dec_str[i] = dec % 10;
        }

        uint8_t j = 0;
        for(j=i; j>0; j--)
        {
            sys_log_print_digit(dec_str[j-1]);
        }
    }
}

void sys_log_print_hex(uint32_t hex)
{
    sys_log_print_msg("0x");
    
    if (hex > 0x00FFFFFF)
    {
        sys_log_print_digit((uint8_t)(hex >> 28) & 0x0F);
        sys_log_print_digit((uint8_t)(hex >> 24) & 0x0F);
    }

    if (hex > 0x0000FFFF)
    {
        sys_log_print_digit((uint8_t)(hex >> 20) & 0x0F);
        sys_log_print_digit((uint8_t)(hex >> 16) & 0x0F);
    }

    if (hex > 0x000000FF)
    {
        sys_log_print_digit((uint8_t)(hex >> 12) & 0x0F);
        sys_log_print_digit((uint8_t)(hex >> 8) & 0x0F);
    }

    sys_log_print_digit((uint8_t)(hex >> 4) & 0x0F);
    sys_log_print_digit((uint8_t)(hex & 0x0F));
}

void sys_log_dump_hex(uint8_t *data, uint16_t len)
{
    uint16_t i = 0;
    for(i=0; i<len; i++)
    {
        sys_log_print_hex(data[i]);

        if (i < len-1)
        {
            sys_log_print_msg(", ");
        }
    }
}

void sys_log_print_byte(uint8_t byte)
{
    sys_log_uart_write_byte(byte);
}

void sys_log_print_system_time()
{
    sys_log_set_color(SYS_LOG_SYSTEM_TIME_COLOR);

    sys_log_print_msg("[ ");
    sys_log_print_dec(xTaskGetTickCount());  /* System time in milliseconds */
    sys_log_print_msg(" ]");

    sys_log_reset_color();
}

void sys_log_print_license_msg()
{
    sys_log_print_msg("HARSH Payload Copyright (C) 2020, Andre Mattos;");
    sys_log_new_line();
    sys_log_print_msg("This program comes with ABSOLUTELY NO WARRANTY.");
    sys_log_new_line();
    sys_log_print_msg("This is free software, and you are welcome to redistribute it");
    sys_log_new_line();
    sys_log_print_msg("under certain conditions.");
    sys_log_new_line();
    sys_log_new_line();
    sys_log_print_msg("Source code: https://github.com/andrempmattos/HARSH");
    sys_log_new_line();
    sys_log_print_msg("Documentation: https://github.com/andrempmattos/HARSH/tree/master/documentation");
    sys_log_new_line();
}

void sys_log_print_splash_screen()
{
    sys_log_print_msg("                                                                   ");
    sys_log_new_line();
    sys_log_print_msg("                                                                   ");
    sys_log_new_line();
    sys_log_print_msg(" _   _    _    ____  ____  _   _   ____   _ __   ___     ___    _    ____  ");
    sys_log_new_line();
    sys_log_print_msg("| | | |  / \\  |  _ \\/ ___|| | | | |  _ \\ / \\\\ \\ / / |   / _ \\  / \\  |  _ \\ ");
    sys_log_new_line();
    sys_log_print_msg("| |_| | / _ \\ | |_) \\___ \\| |_| | | |_) / _ \\\\ V /| |  | | | |/ _ \\ | | | |");
    sys_log_new_line();
    sys_log_print_msg("|  _  |/ ___ \\|  _ < ___) |  _  | |  __/ ___ \\| | | |__| |_| / ___ \\| |_| |");
    sys_log_new_line();
    sys_log_print_msg("|_| |_/_/   \\_\\_| \\_\\____/|_| |_| |_| /_/   \\_\\_| |_____\\___/_/   \\_\\____/ ");
    sys_log_new_line();
    sys_log_print_msg("                                                                   ");
    sys_log_new_line();
    sys_log_print_msg("                                                                   ");
    sys_log_new_line();
}

void sys_log_print_firmware_version()
{
    sys_log_print_msg("[ ");
    sys_log_print_msg(FIRMWARE_VERSION);
    sys_log_print_msg(" ]");
}

/** \} End of sys_log group */

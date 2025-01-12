/*
 * sys_log.h
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
 * \brief Functions for printing messages and variables over an UART port.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.0.2
 * 
 * \date 22/02/2019
 * 
 * \defgroup sys_log System Log
 * \ingroup system
 * \{
 */

#ifndef SYS_LOG_H_
#define SYS_LOG_H_

#include <stdint.h>
#include <stdbool.h>

#include <FreeRTOS.h>
#include <semphr.h>

/**
 * \brief Event types.
 */
typedef enum
{
    SYS_LOG_INFO,               /**< Information message. */
    SYS_LOG_WARNING,            /**< Warning message. */
    SYS_LOG_ERROR               /**< Error message. */
} sys_log_event_type_e;

/**
 * \brief System log text colors list.
 */
typedef enum
{
    SYS_LOG_COLOR_BLACK = 0,    /**< Color black. */
    SYS_LOG_COLOR_RED,          /**< Color red. */
    SYS_LOG_COLOR_GREEN,        /**< Color green. */
    SYS_LOG_COLOR_YELLOW,       /**< Color yellow. */
    SYS_LOG_COLOR_BLUE,         /**< Color blue. */
    SYS_LOG_COLOR_MAGENTA,      /**< Color magenta. */
    SYS_LOG_COLOR_CYAN,         /**< Color cyan. */
    SYS_LOG_COLOR_WHITE         /**< Color white. */
} sys_log_colors_e;

/**
 * \brief System log mutex.
 */
extern SemaphoreHandle_t xSysLogSemaphore;

/**
 * \brief Initialization of the system log.
 * 
 * \return The error/status code.
 */
int sys_log_init();

/**
 * \brief Sets the foreground color for the next log message.
 *
 * This function uses the ANSI color code to output color log messages.
 *
 * \param[in] color is the foreground color of text to select. It can be:
 * \parblock
 *      -\b SYS_LOG_COLOR_BLACK
 *      -\b SYS_LOG_COLOR_RED
 *      -\b SYS_LOG_COLOR_GREEN
 *      -\b SYS_LOG_COLOR_YELLOW
 *      -\b SYS_LOG_COLOR_BLUE
 *      -\b SYS_LOG_COLOR_MAGENTA
 *      -\b SYS_LOG_COLOR_CYAN
 *      -\b SYS_LOG_COLOR_WHITE
 *      .
 * \endparblock
 *
 * \return None.
 */
void sys_log_set_color(uint8_t color);

/**
 * \brief Resets the color back to normal.
 *
 * \return None.
 */
void sys_log_reset_color();

/**
 * \brief Prints a general event.
 *
 * \param[in] type is the type of event. It can be:
 * \parblock
 *      -\b SYS_LOG_INFO
 *      -\b SYS_LOG_WARNING
 *      -\b SYS_LOG_ERROR
 *      .
 * \endparblock
 *
 * \param[in] event is the event text.
 *
 * \return None.
 */
void sys_log_print_event(uint8_t type, const char *event);

/**
 * \brief Prints an event from a system module.
 *
 * \param[in] type is the type of event. It can be:
 * \parblock
 *      -\b SYS_LOG_INFO
 *      -\b SYS_LOG_WARNING
 *      -\b SYS_LOG_ERROR
 *      .
 * \endparblock
 *
 * \param[in] module is the module name.
 *
 * \param[in] event is the event text.
 *
 * \return None.
 */
void sys_log_print_event_from_module(uint8_t type, const char *module, const char *event);

/**
 * \brief Prints a message over the system log module.
 * 
 * \param[in] msg is the message to be written.
 * 
 * \return None.
 */
void sys_log_print_msg(const char *msg);

/**
 * \brief Prints an string over the system log module.
 *
 * \param[in] str is a pointer to an string.
 *
 * \return None.
 */
void sys_log_print_str(char *str);

/**
 * \brief Prints a new line.
 *
 * \return None.
 */
void sys_log_new_line();

/**
 * \brief Prints a integer digit over the system log module.
 * 
 * \param[in] d is the digit to be written (0 to 9)
 * 
 * \return None.
 */
void sys_log_print_digit(uint8_t d);

/**
 * \brief Prints a decimal number over the system log module.
 *
 * \param[in] dec is the decimal number to print.
 *
 * \return None.
 */
void sys_log_print_dec(uint32_t dec);

/**
 * \brief Prints a hexadecimal value over the system log module.
 * 
 * Example:
 *      - Integer   = 0x65
 *      - Output    = "0x65"
 * 
 * \note The integer is printed in ASCII code.
 * 
 * \param hex is the hexadecimal to be written.
 * 
 * \return None.
 */
void sys_log_print_hex(uint32_t hex);

/**
 * \brief .
 *
 * \param[in] data .
 *
 * \param[in] len .
 *
 * \return None.
 */
void sys_log_dump_hex(uint8_t *data, uint16_t len);

/**
 * \brief Prints a raw byte over the system log module.
 * 
 * \param[in] byte is the byte to be printed.
 * 
 * \return None.
 */
void sys_log_print_byte(uint8_t byte);

/**
 * \brief Prints the system time in milliseconds.
 *
 * \return None.
 */
void sys_log_print_system_time();

/**
 * \brief Prints the license text and genreal firmware information.
 *
 * \return None.
 */
void sys_log_print_license_msg();

/**
 * \brief Prints the splash screen of the firmware.
 *
 * \return None.
 */
void sys_log_print_splash_screen();

/**
 * \brief Writes the current firmware version.
 *
 * \return None.
 */
void sys_log_print_firmware_version();

/**
 * \brief Initialization of the system log UART port.
 * 
 * UART settings:
 *      -\b MCU interface = USCI_A1
 *      -\b Baudrate      = 115200 bps
 *      -\b Data bits     = 8
 *      -\b Parity bit    = None
 *      -\b Stop bits     = 1
 *      .
 * 
 * \return TRUE/FALSE if successful or not.
 */
bool sys_log_uart_init();

/**
 * \brief Writes a byte over the UART port.
 *
 * \param[in] byte is the byte to be written.
 *
 * \return None.
 */
void sys_log_uart_write_byte(uint8_t byte);

/**
 * \brief Creates a mutex to use the system log module.
 *
 * \return TRUE/FALSE if successful or not.
 */
bool sys_log_mutex_create();

/**
 * \brief Holds the resource (system log module).
 *
 * \return TRUE/FALSE if successful or not.
 */
bool sys_log_mutex_take();

/**
 * \brief Frees the resource (system log).
 *
 * \return TRUE/FALSE if successful or not.
 */
bool sys_log_mutex_give();

#endif /* SYS_LOG_H_ */

/** \} End of sys_log group */

/*
 * heartbeat.h
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
 * \brief Heartbeat task definition.
 * 
 * \author Andre Mattos <andrempmattos@gmail.com>
 * 
 * \version 0.0.5
 * 
 * \date 09/05/2020
 * 
 * \defgroup heartbeat Heartbeat
 * \ingroup tasks
 * \{
 */

#ifndef HEARTBEAT_H_
#define HEARTBEAT_H_

#include <FreeRTOS.h>
#include <task.h>

#define TASK_HEARTBEAT_NAME                 "Heartbeat"     /**< Task name. */
#define TASK_HEARTBEAT_STACK_SIZE           128             /**< Memory stack size in bytes. */
#define TASK_HEARTBEAT_PRIORITY             1               /**< Priority. */
#define TASK_HEARTBEAT_PERIOD_MS            500             /**< Period in milliseconds. */
#define TASK_HEARTBEAT_INIT_TIMEOUT_MS      2000            /**< Wait time to initialize the task in milliseconds. */

/**
 * \brief Heartbeat task handle.
 */
extern xTaskHandle xTaskHeartbeatHandle;

/**
 * \brief System heartbeat task.
 *
 * \param[in] pvParameters is a value that will passed as the task's parameter.
 *
 * \return None.
 */
void vTaskHeartbeat(void *pvParameters);

#endif /* HEARTBEAT_H_ */

/** \} End of heartbeat group */
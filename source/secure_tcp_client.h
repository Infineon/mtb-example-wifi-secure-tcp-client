/******************************************************************************
* File Name:   secure_tcp_client.h
*
* Description: This file contains declaration of task related to secure TCP
* client operation.
*
*******************************************************************************
* Copyright 2019-2022, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#ifndef SECURE_TCP_CLIENT_H_
#define SECURE_TCP_CLIENT_H_

/*******************************************************************************
* Macros
********************************************************************************/
/* Maximum number of connection retries to the TCP server. */
#define MAX_TCP_SERVER_CONN_RETRIES           (5)

/* Length of the TCP data packet. */
#define MAX_TCP_DATA_PACKET_LENGTH            (20)

/* Length of the LED ON/OFF command issued from the TCP server. */
#define TCP_LED_CMD_LEN                       (1)

/* Set this macro to '1' to enable IPv6 protocol. Default value is '0' to use
 * IPv4 protocol.
 */
#define USE_IPV6_ADDRESS                      (0)
#define TCP_SERVER_PORT                       (50007)
#define RTOS_TICK_TO_WAIT                     (50u)
#define UART_INPUT_TIMEOUT_MS                 (1u)
#define UART_BUFFER_SIZE                      (50u)

/*******************************************************************************
* Function Prototype
********************************************************************************/
void tcp_secure_client_task(void *arg);

#endif /* SECURE_TCP_CLIENT_H_ */

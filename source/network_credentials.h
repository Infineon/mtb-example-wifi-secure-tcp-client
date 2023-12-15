/******************************************************************************
* File Name: network_credentials.h
*
* Description: This file is the public interface for Wi-Fi/Soft-AP credentials and
* TLS credentials.
*
* Related Document: See README.md
*
*******************************************************************************
* Copyright 2019-2023, Cypress Semiconductor Corporation (an Infineon company) or
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

/*******************************************************************************
* Include guard
*******************************************************************************/
#ifndef NETWORK_CREDENTIALS_H_
#define NETWORK_CREDENTIALS_H_

#include "cy_wcm.h"

/*******************************************************************************
* Macros
********************************************************************************/
#define INITIALISER_IPV4_ADDRESS(addr_var, addr_val)   addr_var = { CY_WCM_IP_VER_V4, \
                                                       { .v4 = (uint32_t)(addr_val) } }

#define MAKE_IPV4_ADDRESS(a, b, c, d)                  ((((uint32_t) d) << 24) | \
                                                       (((uint32_t) c) << 16) | \
                                                       (((uint32_t) b) << 8) | \
                                                       ((uint32_t) a))
#if(USE_IPV6_ADDRESS)
    /* Converts a 16-bit value from host byte order (little-endian) to network byte order (big-endian) */
    #define HTONS(x) ( ( ( (x) & 0x0000FF00) >> 8 ) | ((x) & 0x000000FF) << 8 )

    #define MAKE_IPV6_ADDRESS(a, b, c, d, e, f, g, h)  { \
                                                         ( (uint32_t) (HTONS(a)) | ( (uint32_t) (HTONS(b)) << 16 ) ), \
                                                         ( (uint32_t) (HTONS(c)) | ( (uint32_t) (HTONS(d)) << 16 ) ), \
                                                         ( (uint32_t) (HTONS(e)) | ( (uint32_t) (HTONS(f)) << 16 ) ), \
                                                         ( (uint32_t) (HTONS(g)) | ( (uint32_t) (HTONS(h)) << 16 ) ), \
                                                       }
#endif /* USE_IPV6_ADDRESS */

/* To use the Wi-Fi device in AP interface mode, set this macro as '1' */
#define USE_AP_INTERFACE                               (0)

/* Change the server IP address to match the TCP server address (IP address
 * of the PC).
 */
#if(USE_IPV6_ADDRESS)
    #define TCP_SERVER_IP_ADDRESS                      MAKE_IPV6_ADDRESS(0xFE80, 0, 0 ,0, 0xF0F3, 0xB58C, 0x8FC2, 0xA690)
#else
    #define TCP_SERVER_IP_ADDRESS                      MAKE_IPV4_ADDRESS(192, 168, 43, 105)
#endif

#if(USE_AP_INTERFACE)
    #define WIFI_INTERFACE_TYPE                        CY_WCM_INTERFACE_TYPE_AP
    /* SoftAP Credentials: Modify SOFTAP_SSID and SOFTAP_PASSWORD as required */
    #define SOFTAP_SSID                                "MY_SOFT_AP"
    #define SOFTAP_PASSWORD                            "psoc1234"

    /* Security type of the SoftAP. See 'cy_wcm_security_t' structure
     * in "cy_wcm.h" for more details.
     */
    #define SOFTAP_SECURITY_TYPE                       CY_WCM_SECURITY_WPA2_AES_PSK

    #define SOFTAP_IP_ADDRESS_COUNT                    (2u)

    #define SOFTAP_IP_ADDRESS                          MAKE_IPV4_ADDRESS(192, 168, 10, 1)
    #define SOFTAP_NETMASK                             MAKE_IPV4_ADDRESS(255, 255, 255, 0)
    #define SOFTAP_GATEWAY                             MAKE_IPV4_ADDRESS(192, 168, 10, 1)
    #define SOFTAP_RADIO_CHANNEL                       (1u)
#else
    #define WIFI_INTERFACE_TYPE                        CY_WCM_INTERFACE_TYPE_STA
    /* Wi-Fi Credentials: Modify WIFI_SSID, WIFI_PASSWORD, and WIFI_SECURITY_TYPE
     * to match your Wi-Fi network credentials.
     * Note: Maximum length of the Wi-Fi SSID and password is set to
     * CY_WCM_MAX_SSID_LEN and CY_WCM_MAX_PASSPHRASE_LEN as defined in cy_wcm.h file.
     */
    #define WIFI_SSID                                  "MY_WIFI_SSID"
    #define WIFI_PASSWORD                              "MY_WIFI_PASSWORD"

    /* Security type of the Wi-Fi access point. See 'cy_wcm_security_t' structure
     * in "cy_wcm.h" for more details.
     */
    #define WIFI_SECURITY_TYPE                         CY_WCM_SECURITY_WPA2_MIXED_PSK

    /* Maximum number of connection retries to a Wi-Fi network. */
    #define MAX_WIFI_CONN_RETRIES                      (10u)

    /* Wi-Fi re-connection time interval in milliseconds */
    #define WIFI_CONN_RETRY_INTERVAL_MSEC              (1000u)
#endif

/* TCP client certificate. Copy from the TCP client certificate
 * generated by OpenSSL (See Readme.md on how to generate a SSL certificate).
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIICOTCCAd4CFFwqB0M9Wvf0fVI4ztYF/DqvIWWlMAoGCCqGSM49BAMCMIGCMQsw\n"\
"CQYDVQQGEwJJTjELMAkGA1UECAwCS0ExETAPBgNVBAcMCGJhbmdsb3JlMREwDwYD\n"\
"VQQKDAhpbmZpbmVvbjELMAkGA1UECwwCQ1kxDzANBgNVBAMMBnByYXZpbjEiMCAG\n"\
"CSqGSIb3DQEJARYTcHJhdmluQGluZmluZW9uLmNvbTAeFw0yMzExMTYxMjMyNTJa\n"\
"Fw0yNjA4MTIxMjMyNTJaMIG5MQswCQYDVQQGEwJJTjELMAkGA1UECAwCS0ExETAP\n"\
"BgNVBAcMCGJhbmdsb3JlMQswCQYDVQQKDAJDWTERMA8GA1UECwwIaW5maW5lb24x\n"\
"RjBEBgNVBAMMPRtbQ1kbW0EbW0MbW0MbW0MbW0MbW0MbW0MbW0MbW0MbW0MbW0Mb\n"\
"W0MbW0MbW0MbW0MbW0MbW0MbW0MbW0MxIjAgBgkqhkiG9w0BCQEWE3ByYXZpbkBp\n"\
"bmZpbmVvbi5jb20wWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAAS9xMn6y/rBYA9p\n"\
"52lWJwXSSWdMS+ULefV7dpSAyXsGZgTLMiI5T5tIXBlByekCkxHmzIig6L+wR78b\n"\
"qRoJBNNuMAoGCCqGSM49BAMCA0kAMEYCIQDkcL1A4+KtwKR43Qpo08mGQfp+ZTy0\n"\
"93W536pasE59TwIhAIIpkTIyg98UrhguhzXOBwizcU4KgXAT3mijmYBX9a2L\n"\
"-----END CERTIFICATE-----\n"

/* Private key of the TCP client. Copy from the TCP client key
 * generated by OpenSSL (See Readme.md on how to create a private key).
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN EC PRIVATE KEY-----\n"\
"MHcCAQEEIDayKWsew2V6mB0gw/x18u9EOzWXyphcnDOMV3peyER0oAoGCCqGSM49\n"\
"AwEHoUQDQgAEvcTJ+sv6wWAPaedpVicF0klnTEvlC3n1e3aUgMl7BmYEyzIiOU+b\n"\
"SFwZQcnpApMR5syIoOi/sEe/G6kaCQTTbg==\n"\
"-----END EC PRIVATE KEY-----\n"


/* TCP server certificate. In this example this is the RootCA
 * certificate so as to verify the TCP server's identity. */
#define keySERVER_ROOTCA_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIICWzCCAgGgAwIBAgIUFsfvWrTILENpQQKpo9bzf+Dc9l8wCgYIKoZIzj0EAwIw\n"\
"gYIxCzAJBgNVBAYTAklOMQswCQYDVQQIDAJLQTERMA8GA1UEBwwIYmFuZ2xvcmUx\n"\
"ETAPBgNVBAoMCGluZmluZW9uMQswCQYDVQQLDAJDWTEPMA0GA1UEAwwGcHJhdmlu\n"\
"MSIwIAYJKoZIhvcNAQkBFhNwcmF2aW5AaW5maW5lb24uY29tMB4XDTIzMTExNjEy\n"\
"MjkwOVoXDTIzMTIxNjEyMjkwOVowgYIxCzAJBgNVBAYTAklOMQswCQYDVQQIDAJL\n"\
"QTERMA8GA1UEBwwIYmFuZ2xvcmUxETAPBgNVBAoMCGluZmluZW9uMQswCQYDVQQL\n"\
"DAJDWTEPMA0GA1UEAwwGcHJhdmluMSIwIAYJKoZIhvcNAQkBFhNwcmF2aW5AaW5m\n"\
"aW5lb24uY29tMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEixkfal3CQEc/Jy3Q\n"\
"J6RlgFRfYv/2WwQeXRuzEesJJ/cLEy4N3sjfbIkeysMwdViHvU4uotghNoEZ+nrK\n"\
"kqG606NTMFEwHQYDVR0OBBYEFC+9lLNnrXxhz0gylhF49S+gk/c0MB8GA1UdIwQY\n"\
"MBaAFC+9lLNnrXxhz0gylhF49S+gk/c0MA8GA1UdEwEB/wQFMAMBAf8wCgYIKoZI\n"\
"zj0EAwIDSAAwRQIgO0d/rjYkijh3yI6xz88jNlGgJ0GNj0IeShvHywZWnMkCIQCC\n"\
"kEl7qVWwS9Aoy6JHOD+5AzLpsIdHDuGcfF5CKqO7yA==\n"\
"-----END CERTIFICATE-----\n"


#endif /* NETWORK_CREDENTIALS_H_ */

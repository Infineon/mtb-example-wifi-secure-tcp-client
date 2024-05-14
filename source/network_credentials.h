/******************************************************************************
* File Name: network_credentials.h
*
* Description: This file is the public interface for Wi-Fi/Soft-AP credentials and
* TLS credentials.
*
* Related Document: See README.md
*
*******************************************************************************
* Copyright 2019-2024, Cypress Semiconductor Corporation (an Infineon company) or
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
"MIICAzCCAakCFD3ZEPLPA3JQLvR7Yvx/KGXlYleHMAoGCCqGSM49BAMCMIGBMQsw\n"\
"CQYDVQQGEwJJTjEMMAoGA1UECAwDXEtBMREwDwYDVQQHDAhCYW5nbG9yZTERMA8G\n"\
"A1UECgwISW5maW5lb24xCzAJBgNVBAsMAkNZMQ0wCwYDVQQDDARteUNBMSIwIAYJ\n"\
"KoZIhvcNAQkBFhNwcmF2aW5AaW5maW5lb24uY29tMB4XDTI0MDQwODA3MjExNloX\n"\
"DTI3MDEwMzA3MjExNlowgYUxCzAJBgNVBAYTAklOMQwwCgYDVQQIDANcS0ExETAP\n"\
"BgNVBAcMCEJhbmdsb3JlMREwDwYDVQQKDAhJbmZpbmVvbjELMAkGA1UECwwCQ1kx\n"\
"ETAPBgNVBAMMCG15Q2xpZW50MSIwIAYJKoZIhvcNAQkBFhNwcmF2aW5AaW5maW5l\n"\
"b24uY29tMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEOGe9cWOlv9i2k1xDcfhE\n"\
"X2KrdmxZdLntsA9uHJA48k09oSUwt/bUPYojm027Kn+OBnFAiRWtNg1LMm2MYXb6\n"\
"rzAKBggqhkjOPQQDAgNIADBFAiBVUyJ3KvqiFtULixi5W2SZTAeFHnKIGiT/jhLz\n"\
"AL+2bAIhAMz157JwkPlFdbKxMcXOwWZJJ276aGDSoiJdfoTVUv7E\n"\
"-----END CERTIFICATE-----\n"

/* Private key of the TCP client. Copy from the TCP client key
 * generated by OpenSSL (See Readme.md on how to create a private key).
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN EC PRIVATE KEY-----\n"\
"MHcCAQEEIBLzz4YaqTjcO/cA8dDCrzCJNku0XJBNqTOayRecnsz5oAoGCCqGSM49\n"\
"AwEHoUQDQgAEOGe9cWOlv9i2k1xDcfhEX2KrdmxZdLntsA9uHJA48k09oSUwt/bU\n"\
"PYojm027Kn+OBnFAiRWtNg1LMm2MYXb6rw==\n"\
"-----END EC PRIVATE KEY-----\n"


/* TCP server certificate. In this example this is the RootCA
 * certificate so as to verify the TCP server's identity. */
#define keySERVER_ROOTCA_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIICWjCCAf+gAwIBAgIUei4kFRyPg1tqQgC453IS1rLS7QwwCgYIKoZIzj0EAwIw\n"\
"gYExCzAJBgNVBAYTAklOMQwwCgYDVQQIDANcS0ExETAPBgNVBAcMCEJhbmdsb3Jl\n"\
"MREwDwYDVQQKDAhJbmZpbmVvbjELMAkGA1UECwwCQ1kxDTALBgNVBAMMBG15Q0Ex\n"\
"IjAgBgkqhkiG9w0BCQEWE3ByYXZpbkBpbmZpbmVvbi5jb20wHhcNMjQwNDA4MDcy\n"\
"MDAwWhcNMjcwMTAzMDcyMDAwWjCBgTELMAkGA1UEBhMCSU4xDDAKBgNVBAgMA1xL\n"\
"QTERMA8GA1UEBwwIQmFuZ2xvcmUxETAPBgNVBAoMCEluZmluZW9uMQswCQYDVQQL\n"\
"DAJDWTENMAsGA1UEAwwEbXlDQTEiMCAGCSqGSIb3DQEJARYTcHJhdmluQGluZmlu\n"\
"ZW9uLmNvbTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABNtlZx0E4yb+2yXy2FKQ\n"\
"T2JOgCLHH126FKFYfm/AuByMvgQBZHSIAgp80rz3ttgrOY9x4r3YdC1tKBILctlH\n"\
"16ijUzBRMB0GA1UdDgQWBBReKAfVraHJbLK8ek775mpchP18ajAfBgNVHSMEGDAW\n"\
"gBReKAfVraHJbLK8ek775mpchP18ajAPBgNVHRMBAf8EBTADAQH/MAoGCCqGSM49\n"\
"BAMCA0kAMEYCIQDAFkUC4CU3q4bpTY4UX3xCfJsPIjOjhHMv09DG2+SomwIhAIQ1\n"\
"wojOQQd/7c2v4mSi7wbmRLEJXi5mGzC7OdvXPcUC\n"\
"-----END CERTIFICATE-----\n"


#endif /* NETWORK_CREDENTIALS_H_ */

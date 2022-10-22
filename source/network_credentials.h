/******************************************************************************
* File Name: network_credentials.h
*
* Description: This file is the public interface for Wi-Fi/Soft-AP credentials and
* TLS credentials.
*
* Related Document: See README.md
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
"MIIDZTCCAk2gAwIBAgIUCB3odAFJqqSzvarpsDycsXVAOlMwDQYJKoZIhvcNAQEL\n"\
"BQAwQjELMAkGA1UEBhMCWFgxFTATBgNVBAcMDERlZmF1bHQgQ2l0eTEcMBoGA1UE\n"\
"CgwTRGVmYXVsdCBDb21wYW55IEx0ZDAeFw0yMjA5MTkwNTA1MTBaFw0yMzA5MTkw\n"\
"NTA1MTBaMEIxCzAJBgNVBAYTAlhYMRUwEwYDVQQHDAxEZWZhdWx0IENpdHkxHDAa\n"\
"BgNVBAoME0RlZmF1bHQgQ29tcGFueSBMdGQwggEiMA0GCSqGSIb3DQEBAQUAA4IB\n"\
"DwAwggEKAoIBAQDUSCHIcQ/EmVPVVasxANetNVIyCmYruz2pP0dGHcMA8cp9YLV8\n"\
"FRg9SvPrGSvxMQBMfJc6dJJFm1SWARpkthPKCk9c0TZJHYiPysEI00TT1cHJZVwQ\n"\
"wv4+YwIoCHxGcBnskSuqF03S2d8F50GkORKBewe3PfeNSK0hG/nV0ysylZQFQc9w\n"\
"05E5v6mlXU5sDeCcXwgOeffiLMkcH5gIlqIy9ZUh+wie4LsQ74F8PML+nkW1a6Ce\n"\
"FvFbtJgxoqIVVswbNctfEs5cjU59T14V4VD4kpRZfYfatKMGr9q0the8virVohWb\n"\
"1d6Qf9rscmhwww5g1vyxCYjUb329OJw+neCHAgMBAAGjUzBRMB0GA1UdDgQWBBSd\n"\
"/own2dVyCfTtq8RLmC09d910gTAfBgNVHSMEGDAWgBSd/own2dVyCfTtq8RLmC09\n"\
"d910gTAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQBSN9hqUtgj\n"\
"6N6GAx5Ru7lLPlxmWw6nGHL6GtYrj878OPuxq9Sp81vpgoCFGQJB+XzbVZtiXIHq\n"\
"bu0ML2KbLFZi2xY6puCTFyz5dPz5JYkvHBkCM/nPb5miOui+ez+DLeRA9fiwoNZ9\n"\
"AYFXMR9EzYCvHmcBNqiVooUZkuORFg++mowZlgDjAJUhCYiK5VKHHdsAonADijUj\n"\
"cVra5iMNNVyGMMd3+j/0wS7MwSpEt9ckKRS+wxaGp+yvGbU/FL3+cy72tp1BuPt9\n"\
"ZixeFmgjizO5V7yNZbBL5+B3DdCAtMuYzMlyOBI4NRDr7YbZFsve1mXGkxjVpW4e\n"\
"7v9U5o9yVYgf\n"\
"-----END CERTIFICATE-----\n"

/* Private key of the TCP client. Copy from the TCP client key
 * generated by OpenSSL (See Readme.md on how to create a private key).
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN PRIVATE KEY-----\n"\
"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDUSCHIcQ/EmVPV\n"\
"VasxANetNVIyCmYruz2pP0dGHcMA8cp9YLV8FRg9SvPrGSvxMQBMfJc6dJJFm1SW\n"\
"ARpkthPKCk9c0TZJHYiPysEI00TT1cHJZVwQwv4+YwIoCHxGcBnskSuqF03S2d8F\n"\
"50GkORKBewe3PfeNSK0hG/nV0ysylZQFQc9w05E5v6mlXU5sDeCcXwgOeffiLMkc\n"\
"H5gIlqIy9ZUh+wie4LsQ74F8PML+nkW1a6CeFvFbtJgxoqIVVswbNctfEs5cjU59\n"\
"T14V4VD4kpRZfYfatKMGr9q0the8virVohWb1d6Qf9rscmhwww5g1vyxCYjUb329\n"\
"OJw+neCHAgMBAAECggEAZSQs/Gxp/9ix6a4Uj5eAKyWBkRgFUAa5PT9J/S1G8NdD\n"\
"C/Oc5I7Easegab4ngpY/NzIRd6d83a9BYOsLoTpjOVsqLuX7QGDS5PfMeyD15Rwu\n"\
"ZX9mmxHcwuq3Z02LsJ/OqjkMndDWooRtz0k8rDsJByoQJg1fOjCLVIAYy/j91u4x\n"\
"V97yIe9oUMTMm+mzXP+3XHUMDjKKCoINKv1HOexJqYBslJSvIyxLiDXHsDY1/J9r\n"\
"0SNOIXhZ/DZOWqvhSq6EsNk5fCUHIM3iK0Vo/lCYrXn1099ubpQYGNy9wC/tdsxD\n"\
"dUNVKVZR5JTxRDvgmd7+qE+pgQcDhvca1KhRKzaPyQKBgQDtXlw/gt6xffH9zt+k\n"\
"GC7q7+QastnhwuiIoWfORMPlqRFb5VtI9UCWO2BLwqc7CRJJCm9me70JZJ9QBqMD\n"\
"J8nL4j9Ba/W7uX95pN9glTefobUe2tlt0KgkUy+AtIjn6YU1t2EKY5MNJuYFu9vi\n"\
"jGW5QVtM74kSgjoxDhbgh2T5tQKBgQDk8a5+EvPD3YG5kqMW6WuR+DtE9R9AlxzF\n"\
"MGklUyVsHuZMEaDsYwx/msG9CLWPrOVjf3Mtgp93l1JS4B6BTUuMeOVmsV14YeZl\n"\
"hi9NK5TihZmOVnMWlmuThp+wi5ZiqI0dFPNPT771bfja9cuA4oG/BXEg2W3dAhx+\n"\
"DLFIg28mywKBgEhm3dBphK+y8Nsv/Ls6vSTgIz2ZjCf2oaL7SIR8KRymIytanCt2\n"\
"00p/tfGl4Ah7zd4FltE1sQVqccWhIJvXyQ+tZQn5eizWefGKvq/hE+RXGL3ely+N\n"\
"05uw2+5wIspKSl2GH81hbfs3ADaDhKBnnqeRLd4buj2xBzrrR0MZSU15AoGBAKWL\n"\
"8O3vDF8b47rpQo7FuGfzhAAH81JEMqSPreg0aEH3UfW9ZYyozpfSsrba/lZm4fQB\n"\
"a6qD4oWaYQfWUZiT6MYpgU+xfvIWcIAG+Fsn4V+u1WtsLYouuJkTZpNFTDgIwwk9\n"\
"ZfZ6po1XuPOzejS3FLSo3bWwI1YFOc8XpHXXvF7jAoGBAOmvU8xhrSzehtwQof1a\n"\
"smiMCTdbuCRNS0FydXMKFflGr2wPDHCHmyiaOU/hWhf0OsqgCTRrLTTIcRt/FlnC\n"\
"lXWSEXnN5cRvwoFPS8oZNn9CVsdibTZizE2JzLfP9AMGcKJrfisRJ1/BVoPlbgf0\n"\
"ETv5IEUCQEjbSaZLQ/T0VW/3\n"\
"-----END PRIVATE KEY-----\n"


/* TCP server certificate. In this example this is the RootCA
 * certificate so as to verify the TCP server's identity. */
#define keySERVER_ROOTCA_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDZTCCAk2gAwIBAgIUPPtbVzaWQ4idal10Oqbo4Vu8vRkwDQYJKoZIhvcNAQEL\n"\
"BQAwQjELMAkGA1UEBhMCWFgxFTATBgNVBAcMDERlZmF1bHQgQ2l0eTEcMBoGA1UE\n"\
"CgwTRGVmYXVsdCBDb21wYW55IEx0ZDAeFw0yMjA5MTkwNDM5MjdaFw0yMzA5MTkw\n"\
"NDM5MjdaMEIxCzAJBgNVBAYTAlhYMRUwEwYDVQQHDAxEZWZhdWx0IENpdHkxHDAa\n"\
"BgNVBAoME0RlZmF1bHQgQ29tcGFueSBMdGQwggEiMA0GCSqGSIb3DQEBAQUAA4IB\n"\
"DwAwggEKAoIBAQDP6UHUHAZqezN4fk2cObpmpcfHjHeDJC2LeTRj9M10VuLyglft\n"\
"PMLl6JuE+NC8zDIreTFCW8sbXfXbsr2abGy4gU9Lak+KsMEHD9xWYIiG+UaHcT6K\n"\
"uayw1p23lUITNW4MGAkIfIzTUr9in9o5o5vX/YGDG1e3zZdnbjyGPmYmWCaICEEu\n"\
"PNVcjgWyJbJsLWWD1zWgGYfwRqdIGW27Dz8d+dNDrL4qWcj10TSdbLS91NEz2VN+\n"\
"qiGM04e1FiDzAshb3aru7Tc3YDgJ9C/BMJ2TEoHpxeMm6vowbp01mvrOAtCTPwFr\n"\
"LGUfkajOPl8uidSSTNABFjDo0grb0+lS9YWTAgMBAAGjUzBRMB0GA1UdDgQWBBTS\n"\
"WdG8cQyFcMIKcHv31zS6gVcgTDAfBgNVHSMEGDAWgBTSWdG8cQyFcMIKcHv31zS6\n"\
"gVcgTDAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQAfjgz09KG+\n"\
"9bZSzDgu3JotZDP5hqZfvUBPPjYgCEsX7OwilxMpFbybc3KAd2bLnNPMiJjBMgu/\n"\
"kN2QlPoUuGY6hM2dlEoWYr9BCZuEmELIublg5GXZVq1/R5ukeo7q3Zy64rihrYtv\n"\
"FKV3sx5ciEnEvlZWOdXwdxDpLDLAiW6t6ckUO8L+OFHq7BBHOu/XP3Xu4XX1w249\n"\
"W5vYFT7+qu0bMXnGEkCGgNghlrnxj0+jxd8fWU6OfAE0BJ7J6xglqAKHf2G3B81c\n"\
"ChsZMFBJ7wMKI2n/kFmc+HFAlkNR84d5fcU6w8nrCytq4RbiVd/zJGTFCW8K/KfZ\n"\
"Tp7CXJ/yJUQG\n"\
"-----END CERTIFICATE-----\n"


#endif /* NETWORK_CREDENTIALS_H_ */

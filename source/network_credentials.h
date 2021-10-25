/******************************************************************************
* File Name: network_credentials.h
*
* Description: This file is the public interface for Wi-Fi/Soft-AP credentials and
* TLS credentials.
*
* Related Document: See README.md
*
*******************************************************************************
* Copyright 2019-2021, Cypress Semiconductor Corporation (an Infineon company) or
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
"MIIDXTCCAkWgAwIBAgIJANovoG8KgaO5MA0GCSqGSIb3DQEBCwUAMEUxCzAJBgNV\n"\
"BAYTAkFVMRMwEQYDVQQIDApTb21lLVN0YXRlMSEwHwYDVQQKDBhJbnRlcm5ldCBX\n"\
"aWRnaXRzIFB0eSBMdGQwHhcNMjEwODIwMDgwNTM2WhcNMjIwODIwMDgwNTM2WjBF\n"\
"MQswCQYDVQQGEwJBVTETMBEGA1UECAwKU29tZS1TdGF0ZTEhMB8GA1UECgwYSW50\n"\
"ZXJuZXQgV2lkZ2l0cyBQdHkgTHRkMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIB\n"\
"CgKCAQEAu85FvtjQqktjqepm0IE+Npj4Je/JylEJNPfEavvYn7LOCAjIh+n2fV9G\n"\
"rq4s5sO5DV1ctenRtIoMlT4HL6f2or/0hfPnG4IDNZRFi+NwGf67wFuvRPOc8lnY\n"\
"QrGMAKJx+l2SNby8SsjCwwmAM3iAuzPPGRn9whPJfy/D46oHN3yHfXpGRaGQCZbK\n"\
"1RJ31XOS6A4q80wef5DPz4YYLFROFuS+lC5oHsOjDDNHbhz6W9D1dPvV0MMLbMoL\n"\
"tRaeE8R2y/AkLm+2yum5xC2kMN4ZgBCOFbtmUbI92tDXTnV/yAu0GQ2DHZIIoHaQ\n"\
"rlJaZOz+RTBSJ6Ir3Sro0UkLWAkbsQIDAQABo1AwTjAdBgNVHQ4EFgQURJQssHJl\n"\
"GfLSHOE0uaWBTdn3YDwwHwYDVR0jBBgwFoAURJQssHJlGfLSHOE0uaWBTdn3YDww\n"\
"DAYDVR0TBAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAWX7Iid2vJCzxY7ADMoFu\n"\
"SyigePc9A3EuM+1UbvIDqpiIpXvCGZwpbJ64Kf8D1rYCJxKz9l4f+7j/MgG+qaFE\n"\
"UuDsfEcnPh+SVgn2PrzOSL4I9tCOquIkUZ4RXoYbJqb912EKz2sU2RT3szE3d5Qx\n"\
"jNqtnAMwffGmgLNpyCP0DLZ8VgTjLE0fw8sXJvvnB0Ez0CS4JIV+lzFLYIIap7KB\n"\
"H3rWLlJmrPhenNkYkDLDPpC7kg1yxgzAH7VTuDjo37eosSjvMbjk2SKAFwe/aYvt\n"\
"8wSqH9jsWFKCGgxIAwoKDpydrF5jVoFZ9Ge87pUi+ayHf+zzEydbVYgyh33ytigP\n"\
"qw==\n"\
"-----END CERTIFICATE-----\n"

/* Private key of the TCP client. Copy from the TCP client key
 * generated by OpenSSL (See Readme.md on how to create a private key).
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN PRIVATE KEY-----\n"\
"MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC7zkW+2NCqS2Op\n"\
"6mbQgT42mPgl78nKUQk098Rq+9ifss4ICMiH6fZ9X0aurizmw7kNXVy16dG0igyV\n"\
"Pgcvp/aiv/SF8+cbggM1lEWL43AZ/rvAW69E85zyWdhCsYwAonH6XZI1vLxKyMLD\n"\
"CYAzeIC7M88ZGf3CE8l/L8Pjqgc3fId9ekZFoZAJlsrVEnfVc5LoDirzTB5/kM/P\n"\
"hhgsVE4W5L6ULmgew6MMM0duHPpb0PV0+9XQwwtsygu1Fp4TxHbL8CQub7bK6bnE\n"\
"LaQw3hmAEI4Vu2ZRsj3a0NdOdX/IC7QZDYMdkgigdpCuUlpk7P5FMFInoivdKujR\n"\
"SQtYCRuxAgMBAAECggEASukrPsXC7bpmhZce7Zov051OletApTePoZYWvcm5DXJH\n"\
"5kKColv7WuTPD8wf0uhM/vy3h0Q9xnKuNDVqrmKj6SUCBxBTpdBFMXD0EKlmxKes\n"\
"Aj1P+wPlHXIi5e9l9bbWGdSLBm5C+N19ekhm36D4UDOJLu0EIA6+d8H4s+3VNRcC\n"\
"bXKfqmbR8HLfzbemPx4Yg1vKDgdFoNvixrZkwNzowuvcdypMkLsovlkYsqfQlQBR\n"\
"MfuStsmECmnuf1Q+Z7Qs/0DynSMMf2nw6HX6oTUIepmjYPb9lCtk9jK8UdJ2Nc5X\n"\
"IPGwCR/U1TPd9MgrIu4Dr8PQk5Mcqws7qvZCKGkoMQKBgQDvBCrtsU82aOSrOaoF\n"\
"/Cnas5TNpmkM+rApAJRQULY6b9ApvnMkyj1YwEEIV37cbLKTdcGG2UBYrs9JZesx\n"\
"F1viKmURqVWGWL6vAUFKq1GTiqrOx4/SCwyxN9X3cKqytgfMrwGM3xwK6m8lhdws\n"\
"kOMaOTJ+W0MT9ln6Thb2YNBpJQKBgQDJJo7m2j1Apx8yKLob+dEuOe+F9n1Schbm\n"\
"GtG+OpL8JCas1l7PO7s1CnExd/me7grdA6gP5Wakj/3dQdWDkboo2rcw+bif7Otu\n"\
"3KuWX7O82ilun9SwopMChP8joPhAEUZ/T7cL7XlFq4YjmArZGQ78qK9kOOuuERB2\n"\
"RYUOpIQgnQKBgGAE9Jn4mTHqgbKnv74Xx1isvCLBr4IfU5WlPe/l/M8NDDs431jw\n"\
"RiTZV0ban4Q9xp+mttBNhqQZ1fxOjWVzVN5O2bt2o30NOc1kW657lJIJKwVW9lgT\n"\
"SE4JeFOnV2vj5M49oAnPt5xLAcu5MvJUYmeugrJwR0pFtW/w3xirXA5hAoGBAK81\n"\
"i9HflO0E5TJusTV/E8q9IjrA6oZu5C1IfRvCr5c68gkorOq7r6RS1Sfuxhq+Y+4B\n"\
"qlk2S4LZ/ZnFJ3Lz84B0io75Zey/lI87Xaac89Vy/hXi2IOHCKBwMkDZjINZyNtK\n"\
"FzonfrPF5RCJ9iEGJ7zCPgwBXKCBMqKiiXSoroItAoGAPq+YvXimi6fAHYSOxbm1\n"\
"p2Q0iemT+q3tUaUdYeRxGmBIk4OG9FfaowN0IvBKqzCzEheNlTso2/Mqu4E57vuk\n"\
"vikNRXiRvu5lm/Q98Qa5AWzjLZ3zSfUdhqg4kFe86jlgwrpoQWzl5p9cFnWavPzt\n"\
"pQcOTQ6b+uSM8NDB3akm2xY=\n"\
"-----END PRIVATE KEY-----\n"



/* TCP server certificate. In this example this is the RootCA
 * certificate so as to verify the TCP server's identity. */
#define keySERVER_ROOTCA_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDXTCCAkWgAwIBAgIJAMqhDN/tUBXVMA0GCSqGSIb3DQEBCwUAMEUxCzAJBgNV\n"\
"BAYTAkFVMRMwEQYDVQQIDApTb21lLVN0YXRlMSEwHwYDVQQKDBhJbnRlcm5ldCBX\n"\
"aWRnaXRzIFB0eSBMdGQwHhcNMjEwODE5MTExOTU0WhcNMjIwODE5MTExOTU0WjBF\n"\
"MQswCQYDVQQGEwJBVTETMBEGA1UECAwKU29tZS1TdGF0ZTEhMB8GA1UECgwYSW50\n"\
"ZXJuZXQgV2lkZ2l0cyBQdHkgTHRkMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIB\n"\
"CgKCAQEAyIEP0iuIKQkBvDV58Xkv/Ia9mLOAL/5jrulfkDYLx7Hl8llBfCAtlAQd\n"\
"KQRbhmRv1prgRdvn0mkykr15BVPgBGC+27FW1+M1jtRxzpSvfknX8hRAA0Jh4zwZ\n"\
"2tF1vNq9JQWEuPDfawpFiShIg1C8DJ/GVeakbU12BA088xsCKWqvVWtZ9Vqespuc\n"\
"bLa27l4z0iVMUAECMU+sztrruYMQf8C2wIa3ZAclIt7tL4Nkm7S928YF77fMPdl8\n"\
"nv08G5OHzSJN9RNqf/UDoy1kBGSdFI6L7aTeqgyBPhzWBDXdIm6otUwfOeXsbYRy\n"\
"yxP5Am3c0dSvGCIiTEyuhzF0unxQHwIDAQABo1AwTjAdBgNVHQ4EFgQUY2NDL36s\n"\
"dGvkA4unf+0kHFKHevQwHwYDVR0jBBgwFoAUY2NDL36sdGvkA4unf+0kHFKHevQw\n"\
"DAYDVR0TBAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAUcCHz74R/kB19V8oQmwl\n"\
"ahF1C9RpTlciTy0NhaMiBFS34WvC0I5iXLzY0tnZodfUUF8oI1AspLcTxfL/HrUh\n"\
"Xunus1DKek9ZMp/G5W7Qc3+A/53m266M6BVWaCrs7y5BJlzOkPMLRBhaQa7vBIBP\n"\
"pHC1mKvkBppLAUk4NV/hAGqVonoeFKpC3qE+tZmufEcygklgB+M347Le2crxUcdL\n"\
"/f0Fw082e96Sw3HVPJmGCdACaNeBWai4ydE9R1dLacajFB8KYD+Gt0qkvrHnlK7h\n"\
"oBZsbXfHZrZoBqjYzKY2s2Js0w19O2D2FVcjZEfF3HuEQI0c19VuAcjPL5Bd8Mw0\n"\
"VQ==\n"\
"-----END CERTIFICATE-----\n"


#endif /* NETWORK_CREDENTIALS_H_ */

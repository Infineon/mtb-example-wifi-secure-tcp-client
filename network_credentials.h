/******************************************************************************
* File Name: network_credentials.h
*
* Description: This file is the public interface for Wi-Fi credentials and
* TCP server certificate
*
* Related Document: See README.md
*
******************************************************************************
* Copyright (2019), Cypress Semiconductor Corporation.
******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death (“High Risk Product”). By
* including Cypress’s product in a High Risk Product, the manufacturer of such
* system or application assumes all risk of such use and in doing so agrees to
* indemnify Cypress against all liability.
*****************************************​**************************************/


/*******************************************************************************
* Include guard
*******************************************************************************/
#ifndef NETWORK_CREDENTIALS_H_
#define NETWORK_CREDENTIALS_H_

/* Wi-Fi Credentials: Modify WIFI_SSID and WIFI_KEY to match your Wi-Fi network
 * Credentials.
 */
#define WIFI_SSID                         "MY-WIFI-SSID"
#define WIFI_PASSWORD                     "MY-WIFI-PASSWORD"

/* TCP server certificate. */
static const char tcp_server_cert[] =
"-----BEGIN CERTIFICATE-----\n"
"MIIDhTCCAm0CFHpvc/v8K67YWp7SkKZ+U8UgDBvRMA0GCSqGSIb3DQEBCwUAMH8x\n"
"CzAJBgNVBAYTAklOMRIwEAYDVQQIDAlLYXJuYXRha2ExGDAWBgNVBAcMD0Jlbmdh\n"
"bHVydRtbQxtbRDEQMA4GA1UECgwHQ3lwcmVzczEUMBIGA1UECwwLRW5naW5lZXJp\n"
"bmcxGjAYBgNVBAMMEW15dGNwc2VjdXJlc2VydmVyMB4XDTE5MTIwNTA1MjUwMloX\n"
"DTIwMTIwNDA1MjUwMlowfzELMAkGA1UEBhMCSU4xEjAQBgNVBAgMCUthcm5hdGFr\n"
"YTEYMBYGA1UEBwwPQmVuZ2FsdXJ1G1tDG1tEMRAwDgYDVQQKDAdDeXByZXNzMRQw\n"
"EgYDVQQLDAtFbmdpbmVlcmluZzEaMBgGA1UEAwwRbXl0Y3BzZWN1cmVzZXJ2ZXIw\n"
"ggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDbYpG/jopHvy6j2ln5Dbxg\n"
"XaQRwu/kHAE9WuxA6svYPWcZ5txqXvP1hPjVPsU74lxc/ckZlgSGspMc/ubc/BFS\n"
"LoZ6Br5IjzpGx0nxA2g7Rb2EzSKhVoZDqc356S3lBFnf6quKfAlqKSAbv3uvjTbt\n"
"up0Fnb0rZnMIBrZHQf5m/KMmDmlYHkEPVRXlx3UvNx2v2+22ktdD86R7AOPjjopo\n"
"M9963Z24pQ6QRA7MrDiAFG7ajKrPwJpbJ5DgzD72+LSIPjejKeFiP5S3LgUvPXv8\n"
"neQ3UdXCY/8M44yULhKRlhKIk+B5vwBWfm8IxAfJCsktREomUM0jGoJScljVJmul\n"
"AgMBAAEwDQYJKoZIhvcNAQELBQADggEBAAqyZAIRhNJumQnLM0Kke8lobUpBS0Cq\n"
"kSaC1zQIQ8w6ruVAXVMohE9DFQbBk7OgX8HxUzDUQIL6h9i2knF0dNseKSFvul4w\n"
"4I6eYopg/jsTmEkWOgcw9bXb7ibJDjmxSOx9nPXy7ouyqw1/jMlEqAZ8l8hWMYA+\n"
"fsdkah64dvGTLfhyXpOtF/TUjhLG4A3y6VMTJcZhWbqmIBaY45u9c6nRksM/5ZX9\n"
"B6PWtpHE5Q4GfQJavgnlLhaOOTuznhssBKIMzTFivAA35RYL5btRsQkKu/2oALP4\n"
"yg+tikuvKL2cuAHvFmHbAlJcn5wsTMBLb5AU6pacdtS0uPvsD5QHEgM=\n"
"-----END CERTIFICATE-----\n";

#endif /* NETWORK_CREDENTIALS_H_ */

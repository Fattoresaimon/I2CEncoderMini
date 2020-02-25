/**
 * \file
 *
 * \brief EVSYS related functionality implementation.
 *
 (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/**
 * \addtogroup doc_driver_evsys
 *
 * \section doc_driver_evsys_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */
#include <evsys.h>

/**
 * \brief Initialize EVSYS interface
 *
 * \return Initialization status.
 */
int8_t EVENT_SYSTEM_0_init()
{

	// EVSYS.ASYNCCH0 = EVSYS_ASYNCCH0_OFF_gc; /* Off */

	// EVSYS.ASYNCCH1 = EVSYS_ASYNCCH1_OFF_gc; /* Off */

	EVSYS.ASYNCUSER0 = EVSYS_ASYNCUSER0_SYNCCH0_gc; /* Synchronous Event Channel 0 */

	// EVSYS.ASYNCUSER1 = EVSYS_ASYNCUSER1_OFF_gc; /* Off */

	// EVSYS.ASYNCUSER2 = EVSYS_ASYNCUSER2_OFF_gc; /* Off */

	// EVSYS.ASYNCUSER3 = EVSYS_ASYNCUSER3_OFF_gc; /* Off */

	// EVSYS.ASYNCUSER4 = EVSYS_ASYNCUSER4_OFF_gc; /* Off */

	// EVSYS.ASYNCUSER5 = EVSYS_ASYNCUSER5_OFF_gc; /* Off */

	// EVSYS.ASYNCUSER6 = EVSYS_ASYNCUSER6_OFF_gc; /* Off */

	// EVSYS.ASYNCUSER7 = EVSYS_ASYNCUSER7_OFF_gc; /* Off */

	// EVSYS.ASYNCUSER8 = EVSYS_ASYNCUSER8_OFF_gc; /* Off */

	// EVSYS.ASYNCUSER9 = EVSYS_ASYNCUSER9_OFF_gc; /* Off */

	// EVSYS.ASYNCUSER10 = EVSYS_ASYNCUSER10_OFF_gc; /* Off */

	// EVSYS.SYNCCH0 = EVSYS_SYNCCH0_OFF_gc; /* Off */

	// EVSYS.SYNCUSER0 = EVSYS_SYNCUSER0_OFF_gc; /* Off */

	return 0;
}

 /*
 * common_funcs.h
 *
 *  Created on: 03-Sep-2016
 *      Author: Tarang
 */

#ifndef COMMON_FUNCS_H_
#define COMMON_FUNCS_H_

#include "commondef.h"


void UARTInterruptHandler(void);

bool checksumValid(uint8_t* packet);

bool isPacketAvailable();



#endif /* COMMON_FUNCS_H_ */

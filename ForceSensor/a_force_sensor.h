/*
 * ForceSensor.h
 *
 *  Created on: 25-Jul-2016
 *      Author: Tarang
 */

#ifndef HALCLASSES_FORCESENSOR_FORCESENSOR_H_
#define HALCLASSES_FORCESENSOR_FORCESENSOR_H_

class ForceSensor {
public:
	ForceSensor();
	virtual ~ForceSensor();
	virtual double getTorque() = 0;
};

#endif /* HALCLASSES_FORCESENSOR_FORCESENSOR_H_ */

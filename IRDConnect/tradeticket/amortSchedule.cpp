/*
 * amortSchedule.cpp
 *
 *  Created on: 08-Nov-2010
 *      Author: vishist
 */

#include "amortSchedule.h"

using namespace IRDConnect;

AmortSchedule::AmortSchedule()
{
	// nothing to be done
}

AmortSchedule::AmortSchedule (

double 		amortNotional,
Date 		endDate,
Date 		startDate)

{
_amortNotional 	= amortNotional;
_endDate 		= endDate;
_startDate 		= startDate;


}

AmortSchedule::~AmortSchedule()
{
	// do nothing
}

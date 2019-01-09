/*
 * resetSchedule.cpp
 *
 *  Created on: 06-Oct-2010
 *      Author: vishist
 */



#include<iostream>

#include "resetSchedule.h"

using namespace IRDConnect;

ResetSchedule::ResetSchedule()
{
	// do nothing for now
}

ResetSchedule::ResetSchedule(
Date  	quoteDate,
double 	rate,
String 	rateIndexType,
String 	rateSettingType,
Date 	resetStartDate,
Date 	resetEndDate

)
{

_quoteDate 			=	quoteDate;
_rate 				=	rate;
_rateIndexType 		= 	rateIndexType;
_rateSettingType 	=	rateSettingType;
_resetStartDate 	=	resetStartDate;
_resetEndDate 		=	resetEndDate;
}



ResetSchedule::~ResetSchedule()
{
	// do nothing for now
}




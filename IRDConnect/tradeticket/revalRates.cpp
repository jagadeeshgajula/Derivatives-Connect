/*
 * revalRates.cpp
 *
 *  Created on: 12-Nov-2010
 *      Author: vishist
 */

#include <iostream>
#include "revalRates.h"
using namespace std;

using namespace IRDConnect;

RevalRates::RevalRates(

String 		checkerId,
Date 		checkerTimestamp,
Date 		currentDate,
String 		makerId,
Date 		makerTimestamp,
Date 		quoteDate,
String 		quoteId,
String 		quoteType,
double 		rate,
String 		ratesetMode,
double 		tolerance
 )
{
_checkerId			=	checkerId;
_checkerTimestamp	=	checkerTimestamp;
_currentDate		=	currentDate;
_makerId			=	makerId;
_makerTimestamp		=	makerTimestamp;
_quoteDate			=	quoteDate;
_quoteId			=	quoteId;
_quoteType			=	quoteType;
_rate				=	rate;
_ratesetMode		=	ratesetMode;
_tolerance			=	tolerance;
}

RevalRates::~RevalRates()
{
	//do nothing
}


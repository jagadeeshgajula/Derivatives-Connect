/*
 * stubResets.cpp
 *
 *  Created on: 17-Aug-2010
 *      Author: vishist
 */

#include <iostream>
#include "stubResets.h"

using namespace std;

using namespace IRDConnect;

StubResets::StubResets (
Date 		quoteDate,
Date 		startDate,
String 		stubMarketIndex,
double 		stubRate,
String 		stubRateType,
Period		stubTenor,
String 		stubType )
{

_quoteDate			= quoteDate;
_startDate			= startDate;
_stubMarketIndex	= stubMarketIndex;
_stubRate			= stubRate;
_stubRateType		= stubRateType;
_stubTenor			= stubTenor;
_stubType			= stubType;

}

StubResets::~StubResets()
{

	// do nothing

}

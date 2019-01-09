/*
 * fXResets.cpp
 *
 *  Created on: 17-Aug-2010
 *      Author: vishist
 */

#include <iostream>
#include "fxReset.h"


using namespace std;

using namespace IRDConnect;

FXReset::FXReset()
{
	// do nothing
}

FXReset::FXReset(
std::set < std::string >  fxQuoteCalendars,
String 		fXResetType, // manual or auto
int 		fxResetLegNo,
String 		fxMarketIndex,
double		initialFXRate,
Frequency	fxResetFreq,
int			fxResetQuoteLag
)

{

_fxQuoteCalendars	=	fxQuoteCalendars;
_fXResetType		=	fXResetType;
_fxResetLegNo		=	fxResetLegNo;
_fxMarketIndex		=	fxMarketIndex;
_initialFXRate		= 	initialFXRate;
_fxResetFreq		= 	fxResetFreq;
_fxResetQuoteLag 	= 	fxResetQuoteLag;
}

FXReset::~FXReset()
{
	// do nothing
}

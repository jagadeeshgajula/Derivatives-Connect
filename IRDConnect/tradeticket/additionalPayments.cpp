/*
 * manualPayments.cpp
 *
 *  Created on: 17-Aug-2010
 *      Author: vishist
 */

#include <iostream>
#include "additionalPayments.h"

using namespace std;
using namespace IRDConnect;

AdditionalPayments::AdditionalPayments(
double 				amount,
String				comment,
const Currency * 	conversionCurrency,
String 				conversionIndex,
int 				conversionLag,
const Currency * 	currency,
String				customerAccount,
String				firmAccount,
Date 				paymentDate,
String 				payReceive,
int					payRef,
String 				paymentType,
String				thirdPartyType,
String				thirdPartyName)
{
_amount 			=	amount;
_comment			= 	comment;
_conversionCurrency	=	conversionCurrency;
_conversionIndex	=	conversionIndex;
_conversionLag		=	conversionLag;
_currency			=	currency;
_customerAccount	=	customerAccount;
_firmAccount		= 	firmAccount;
_paymentDate		=	paymentDate;
_payReceive			=	payReceive;
_payRef				=   payRef;
_paymentType		=	paymentType;
_thirdPartyType		=	thirdPartyType;
_thirdPartyName		=	thirdPartyName;
}

AdditionalPayments::~AdditionalPayments()
{
	// nothing to do
}

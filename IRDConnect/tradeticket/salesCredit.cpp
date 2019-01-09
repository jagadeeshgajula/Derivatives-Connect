/*
 * salesCredit.cpp
 *
 *  Created on: 19-Mar-2011
 *      Author: vishist
 */

#include "salesCredit.h"

using namespace IRDConnect;

SalesCredit::SalesCredit()
{
	// do nothing
}

SalesCredit::SalesCredit
(
		String				evType,
		Date				evDate,
		double				amount,
		const Currency * 	ccy,
		String 				firmAccount,
		String				customerAccount,
		String				salesPerson,
		String				comment
)
{

_evType				= evType;
_evDate				= evDate;
_amount				= amount;
_ccy				= ccy;
_firmAccount 		= firmAccount;
_customerAccount	= customerAccount;
_salesPerson		= salesPerson;
_comment			= comment;
}

SalesCredit::~SalesCredit()
{
	// do nothing
}

/*
 * tradeMargin.cpp
 *
 *  Created on: 20-Mar-2011
 *      Author: vishist
 */

#include "tradeMargin.h"


using namespace IRDConnect;
using namespace std;

TradeMargin::TradeMargin()
{
	// do nothing as it is default ctr
}

TradeMargin::~TradeMargin()
{
	// do nothing as it is default des ctr
}


TradeMargin::TradeMargin(
		String 				marginType,
		double				amount,
		const Currency * 	ccy,
		String 				varEligible )
{

_marginType		= marginType;
_amount			= amount;
_ccy			= ccy;
_varEligible	= varEligible;

}

/*
 * mmFutureOption.cpp
 *
 *  Created on: 07-Nov-2010
 *      Author: vishist
 */

#include "mmFutureOption.h"

MMFutureOption::MMFutureOption (
String   		alternateRef,
String  		bookingType,
String			buyOrSell,
String  		contract,
String  		customerAccount,
Date  			earlyTermDate,
String  		earlyTermReason,
String  		externalRef,
String  		externalSystem,
String  		firmAccount,
String  		flowStatus,
String  		lastModifiedBy,
String  		lastVerifiedBy,
String 			legalEntity,
String  		location,
String  		matchingStatus,
Date  			terminationDate,
String  		modifiedTimeStamp,
String  		operationsRef,
String  			originalTradeRef,
String  		productType,
double			quantity,
String 			salesPerson,
Date  			effectiveDate,
String  		subType,
Date  			tradeDate,
double  		tradePrice,
String  		trader,
String  		tradeRef,
String			tradeRemarks,
String 			tradeStatus,
String 			tradeType,
double			tradeVersion,
String			verifiedTimeStamp,
String 			washAccount ):

TradeTicket(
		                 alternateRef,
						 bookingType,
						 customerAccount,
						 earlyTermDate,
						 earlyTermReason,
						 externalRef,
						 externalSystem,
				 	 	 firmAccount,
				 	 	 flowStatus,
				 	 	 lastModifiedBy,
				 	 	 lastVerifiedBy,
				 	 	 legalEntity,
				 	 	 location,
						 matchingStatus,
						 terminationDate,
				 	 	 modifiedTimeStamp,
				 	 	 operationsRef,
						 originalTradeRef,
				 	 	 productType,
				 	 	 salesPerson,
				 	 	 effectiveDate,
				 	 	 subType,
				 	 	 tradeDate,
				 	 	 trader,
				 	 	 tradeRef,
				 	 	 tradeRemarks,
				 	 	 tradeStatus,
				 	 	 tradeType,
				 	 	 tradeVersion,
				 	 	 verifiedTimeStamp,
				 	 	 washAccount),_contract(contract), _buyOrSell(buyOrSell), _quantity(quantity), _tradePrice(tradePrice)
{

// work is done already
}

MMFutureOption::~MMFutureOption ()
{
	//do nothing
}

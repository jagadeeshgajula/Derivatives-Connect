#ifndef BONDFUTUREOPTION_H
#define BONDFUTUREOPTION_H

#include "irdString.h"
#include "tradeTicket.h"
#include "date.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class BondFutureOption : public TradeTicket
{

public:


BondFutureOption (
		String   		alternateRef,
		String  		bond,
		String  		bookingType,
		String		    buyOrSell,
		String  		contract,// Future related fields starting
		String  		customerAccount,
		Date  		 	earlyTermDate,
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
		String 			originalTradeRef,
		String  		productType,
		double			quantity,
		String 			salesPerson,
		Date  			effectiveDate,
		String  		subType,
		Date  			tradeDate,
		double  		tradePrice,
		String  		trader,
		String  		tradeRef,
		String  		tradeRemarks,
		String 			tradeStatus,
		String 			tradeType,
		double			tradeVersion,
		String			verifiedTimeStamp,
		String			washAccount);

virtual ~BondFutureOption();

String getContract() { return _contract; };
void setContract(String contract) { _contract = contract; };

String getBond() { return _bond; };
void setBond(String bond) { _bond = bond; };

String getBuyOrSell() { return _buyOrSell; };
void setBuyOrSell(String buyOrSell) { _buyOrSell = buyOrSell; };

double getQuantity() { return _quantity; };
void setQuantity(double quantity) { _quantity = quantity; };

double getTradePrice() { return _tradePrice; };
void setTradePrice(double tradePrice) { _tradePrice = tradePrice; };

protected:
String 		_bond;
String 		_buyOrSell;
String 		_contract;
double 		_quantity;
double 		_tradePrice;

};
}



#endif // BONDFUTUREOPTION_H

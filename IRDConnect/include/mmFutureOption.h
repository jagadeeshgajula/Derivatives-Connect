#ifndef MMFUTUREOPTION_H
#define MMFUTUREOPTION_H

#include "irdString.h"
#include "tradeTicket.h"
#include "date.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class MMFutureOption : public TradeTicket
{

public:

MMFutureOption (
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
		String  		tradeRemarks,
		String 			tradeStatus,
		String 			tradeType,
		double			tradeVersion,
		String			verifiedTimeStamp,
		String 			washAccount);

virtual ~MMFutureOption();

String getContract() { return _contract; };
void setContract(String contract) { _contract = contract; };

String getBuyOrSell() { return _buyOrSell; };
void setBuyOrSell(String buyOrSell) { _buyOrSell = buyOrSell; };

double getQuantity() { return _quantity; };
void setQuantity(double quantity) { _quantity = quantity; };

double getTradePrice() { return _tradePrice; };
void setTradePrice(double tradePrice) { _tradePrice = tradePrice; };


protected:

String 		_contract;
String 		_buyOrSell;
double 		_quantity;
double 		_tradePrice;

};




}





#endif // MMFUTUREOPTION_H

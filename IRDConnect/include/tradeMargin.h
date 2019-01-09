#ifndef TRADEMARGIN_H
#define TRADEMARGIN_H

#include "irdString.h"
#include "currency.h"


using namespace IRDConnect;
using namespace std;

namespace IRDConnect
{

class TradeMargin
{

public:

TradeMargin();

~TradeMargin();

TradeMargin(
String 				marginType,
double				amount,
const Currency * 	ccy,
String 				varEligible
);


String getMarginType() { return _marginType; };
void setMarginType(String marginType) { _marginType = marginType; };

double getAmount() { return _amount; };
void setAmount(double amount) { _amount = amount ; };

const Currency * getCcy() { return _ccy; };
void setCurrency(const Currency * ccy) { _ccy = ccy; };

String getVarEligible() { return _varEligible; };
void setVarEligible(String varEligible) { _varEligible = varEligible; };


private:

String 				_marginType;
double				_amount;
const Currency * 	_ccy;
String 				_varEligible;
};

}
#endif // TRADEMARGIN_H finished

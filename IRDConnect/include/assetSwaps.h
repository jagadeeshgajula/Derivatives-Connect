#include<iostream>
#include<string>
#include "irdString.h"
#include "date.h"
#include "currency.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class AssetSwaps
{

public:
AssetSwaps();
AssetSwaps(
double  	accruedInterest,
String 		bondId,
Currency * 	currency,
String 		issuer,
int 		legNo,
Date  		maturityDate,
String 		market,
String 		tradeRef,
double 		yield)
{

_accruedInterest = accruedInterest;
_bondId          = bondId;
_currency        = currency;
_issuer          = issuer;
_legNo			 = legNo;
_maturityDate    = maturityDate;
_market			 = market;
_tradeRef		 = tradeRef;
_yield           = yield;
}

double getAccruedInterest() {return _accruedInterest;}     
void setAccruedInterest(double accruedInterest) { _accruedInterest = accruedInterest; }

String getBondId(){return _bondId;}
void setBondId(String bondId){ _bondId = bondId;}

Currency * getCurrency(){return _currency;}
void setCurrency(Currency * currency){ _currency = currency;}

String getIssuer(){return _issuer;}
void setIssuer (String issuer ){ _issuer = issuer ;}

int getLegNo() {return _legNo;}
void setLegNo(int legNo) { _legNo = legNo; }

Date getMaturityDate(){return _maturityDate;}
void setMaturityDate(Date maturityDate){ _maturityDate = maturityDate;}

String getMarket(){return _market;}
void setMarket(String market){ _market = market;}

String getTradeRef(){return _tradeRef;}
void setTradeRef (String tradeRef ){ _tradeRef = tradeRef ;}

double getYield(){return _yield;}
void setYield (double yield ){ _yield=yield ;}

protected:

double 		_accruedInterest;
String 		_bondId;
Currency * 	_currency;
String 		_issuer;
int 		_legNo;
Date 		_maturityDate;
String 		_market;
String 		_tradeRef;
double 		_yield;
};
  
}

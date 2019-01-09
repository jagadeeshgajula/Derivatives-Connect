#ifndef PREMIUMS_H
#define PREMIUMS_H
#include <iostream>
#include "irdString.h"
#include "date.h"
#include "currency.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class   Premiums
{

public:


Premiums (
double  			amount,
const Currency *    currency,
Date   				paymentDate,
String  			payReceive,
double    			premiumBP,
String    			premiumType
);

virtual ~Premiums();

double getAmount () {return _amount ;}
void setAmount( double amount) { _amount = amount;}

const Currency *  getCurrency () {return _currency;}
void     setCurrency(const Currency * currency) {_currency = currency;}

Date getPaymentDate () {return _paymentDate;}
void setPaymentDate(Date paymentDate) { _paymentDate = paymentDate;}

String getPayReceive() {return _payReceive;}
void setPayReceive(String payReceive) { _payReceive = payReceive;}

double getPremiumBP () {return _premiumBP;}
void setPremiumBP (double premiumBP) { _premiumBP = premiumBP;}

String  getPremiumType () {return _premiumType;}
void setPremiumType(String premiumType) { _premiumType = premiumType;}

protected:

double  			_amount;
const Currency *    _currency;
Date        		_paymentDate;
String  			_payReceive;
double        		_premiumBP;
String  			_premiumType;
          

};

}

#endif // PREMIUMS_H

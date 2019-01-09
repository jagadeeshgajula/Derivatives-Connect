#ifndef ADDITIONALPAYMENTS_H
#define ADDITIONALPAYMENTS_H
#include<iostream>
#include<string>
#include "irdString.h"
#include "date.h"
#include "currency.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {
 

class AdditionalPayments
{

public:

AdditionalPayments(){;};
AdditionalPayments(
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
String				thirdPartyName);

virtual ~AdditionalPayments();


double getAmount (){return _amount;}     
void setAmount(double amount) { _amount = amount; }

const Currency * getCurrency(){return _currency;}
void setCurrency(const Currency * currency){ _currency = currency;}

String getConversionIndex(){return _conversionIndex;}
void setConversionIndex (String conversionIndex){ _conversionIndex = conversionIndex ;}

const Currency * getConversionCurrency() {return _conversionCurrency;}
void setConversionCurrency(const Currency * conversionCurrency) { _conversionCurrency = conversionCurrency; }

int getConversionLag(){return _conversionLag;}
void setConversionLag(int conversionLag){ _conversionLag = conversionLag; }

String getPaymentType(){return _paymentType;}
void setPaymentType(String paymentType){ _paymentType = paymentType;}

Date getPaymentDate(){return _paymentDate;}
void setPaymentDate(Date paymentDate){ _paymentDate = paymentDate; }

String getPayReceive(){return _payReceive;}
void setPayReceive(String payReceive){ _payReceive = payReceive;}

String getCustomerAccount(){return _customerAccount;}
void setCustomerAccount(String customerAccount){ _customerAccount = customerAccount;}

String getFirmAccount(){return _firmAccount;}
void setFirmAccount(String firmAccount){ _firmAccount = firmAccount;}

int getPayRef(){return _payRef;}
void setPayRef(int payRef) { _payRef = payRef;}

String getThirdPartyType(){return _thirdPartyType;}
void setThirdPartyType(String thirdPartyType){ _thirdPartyType = thirdPartyType;}

String getThirdPartyName(){return _thirdPartyName;}
void setThirdPartyName(String thirdPartyName){ _thirdPartyName = thirdPartyName;}

String getComment(){return _comment;}
void setComment(String comment){ _comment = comment;}


protected:

double 				_amount;
String				_comment;
const Currency * 	_conversionCurrency;
String 				_conversionIndex ;
int 				_conversionLag;
const Currency * 	_currency;
String				_customerAccount;
String				_firmAccount;
Date 				_paymentDate;
String 				_payReceive;
int					_payRef;
String 				_paymentType;
String 				_thirdPartyType;
String				_thirdPartyName;
};
      
}

#endif // ADDITIONALPAYMENTS_H

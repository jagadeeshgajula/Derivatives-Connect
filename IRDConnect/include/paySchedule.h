#ifndef PAYSCHEDULE_H
#define PAYSCHEDULE_H
#include<iostream>
#include<string>
#include "irdString.h"
#include "date.h"

using namespace std;
using namespace IRDConnect;


namespace IRDConnect {

class PaySchedule
{

public:

PaySchedule();
virtual ~PaySchedule();

PaySchedule(
Date 		couponStartDate,
double 		amount,
double 		convertedAmount,
Date 		couponEndDate,
Date 		paymentDate,
double 		periodRate,
double		notional)

{
_couponStartDate 	=	couponStartDate;
_amount				=	amount;
_convertedAmount	=	convertedAmount;
_couponEndDate 		=	couponEndDate;
_paymentDate 		=	paymentDate;
_periodRate 		= 	periodRate;
_notional			=	notional;
}

Date getCouponStartDate() const {return _couponStartDate;}
void setCouponStartDate(Date couponStartDate){ _couponStartDate = couponStartDate;}

Date getCouponEndDate() { return  _couponEndDate;}
void setCouponEndDate(Date couponEndDate) { _couponEndDate = couponEndDate; }

Date getPaymentDate(){return _paymentDate;}
void setPaymentDate(Date paymentDate){ _paymentDate = paymentDate; }

double getAmount(){return _amount;}
void setAmount(float amount){ _amount = amount;}

double getPeriodRate(){return _periodRate;}
void setPeriodRate(double periodRate){ _periodRate = periodRate;}

double getNotional(){return _notional;}
void setNotional(double notional){ _notional = notional;}

double getConvertedAmount(){return _convertedAmount;}
void setConvertedAmount(float convertedAmount){ _convertedAmount = convertedAmount;}


protected:

double 		_amount;
double 		_convertedAmount;
Date 		_couponStartDate;
Date 		_couponEndDate;
Date 		_paymentDate;
double 		_periodRate;
double		_notional;
};

class PrincipalSchedule
{

public:

PrincipalSchedule();
virtual ~PrincipalSchedule();

PrincipalSchedule(
Date 		paymentDate,
double 		principalAmt
)
{
_paymentDate 		=	paymentDate;
_principalAmt		=	principalAmt; // principal payments if any
}

Date getPaymentDate(){return _paymentDate;}
void setPaymentDate(Date paymentDate){ _paymentDate = paymentDate; }

double getPrincipalAmt(){return _principalAmt;}
void setPrincipalAmt(float principalAmt){ _principalAmt = principalAmt;}

protected:

Date 		_paymentDate;
double 		_principalAmt;

};

}

#endif  // PAYSCHEDULE_H

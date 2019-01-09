#ifndef CompSchedule_H
#define CompSchedule_H
#include<iostream>
#include<string>
#include "irdString.h"
#include "date.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class CompSchedule
{

public:

CompSchedule();
virtual ~CompSchedule();

CompSchedule(
double 		accrualInterest,
double 		convertedAmount,
Date 		compEndDate,
Date 		compStartDate,
double 		notional,
double 		accrualRate)
{
_accrualInterest 	=	accrualInterest;
_convertedAmount	=	convertedAmount;
_compStartDate 		=	compStartDate;
_compEndDate 		=	compEndDate;
_notional			=	notional; // amortized notional to be stored here
_accrualRate 		= 	accrualRate;
}

Date getCompStartDate(){return _compStartDate;}
void setCompStartDate(Date compStartDate){ _compStartDate = compStartDate;}

Date getCompEndDate() { return  _compEndDate;}
void setCompEndDate(Date compEndDate) { _compEndDate = compEndDate; }

double getAccrualInterest(){return _accrualInterest;}
void setAccrualInterest(double accrualInterest){ _accrualInterest = accrualInterest;}

double getAccrualRate(){return _accrualRate;}
void setAccrualRate(double accrualRate){ _accrualRate = accrualRate;}

double getNotional(){return _notional;}
void setNotional(float notional){ _notional = notional;}

double getConvertedAmount(){return _convertedAmount;}
void setConvertedAmount(float convertedAmount){ _convertedAmount = convertedAmount;}

protected:

double 		_accrualInterest;
double 		_convertedAmount;
Date 		_compStartDate;
Date 		_compEndDate;
double 		_notional;
double 		_accrualRate;
};


}

#endif  // CompSchedule_H

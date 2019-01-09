#ifndef RESETSCHEDULE_H
#define RESETSCHEDULE_H
#include<iostream>
#include<string>
#include "irdString.h"
#include "date.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class ResetSchedule
{
      
public:

ResetSchedule();

virtual ~ResetSchedule();

ResetSchedule(
		Date  	quoteDate,
		double 	rate,
		String 	rateIndexType,
		String 	rateSettingType,
		Date 	resetStartDate,
		Date 	resetEndDate
);

Date getResetStartDate(){return _resetStartDate;}
void setResetStartDate(Date resetStartDate){ _resetStartDate = resetStartDate;}

Date getResetEndDate(){return _resetEndDate;}
void setResetEndDate(Date resetEndDate){ _resetEndDate = resetEndDate;}

Date getQuoteDate(){return _quoteDate;}
void setQuoteDate(Date quoteDate){_quoteDate = quoteDate;}

double getRate(){return _rate;}
void setRate (double rate ){ _rate = rate ;}

String getRateSettingType(){return _rateSettingType;}
void setRateSettingType(String rateSettingType){ _rateSettingType = rateSettingType;}

String getRateIndexType(){return _rateIndexType;}
void setRateIndexType(String rateIndexType){ _rateIndexType = rateIndexType;}

protected:
Date 		_quoteDate;
double 		_rate;
String 		_rateIndexType;
String 		_rateSettingType;
Date 		_resetStartDate;
Date 		_resetEndDate;
};


}

#endif // RESETSCHEDULE_H


#ifndef REVALRATES_H
#define REVALRATES_H
#include<iostream>
#include<string>
#include "irdString.h"
#include "date.h"


using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class RevalRates
{

public:

RevalRates(){;};

RevalRates(
		String 	checkerId,
		Date 	checkerTimestamp,
		Date 	currentDate,
		String 	makerId,
		Date 	makerTimestamp,
		Date 	quoteDate,
		String 	quoteId,
		String 	quoteType,
		double 	rate,
		String 	ratesetMode,
		double 	tolerance
);

~RevalRates();






String getcheckerId(){return _checkerId;}
void setCheckerId(String checkerId){ _checkerId = checkerId; }

Date getCheckerTimestamp(){return _checkerTimestamp;}
void setCheckerTimestamp(Date checkerTimestamp){ _checkerTimestamp	= checkerTimestamp;}

Date getCurrentDate(){return _currentDate;}
void setCurrentDate(Date currentDate){ _currentDate = currentDate;}


String MakerId(){return _makerId;}
void setMakerId (String makerId ){ _makerId	= makerId ;}

Date getMakerTimestamp() {return _makerTimestamp;}
void setMakerTimestamp(Date makerTimestamp) { _makerTimestamp = makerTimestamp; }

Date getQuoteDate(){return _quoteDate;}
void setQuoteDate(Date quoteDate){ _quoteDate = quoteDate; }

String getQuoteId() {return _quoteId;}
void setQuoteId(String quoteId) { _quoteId = quoteId; }

String getQuoteType(){return _quoteType;}
void setQuoteType(String quoteType){ _quoteType = quoteType;}

double getRate(){return _rate;}
void setRate(double rate){ _rate = rate;}

String getRatesetMode(){return _ratesetMode;}
void setRatesetMode (String ratesetMode ){ _ratesetMode	= ratesetMode ;}

double getTolerance(){return _tolerance;}
void setTolerance (double tolerance ){ _tolerance = tolerance ;}

private:

String 		_checkerId;
Date 		_checkerTimestamp;
Date 		_currentDate;
String 		_makerId;
Date 		_makerTimestamp;
Date 		_quoteDate;
String 		_quoteId;
String 		_quoteType;
double 		_rate;
String 		_ratesetMode;
double 		_tolerance;
};

}

#endif // end of REVALRATES_H
  


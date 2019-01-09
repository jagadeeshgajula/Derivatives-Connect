#ifndef FIXINGRATES_H
#define FIXINGRATES_H
#include<iostream>
#include<string>
#include "irdString.h"
#include "date.h"
#include "period.h"
#include "busDayConv.h"
#include <set>
#include <list>


using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class FixingRates;


static std::list < FixingRates > _fixingRatesList;


class FixingRates
{

public:

FixingRates(){;};

FixingRates(
		Date 	currentDate,
		String 	lastModifiedBy,
		String 	lastVerifiedBy,
		Date 	modifiedTimestamp,
		Date 	quoteDate,
		String 	quoteId,
		String 	quoteType,
		double 	rate,
		String 	ratesetMode,
		Date	verifiedTimestamp
);

~FixingRates();

void static init();
String getQuoteId() {return _quoteId;}     
void setQuoteId(String quoteId) { _quoteId =	quoteId; }

Date getQuoteDate(){return _quoteDate;}
void setQuoteDate(Date quoteDate){ _quoteDate = quoteDate; }

String getQuoteType(){return _quoteType;}
void setQuoteType(String quoteType){ _quoteType = quoteType;}

double getRate(){return _rate;}
void setRate(double rate)  { _rate = rate;}

String getLastModifiedBy(){return _lastModifiedBy;}
void setLastModifiedBy (String lastModifiedBy ){ _lastModifiedBy	=	lastModifiedBy ;}

Date getModifiedTimestamp() {return _modifiedTimestamp;}
void setModifiedTimestamp(Date modifiedTimestamp) { _modifiedTimestamp	 =	modifiedTimestamp; }

String getLastVerifiedBy(){return _lastVerifiedBy;}
void setLastVerifiedBy(String lastVerifiedBy){ _lastVerifiedBy = lastVerifiedBy; }

Date getVerifiedTimestamp(){return _verifiedTimestamp;}
void setVerifiedTimestamp(Date verifiedTimestamp){ _verifiedTimestamp	= verifiedTimestamp;}

Date getCurrentDate(){return _currentDate;}
void setCurrentDate (Date currentDate ){ _currentDate	=	currentDate ;}

String getRatesetMode(){return _ratesetMode;}
void setRatesetMode (String ratesetMode ){ _ratesetMode = ratesetMode ;}


static std::list < FixingRates > & getFixingRatesList() { return _fixingRatesList ; }


static String getFixingQuote( String index,  Period stubTenor );

static double getFixingRate(Date quoteDate, String quoteId);
static double getFixingRate(Date quoteDate, Date resetStartDate, String quoteId);
static double getFixingRate( Date quoteDate, String stubAIndex, String stubBIndex,
		Date couponStartDate, Date couponEndDate, const BusDayConv * busDay );

private:

Date 	_currentDate;
String 	_lastModifiedBy;
String 	_lastVerifiedBy;
Date	_modifiedTimestamp;
Date 	_quoteDate;
String 	_quoteId;
String	_quoteType;
double 	_rate;
String	_ratesetMode;
Date 	_verifiedTimestamp;




};
  
}

#endif // end of FIXINGRATES_H



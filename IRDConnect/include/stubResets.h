#ifndef STUBRESETS_H
#define STUBRESETS_H
#include<iostream>
#include<string>
#include "irdString.h"
#include "date.h"


using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class  StubResets
{

public:

StubResets(){;};

StubResets (
Date 		quoteDate,
Date 		startDate,
String 		stubMarketIndex,
double 		stubRate,
String 		stubRateType,
Period 		stubTenor,
String 		stubType
);

~StubResets();

Date getQuoteDate(){return _quoteDate;}
void setQuoteDate (Date quoteDate) { _quoteDate = quoteDate;}

Date getStartDate(){return _startDate;}
void setStartDate (Date startDate){ _startDate = startDate;}

String getStubMarketIndex(){return _stubMarketIndex;}
void setStubMarketIndex(String stubMarketIndex){ _stubMarketIndex = stubMarketIndex; }

double getStubRate(){return _stubRate;}
void setStubRate( double stubRate){ _stubRate = stubRate; }

String getStubRateType(){return _stubRateType;}
void setStubRateType( String stubRateType){ _stubRateType = stubRateType; }

String getStubType(){return _stubType;}
void setStubType( String stubType){ _stubType = stubType; }

Period getStubTenor(){return _stubTenor;}
void setStubTenor( Period stubTenor){ _stubTenor = stubTenor; }

void setManualStub(bool manual) { _manualStub = manual; }

bool isManualStub() {
	if ( _manualStub)
		return true;
	else
		return false;
}
protected:

Date 		_quoteDate;
Date 		_startDate;
String 		_stubMarketIndex;
double 		_stubRate;
String 		_stubRateType;
String 		_stubType; // front stub A/B or back Stub A/B
Period		_stubTenor;
bool		_manualStub;

};

}

#endif // STUBRESETS_H end

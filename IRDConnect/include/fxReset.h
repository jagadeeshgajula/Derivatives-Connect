#ifndef FXRESETS_H
#define FXRESETS_H
#include<iostream>
#include<string>
#include "irdString.h"
#include "frequency.h"
#include <set>

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


using namespace std;

class FXReset
{

public:

FXReset();
           
FXReset(
std::set < std::string >  		fxQuoteCalendars,
String 		fXResetType, // manual or auto
int 		fxResetLegNo,
String 		fxMarketIndex, // fx reset index for fx rates published LIBOR
double		initialFXRate,
Frequency	fxResetFreq, // not going to use now, as we match to reset dates and don't generate fx schedule.
int			fxResetQuoteLag // for calculating quote date for fx rate
);

std::set < std::string >  getFXQuoteCalendars(){return _fxQuoteCalendars;}
void setFXQuoteCalendars(std::set < std::string >  fxQuoteCalendars){ _fxQuoteCalendars = fxQuoteCalendars;}

String getFXResetType(){return _fXResetType;}
void setFXResetType(String fXResetType){ _fXResetType = fXResetType;}

int getFXResetLegNo(){return _fxResetLegNo;}
void setFXResetLegNo (int fxResetLegNo){ _fxResetLegNo = fxResetLegNo ;}

String getFXMarketIndex(){return _fxMarketIndex;}
void setFXMarketIndex(String fxMarketIndex){ _fxMarketIndex = fxMarketIndex; }

double getInitialFXRate(){return _initialFXRate;}
void setInitialFXRate (double initialFXRate){ _initialFXRate = initialFXRate ;}

Frequency getFXResetFreq(){return _fxResetFreq;}
void setFXResetFreq (Frequency fxResetFreq){ _fxResetFreq = fxResetFreq ;}

int getFXResetQuoteLag(){return _fxResetQuoteLag;}
void setFXResetQuoteLag (int fxResetQuoteLag){ _fxResetQuoteLag = fxResetQuoteLag ;}

virtual ~FXReset();

private:
         
std::set < std::string >  		_fxQuoteCalendars;
String 		_fXResetType;
int 		_fxResetLegNo;
String 		_fxMarketIndex;
double 		_initialFXRate;
Frequency	_fxResetFreq;
int			_fxResetQuoteLag;

};

}


#endif // FXRESETS_H

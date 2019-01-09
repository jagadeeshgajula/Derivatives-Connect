#ifndef SWAPLEG_H
#define SWAPLEG_H

#include<iostream>
#include <fstream>
#include<string>
#include "irdString.h"
#include "date.h"
#include <stdlib.h>
#include <list>
#include "paySchedule.h"
#include "resetSchedule.h"
#include "amortSchedule.h"
#include "marchingConv.h"
#include "busDayConv.h"
#include "currency.h"
#include "frequency.h"
#include "dayCountConv.h"
#include "rollDayConv.h"
#include "compSchedule.h"
#include <boost/shared_ptr.hpp>
#include "stubResets.h"
#include <set>
#include "curve.h"
#include "curveBuilder.h"
#include "curveDef.h"
#include "curveCache.h"
#include "buildCurveFromZcdf.h"
#include "buildCurveFromMarketRates.h"


using namespace std;
using namespace boost;
using namespace IRDConnect;

namespace IRDConnect {

typedef std::list < shared_ptr < PaySchedule > >  PayScheduleList;
typedef std::list < shared_ptr < PrincipalSchedule > >  PrincipalScheduleList;
typedef std::list < shared_ptr < ResetSchedule > > ResetScheduleList;
typedef std::list < shared_ptr < CompSchedule  > > CompScheduleList;
typedef std::list < shared_ptr < AmortSchedule > > AmortScheduleList;
typedef std::list < shared_ptr < StubResets > > StubResetsList;

static String _PAY = "LONG";
static String _RECV = "SHORT";
static String _FIXLEG = "FIXED";
static String _FLTLEG = "FLOAT";

class SwapLeg
{
public:

SwapLeg();

virtual ~SwapLeg();

SwapLeg(
const BusDayConv * 			accrualBusDay,
std::set < std::string > 	accrualCalendars,
Frequency 					accrualFreq,
const DateMarcher * 		accrualMarching,
int 						accrualRollDay,
DayOfWeek 					accrualRollWeek,
int 						amortRollDay,
DayOfWeek 					amortRollWeek,
double 						amortAmount,
const BusDayConv * 			amortBusDay,
std::set < std::string > 	amortCalendars,
Date 						amortEndDate,
Frequency 					amortFreq,
const DateMarcher * 		amortMarching,
Date 						amortStartDate,
String 						amortType,
String 						averagingMethod,
Date 						backStubDate,
double 						backStubManualRate,
Frequency 					compFreq,
String 						compoundingConv,
const Currency * 			currency,
DayCountConv * 				dayCount,
String 						discountCurve,
Date 						endDate,
String 						endDateRollFlag,
String 						endOfMonthIndicator,
double 						fixedQuote,
Date 						frontStubDate,
double 						frontStubManualRate,
double 						gearFactor,
std::set < std::string > 	initialQuoteCalendars,
Date 						initialQuoteDate,
int 						initialQuoteLag,
int 						legNo,
String 						legType,
String 						marketIndex,
double 						notional,
String 						notionalExchange,
const BusDayConv * 			payBusDay,
std::set < std::string > 	payCalendars,
Frequency 					payFreq,
const DateMarcher * 		payMarching,
String 						paymentConvention,
const Currency * 			paymentConversionCurrency,
String 						paymentConversionIndex,
int 						paymentConversionLag,
int							payLag,
int 						payRollDay,
DayOfWeek 					payRollWeek,
String 						position,
int							precision,
std::set < std::string > 	quoteCalendars,
int 						quoteLag,
int 						rateCutOff,
String 						resetAveraging,
const BusDayConv * 			resetBusDay,
String 						resetConvention,
Frequency 					resetFreq,
const DateMarcher * 		resetMarching,
int 						resetRollDay,
DayOfWeek 					resetRollWeek,
String 						resetType,
int 						scheduleCustomFlag,
double 						spread,
Date 						startDate,
String 						startDateRollFlag
);


const BusDayConv * getAccrualBusDay (){return _accrualBusDay ;}
void setAccrualBusDay (const BusDayConv * accrualBusDay ){ _accrualBusDay = accrualBusDay ;}

std::set < std::string > getAccrualCalendars (){return _accrualCalendars ;}
void setAccrualCalendars (std::set < std::string > accrualCalendars ){ _accrualCalendars = accrualCalendars ;}

Frequency getPayFreq (){return _payFreq ;}
void setPayFreq (Frequency payFreq ){ _payFreq = payFreq ;}

const DateMarcher * getAccrualMarching (){return _accrualMarching ;}
void setAccrualMarching (const DateMarcher * accrualMarching ){ _accrualMarching = accrualMarching ;}

int getAccrualRollDay (){return _accrualRollDay ;}
void setAccrualRollDay (int accrualRollDay ){ _accrualRollDay = accrualRollDay ;}

DayOfWeek getAccrualRollWeek (){return _accrualRollWeek ;}
void setAccrualRollWeek (DayOfWeek accrualRollWeek ){ _accrualRollWeek = accrualRollWeek ;}

int getResetRollDay (){return _resetRollDay ;}
void setResetRollDay (int resetRollDay ){ _resetRollDay = resetRollDay ;}

DayOfWeek getResetRollWeek (){return _resetRollWeek ;}
void setResetRollWeek (DayOfWeek resetRollWeek ){ _resetRollWeek = resetRollWeek ;}


double getAmortAmount (){return _amortAmount ;}
void setAmortAmount (double amortAmount ){ _amortAmount = amortAmount ;}


const BusDayConv * getAmortBusDay (){return _amortBusDay ;}
void setAmortBusDay(const BusDayConv * amortBusDay ){ _amortBusDay = amortBusDay ;}

const BusDayConv * getResetBusDay (){return _resetBusDay ;}
void setResetBusDay(const BusDayConv * resetBusDay ){ _resetBusDay = resetBusDay ;}

std::set < std::string > getAmortCalendars (){return _amortCalendars ;}
void setAmortCalendars ( std::set < std::string > amortCalendars ){ _amortCalendars = amortCalendars ;}

Date getAmortEndDate (){return _amortEndDate ;}
void setAmortEndDate (Date amortEndDate ){ _amortEndDate = amortEndDate ;}

Frequency getAmortFreq (){return _amortFreq ;}
void setAmortFreq (Frequency amortFreq ){ _amortFreq = amortFreq ;}

const DateMarcher * getAmortMarching (){return _amortMarching ;}
void setAmortMarching (const DateMarcher * amortMarching ){ _amortMarching = amortMarching ;}

const DateMarcher * getResetMarching (){return _resetMarching ;}
void setResetMarching (const DateMarcher * resetMarching ){ _resetMarching = resetMarching ;}

int getAmortRollDay (){return _amortRollDay ;}
void setAmortRollDay (int amortRollDay ){ _amortRollDay = amortRollDay ;}

DayOfWeek getAmortRollWeek (){return _amortRollWeek ;}
void setAmortRollWeek (DayOfWeek amortRollWeek ){ _amortRollWeek = amortRollWeek ;}

Date getAmortStartDate (){return _amortStartDate ;}
void setAmortStartDate (Date amortStartDate ){ _amortStartDate = amortStartDate; }


String getAmortType (){return _amortType ;}
void setAmortType (String amortType ){ _amortType = amortType ;}

String getAveragingMethod (){return _averagingMethod;}
void setAveragingMethod (String averagingMethod ){ _averagingMethod = averagingMethod ;}


Date getBackStubDate (){return _backStubDate;}
void setBackStubDate (Date backStubDate ){ _backStubDate = backStubDate ;}


double getBackStubManualRate (){return _backStubManualRate;}
void setBackStubManualRate (double backStubManualRate ){ _backStubManualRate = backStubManualRate ;}

Frequency getCompFreq (){return _compFreq ;}
void setCompFreq (Frequency compFreq ){ _compFreq = compFreq ;}


String getCompoundingConv (){return _compoundingConv ;}
void setCompoundingConv (String compoundingConv ){ _compoundingConv = compoundingConv ;}

const Currency * getCurrency(){return _currency;}
void setCurrency(const Currency * currency){ _currency = currency;}

DayCountConv * getDayCount (){return _dayCount ;}
void setDayCount (DayCountConv * dayCount ){ _dayCount = dayCount ;}

String getDiscountCurve (){return _discountCurve;}
void setDiscountCurve (String discountCurve ){ _discountCurve = discountCurve ;}


Date getEndDate(){return _endDate;}
void setEndDate(Date endDate){ _endDate = endDate;}

String getEndDateRollFlag (){return _endDateRollFlag;}
void setEndDateRollFlag (String endDateRollFlag){ _endDateRollFlag = endDateRollFlag ;}

String getEndOfMonthIndicator(){return _endOfMonthIndicator;}
void setEndOfMonthIndicator (String endOfMonthIndicator ){ _endOfMonthIndicator = endOfMonthIndicator ;}

double getFixedQuote (){return _fixedQuote;}
void setFixedQuote (double fixedQuote ){ _fixedQuote = fixedQuote ;}

Date getFrontStubDate (){return _frontStubDate;}
void setFrontStubDate (Date frontStubDate ){ _frontStubDate = frontStubDate ;}

String getLegType() {return _legType;}
void setLegType(String legType) { _legType = legType; }

bool isFloatLeg() { return ( _legType == "FLOAT"); }
bool isFixedLeg() { return ( _legType == "FIXED"); }

bool isPayLeg() { return ( _position == _PAY); }
bool isReceiveLeg() { return ( _legType == _RECV); }

String getPosition(){return _position;}
void setPosition(String position){ _position = position; }

int getPrecision(){return _precision;}
void setPrecision(int precision){ _precision = precision; }

double getNotional(){return _notional;}
void setNotional(double notional){ _notional = notional;}

Date getStartDate(){return _startDate;}
void setStartDate (Date startDate ){ _startDate = startDate ;}

Date getInitialQuoteDate(){return _initialQuoteDate;}
void setInitialQuoteDate(Date initialQuoteDate){ _initialQuoteDate = initialQuoteDate;}

Frequency getAccrualFreq(){ return  _accrualFreq;}
void setAccrualFreq(Frequency accrualFreq){ _accrualFreq = accrualFreq;}

const BusDayConv * getPayBusDay (){return _payBusDay ;}
void setPayBusDay (const BusDayConv * payBusDay ){ _payBusDay = payBusDay ;}

DayOfWeek getPayRollWeek (){return _payRollWeek ;}
void setPayRollWeek (DayOfWeek payRollWeek ){ _payRollWeek = payRollWeek ;}

int getPayLag (){return _payLag ;}
void setPayLag (int payLag ){ _payLag = payLag ;}

int getPayRollDay (){return _payRollDay ;}
void setPayRollDay (int payRollDay ){ _payRollDay = payRollDay ;}

const DateMarcher * getPayMarching (){return _payMarching ;}
void setPayMarching(const DateMarcher * payMarching ){ _payMarching = payMarching ;}

std::set < std::string > getPayCalendars (){return _payCalendars ;}
void setPayCalendars ( std::set < std::string > payCalendars ){ _payCalendars = payCalendars ;}

std::set < std::string > getQuoteCalendars (){return _quoteCalendars ;}
void setQuoteCalendars ( std::set < std::string > quoteCalendars){ _quoteCalendars = quoteCalendars ;}

int getQuoteLag (){return _quoteLag;}
void setQuoteLag (int quoteLag ){ _quoteLag = quoteLag ;}

Frequency getResetFreq (){return _resetFreq;}
void setResetFreq (Frequency resetFreq ){ _resetFreq = resetFreq ;}

String getNotionalExchange (){return _notionalExchange;}
void setNotionalExchange (String notionalExchange ){ _notionalExchange = notionalExchange ;}

String getMarketIndex (){return _marketIndex;}
void setMarketIndex (String marketIndex ){ _marketIndex = marketIndex ;}

String getPaymentConvention (){return _paymentConvention;}
void setPaymentConvention (String paymentConvention ){ _paymentConvention= paymentConvention ;}

String getResetAveraging(){return _resetAveraging;}
void setResetAveraging (String resetAveraging ){ _resetAveraging = resetAveraging ;}

String getResetConvention(){return _resetConvention;}
void setResetConvention (String resetConvention ){ _resetConvention = resetConvention ;}

double getFrontStubManualRate (){return _frontStubManualRate;}
void setFrontStubManualRate (double frontStubManualRate ){ _frontStubManualRate = frontStubManualRate ;}

const Currency * getPaymentConversionCurrency (){return _paymentConversionCurrency;}
void setPaymentConversionCurrency(const Currency * paymentConversionCurrency ){ _paymentConversionCurrency = paymentConversionCurrency ;}

String getPaymentConversionIndex (){return _paymentConversionIndex;}
void setPaymentConversionIndex (String paymentConversionIndex ){ _paymentConversionIndex = paymentConversionIndex ;}

int getPaymentConversionLag (){return _paymentConversionLag;}
void setPaymentConversionLag (int paymentConversionLag ){ _paymentConversionLag = paymentConversionLag ;}

int getRateCutOff (){return _rateCutOff;}
void setRateCutOff (int rateCutOff ){ _rateCutOff = rateCutOff ;}

String getResetType (){return _resetType;}
void setResetType (String resetType ){ _resetType = resetType ;}

int getScheduleCustomFlag (){return _scheduleCustomFlag;}
void setScheduleCustomFlag (int scheduleCustomFlag ){ _scheduleCustomFlag = scheduleCustomFlag ;}

double getSpread ()
{
	if ( isFloatLeg() )
		return _spread;
	else
		return 0.0;
}
void setSpread (double spread ){ _spread = spread ;}

double getGearFactor (){return _gearFactor;}
void setGearFactor (double gearFactor ){ _gearFactor = gearFactor ;}

String getStartDateRollFlag (){return _startDateRollFlag;}
void setStartDateRollFlag (String startDateRollFlag){ _startDateRollFlag = startDateRollFlag ;}
 
int getLegNo (){return _legNo;}
void setLegNo (int legNo){ _legNo = legNo ;}

std::set < std::string > getInitialQuoteCalendars (){return _initialQuoteCalendars;}
void setInitialQuoteCalendars (std::set < std::string > initialQuoteCalendars){_initialQuoteCalendars = initialQuoteCalendars;}

int getInitialQuoteLag () {return _initialQuoteLag;}
void setInitialQuoteLag (int initialQuoteLag){_initialQuoteLag = initialQuoteLag;}

bool genPaySchedule();  // forcifully generate the schedule
PayScheduleList   & displayPaySchedule() {return _payScheduleList;}; // only get schedule that is already egenrated

bool genPrincipalSchedule();  // forcifully generate the schedule
PrincipalScheduleList   & displayPrincipalSchedule() {return _principalScheduleList;}; // only get schedule that is already egenrated

bool  genResetSchedule();
ResetScheduleList & displayResetSchedule() { return _resetScheduleList;};

bool  genCompSchedule();  // forcifully generate the schedule
CompScheduleList & displayCompSchedule() {return _compScheduleList;}; // only get comp schedule that is already egenrated

bool  genAmortSchedule();
AmortScheduleList & displayAmortSchedule() { return _amortScheduleList; }

double getPeriodRate( double rate);

StubResetsList & getStubResetsList() { return _stubResetsList; };
bool genStubResets();

bool isPSGenerated() { return _isPSGenerated; }
void setIsPSGenerated( bool isPSGenerated ) { _isPSGenerated = isPSGenerated; }

bool isRSGenerated() { return _isRSGenerated; }
void setIsRSGenerated( bool isRSGenerated ) { _isRSGenerated = isRSGenerated; }

bool isFXReset() { return _isFXReset; };
void setFXResetFlag(bool isFXReset ) { _isFXReset = isFXReset; };

bool isCustomized() { return _isCustomized; }
void setIsCustomized(bool isCustomized) { _isCustomized = isCustomized; }



bool generateStubs();
bool genLegCashFlows();
double calculatePV(std::string bumpTenor = "" , double bumpSize = 0.0);
double calculateDV01(std::string bumpTenor = "ALL" , double bumpSizeUp = 0.00005, double bumpSizeDown = 0.00005 ); // 0.5 bp up and 0.5bp down
double calculateTheta(double bumpSize = 1.0); // by default T+1

std::string scheduleSerialize();
//std::string PaySerialize();
//std::string CompSerialize();
//std::string AmortSerialize();
//std::string ResetSerialize();

//std::string SchSerialize();
protected:

const BusDayConv * 			_accrualBusDay;
std::set < std::string > 	_accrualCalendars;
Frequency 					_accrualFreq;
const DateMarcher * 		_accrualMarching;
int 						_accrualRollDay;
DayOfWeek 					_accrualRollWeek;
int 						_amortRollDay;
DayOfWeek 					_amortRollWeek;
double 						_amortAmount;
const BusDayConv * 			_amortBusDay;
std::set < std::string > 	_amortCalendars;
Date 						_amortEndDate;
Frequency 					_amortFreq;
const DateMarcher * 		_amortMarching;
Date 						_amortStartDate;
String 						_amortType;
String 						_averagingMethod;
Date 						_backStubDate;
double 						_backStubManualRate;
Frequency 					_compFreq;
String 						_compoundingConv;
const Currency * 			_currency;
DayCountConv * 				_dayCount;
String 						_discountCurve;
Date 						_endDate;
String 						_endDateRollFlag;
String 						_endOfMonthIndicator;
double 						_fixedQuote;
Date 						_frontStubDate;
double 						_frontStubManualRate;
double 						_gearFactor;
std::set < std::string > 	_initialQuoteCalendars;
Date 						_initialQuoteDate;
int 						_initialQuoteLag;
int 						_legNo;
String 						_legType;
String 						_marketIndex;
double 						_notional;
String 						_notionalExchange;
const BusDayConv * 			_payBusDay;
std::set < std::string > 	_payCalendars;
Frequency 					_payFreq;
const DateMarcher * 		_payMarching;
String 						_paymentConvention;
const Currency * 			_paymentConversionCurrency;
String 						_paymentConversionIndex;
int 						_paymentConversionLag;
int							_payLag;
int 						_payRollDay;
DayOfWeek 					_payRollWeek;
String 						_position;
int							_precision;
std::set < std::string > 	_quoteCalendars;
int 						_quoteLag;
int 						_rateCutOff;
String 						_resetAveraging; // weighted or unweighted
const BusDayConv * 			_resetBusDay;
String 						_resetConvention; // in advance or inarriars
Frequency 					_resetFreq;
const DateMarcher * 		_resetMarching;
int 						_resetRollDay;
DayOfWeek 					_resetRollWeek;
String 						_resetType;
int 						_scheduleCustomFlag;
double 						_spread;
Date 						_startDate;
String 						_startDateRollFlag;
bool 						_isPSGenerated;
bool 						_isRSGenerated;
bool						_isFXReset;
bool						_isCustomized;

StubResets * 				_stubResets;

PayScheduleList  			_payScheduleList;
PrincipalScheduleList  		_principalScheduleList;
CompScheduleList  			_compScheduleList;
ResetScheduleList 			_resetScheduleList;
AmortScheduleList 			_amortScheduleList;
StubResetsList 				_stubResetsList;
};

}

#endif //SWAPLEG_H

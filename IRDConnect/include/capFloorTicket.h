/*
 * capfloorTicket.h
 *
 *  Created on: 26-Sep-2010
 *      Author: vishist
 */

#ifndef CAPFLOORTICKET_H_
#define CAPFLOORTICKET_H_

#include <iostream>
#include "irdString.h"
#include "tradeTicket.h"
#include "date.h"
#include "busDayConv.h"
#include "dayCountConv.h"
#include <list>
#include "currency.h"
#include "marchingConv.h"
#include "rollDayConv.h"
#include "frequency.h"
#include <boost/shared_ptr.hpp>
#include "stubResets.h"
#include <set>
#include "paySchedule.h"
#include "resetSchedule.h"
#include "amortSchedule.h"



using namespace std;
using namespace boost;
using namespace IRDConnect;


namespace IRDConnect {

typedef std::list < shared_ptr < PaySchedule > >  PayScheduleList;
typedef std::list < shared_ptr < ResetSchedule > > ResetScheduleList;
typedef std::list < shared_ptr < AmortSchedule > > AmortScheduleList;
typedef std::list < shared_ptr < StubResets > > StubResetsList;


class CapFloorTicket; // forward declare

typedef std::list <CapFloorTicket *> CapFloorTicketList;


class CapFloorTicket : public TradeTicket
{

public:

CapFloorTicket(){;};

CapFloorTicket(
String  	alternateRef,
String  	bookingType,
String  	customerAccount,
Date  		earlyTermDate,
String  	earlyTermReason,
String  	externalSystem,
String  	externalRef,
String  	firmAccount,
String  	flowStatus,
String  	lastModifiedBy,
String  	lastVerifiedBy,
String  	legalEntity,
String  	location,
String  	matchingStatus,
Date  		terminationDate,
String  	modifiedTimeStamp,
String  	operationsRef,
String  	originalTradeRef,
String  	productType,
String  	salesPerson,
Date  		effectiveDate,
String		subType,
Date  		tradeDate,
String  	trader,
String  	tradeRef,
String  	tradeRemarks,
String  	tradeStatus,
String  	tradeType,
double  	tradeVersion,
String  	verifiedTimeStamp,
String  	washAccount,
// cap/floor related fields
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
Date 						backStubDate,
double 						backStubManualRate,
String 						buyFlag,
String						capFloorType,
const Currency *  			currency,
DayCountConv * 	 			dayCount,
String 						discountCurve,
Date 						endDate,
String 						endDateRollFlag,
Date 						frontStubDate,
double 						frontStubManualRate,
double 						gearFactor,
std::set < std::string > 	initialQuoteCalendars,
Date 						initialQuoteDate,
int 						initialQuoteLag,
int 						legNo,
String 						marketIndex,
double 						notional,
const BusDayConv * 			payBusDay,
std::set < std::string >	payCalendars,
Frequency 					payFreq,
const DateMarcher * 		payMarching,
String 						paymentConvention,
const Currency * 	 		paymentConversionCurrency,
String 						paymentConversionIndex,
int 						paymentConversionLag,
int							payLag,
int 						payRollDay,
DayOfWeek 					payRollWeek,
String						pricingMethod, // closed Form, Tree, Mc 3000:10000:40000 etc
std::set < std::string >	quoteCalendars,
int 						quoteLag,
String						resetAveraging,
String 						resetConvention,
Frequency 					resetFreq,
String 						resetType,
int 						scheduleCustomFlag,
double 						spread,
Date 						capStartDate,
String 						startDateRollFlag,
double 						strike,
String						cfSubType,
String						volId );

~CapFloorTicket();


double getAmortAmount (){return _amortAmount ;}
void setAmortAmount (double amortAmount ){ _amortAmount = amortAmount ;}

const BusDayConv * getAmortBusDay (){return _amortBusDay ;}
void setAmortBusDay(const BusDayConv * amortBusDay ){ _amortBusDay = amortBusDay ;}

std::set < std::string > getAmortCalendars (){return _amortCalendars ;}
void setAmortCalendars ( std::set < std::string > amortCalendars ){ _amortCalendars = amortCalendars ;}

Date getAmortEndDate (){return _amortEndDate ;}
void setAmortEndDate (Date amortEndDate ){ _amortEndDate = amortEndDate ;}

Frequency getAmortFreq (){return _amortFreq ;}
void setAmortFreq (Frequency amortFreq ){ _amortFreq = amortFreq ;}

const DateMarcher * getAmortMarching (){return _amortMarching ;}
void setAmortMarching (const DateMarcher * amortMarching ){ _amortMarching = amortMarching ;}

int getAmortRollDay (){return _amortRollDay ;}
void setAmortRollDay (int amortRollDay ){ _amortRollDay = amortRollDay ;}

DayOfWeek getAmortRollWeek (){return _amortRollWeek ;}
void setAmortRollWeek (DayOfWeek amortRollWeek ){ _amortRollWeek = amortRollWeek ;}

Date getAmortStartDate (){return _amortStartDate ;}
void setAmortStartDate (Date amortStartDate ){ _amortStartDate = amortStartDate; }

String getAmortType (){return _amortType ;}
void setAmortType (String amortType ){ _amortType = amortType ;}

Date getBackStubDate (){return _backStubDate;}
void setBackStubDate (Date backStubDate ){ _backStubDate = backStubDate ;}

double getBackStubManualRate (){return _backStubManualRate;}
void setBackStubManualRate (double backStubManualRate ){ _backStubManualRate = backStubManualRate ;}

String getBuyFlag (){return _buyFlag;}
void setBuyFlag (String buyFlag ){ _buyFlag = buyFlag ;}

String getCapFloorType (){return _capFloorType;}
void setCapFloorType(String capFloorType ){ _capFloorType = capFloorType ;}

const Currency * getCurrency() {return _currency ;}
void setCurrency (const Currency * currency ){ _currency = currency ;}

DayCountConv * getDayCount (){return _dayCount ;}
void setDayCount (DayCountConv * dayCount ){ _dayCount = dayCount ;}

String getDiscountCurve (){return _discountCurve;}
void setDiscountCurve (String discountCurve ){ _discountCurve = discountCurve ;}

Date getEndDate(){return _endDate;}
void setEndDate(Date endDate){ _endDate = endDate;}

String getEndDateRollFlag (){return _endDateRollFlag;}
void setEndDateRollFlag (String endDateRollFlag){ _endDateRollFlag = endDateRollFlag ;}

Date getFrontStubDate (){return _frontStubDate;}
void setFrontStubDate (Date frontStubDate ){ _frontStubDate = frontStubDate ;}

double getFrontStubManualRate (){return _frontStubManualRate;}
void setFrontStubManualRate (double frontStubManualRate ){ _frontStubManualRate = frontStubManualRate ;}

double getGearFactor (){return _gearFactor;}
void setGearFactor (double gearFactor ){ _gearFactor = gearFactor ;}

Date getInitialQuoteDate(){return _initialQuoteDate;}
void setInitialQuoteDate(Date initialQuoteDate){ _initialQuoteDate = initialQuoteDate;}

std::set < std::string > getInitialQuoteCalendars (){return _initialQuoteCalendars;}
void setInitialQuoteCalendars (std::set < std::string > initialQuoteCalendars){_initialQuoteCalendars = initialQuoteCalendars;}

int getInitialQuoteLag () {return _initialQuoteLag;}
void setInitialQuoteLag (int initialQuoteLag){_initialQuoteLag = initialQuoteLag;}

int getLegNo (){return _legNo;}
void setLegNo (int legNo){ _legNo = legNo ;}

String getMarketIndex (){return _marketIndex;}
void setMarketIndex (String marketIndex ){ _marketIndex = marketIndex ;}

double getNotional(){return _notional;}
void setNotional(double notional){ _notional = notional;}

const BusDayConv * getPayBusDay (){return _payBusDay ;}
void setPayBusDay (const BusDayConv *  payBusDay ){ _payBusDay = payBusDay ;}

std::set < std::string > getPayCalendars (){return _payCalendars ;}
void setPayCalendars (std::set < std::string > payCalendars ){ _payCalendars = payCalendars ;}

Frequency getPayFreq (){return _payFreq ;}
void setPayFreq (Frequency payFreq ){ _payFreq = payFreq ;}

const DateMarcher * getPayMarching (){return _payMarching ;}
void setPayMarching(const DateMarcher * payMarching ){ _payMarching = payMarching ;}

String getPaymentConvention (){return _paymentConvention;}
void setPaymentConvention (String paymentConvention ){ _paymentConvention = paymentConvention ;}

const Currency * getPaymentConversionCurrency() {return _paymentConversionCurrency;}
void setPaymentConversionCurrency(const Currency *  paymentConversionCurrency ){ _paymentConversionCurrency = paymentConversionCurrency ;}

String getPaymentConversionIndex (){return _paymentConversionIndex;}
void setPaymentConversionIndex(String paymentConversionIndex ){ _paymentConversionIndex =paymentConversionIndex ;}

int getPaymentConversionLag (){return _paymentConversionLag;}
void setPaymentConversionLag (int paymentConversionLag ){ _paymentConversionLag = paymentConversionLag ;}

int getPayLag (){return _payLag ;}
void setPayLag (int payLag ){ _payLag = payLag ;}

int getPayRollDay (){return _payRollDay ;}
void setPayRollDay (int payRollDay ){ _payRollDay = payRollDay ;}


DayOfWeek getPayRollWeek (){return _payRollWeek ;}
void setPayRollWeek (DayOfWeek payRollWeek ){ _payRollWeek = payRollWeek ;}

String getPricingMethod (){return _pricingMethod;}
void setPricingMethod (String pricingMethod ){ _pricingMethod = pricingMethod ;}

std::set < std::string > getQuoteCalendars (){return _quoteCalendars ;}
void setQuoteCalendars (std::set < std::string > quoteCalendars){ _quoteCalendars = quoteCalendars ;}


int getQuoteLag (){return _quoteLag;}
void setQuoteLag (int quoteLag ){ _quoteLag = quoteLag ;}


String getResetConvention(){return _resetConvention;}
void setResetConvention (String resetConvention ){ _resetConvention = resetConvention ;}

String getResetAveraging(){return _resetAveraging;}
void setResetAveraging (String resetAveraging ){ _resetAveraging = resetAveraging ;}

Frequency getResetFreq (){return _resetFreq;}
void setResetFreq (Frequency resetFreq ){ _resetFreq = resetFreq ;}

String getResetType (){return _resetType;}
void setResetType (String resetType ){ _resetType = resetType ;}

int getScheduleCustomFlag (){return _scheduleCustomFlag;}
void setScheduleCustomFlag (int scheduleCustomFlag ){ _scheduleCustomFlag = scheduleCustomFlag ;}

double getSpread (){return _spread;}
void setSpread (double spread ){ _spread = spread ;}


Date getCapStartDate(){return _capStartDate;}
void setCapStartDate (Date capStartDate ){ _capStartDate = capStartDate ;}

String getStartDateRollFlag (){return _startDateRollFlag;}
void setStartDateRollFlag (String startDateRollFlag){ _startDateRollFlag = startDateRollFlag ;}

double getStrike (){return _strike;}
void setStrike (double strike){ _strike = strike ;}

String getCFSubType (){return _cfSubType;}
void setCFSubType (String cfSubType ){ _cfSubType = cfSubType ;}

String getVolId (){return _volId;}
void setVolId (String volId){ _volId = volId ;}

bool genPaySchedule();
bool genResetSchedule();
bool genCashFlows();
bool generateStubs();

PayScheduleList & displayPaySchedule() { return _payScheduleList; };
ResetScheduleList & displayResetSchedule() { return _resetScheduleList; };
AmortScheduleList & displayAmortSchedule() { return _amortScheduleList; };
StubResetsList & getStubResetsList() { return _stubResetsList; };

bool isPSGenerated() { return _isPSGenerated; };
void setIsPSGenerated(bool isPSGenerated) { _isPSGenerated = isPSGenerated; };


bool isRSGenerated() { return _isRSGenerated; };
void setIsRSGenerated(bool isRSGenerated) { _isRSGenerated = isRSGenerated; };


bool isCustomized() { return _isCustomized; };
void setIsCustomized(bool isCustomized) { _isCustomized = isCustomized; };

CapFloorTicketList & getCapFloorTicketList() { return _capFloorTicketList; }

double getPeriodRate(double rate);

bool genAllCashFlows();

double calculatePV(std::string bumpTenor = "" , double bumpSize = 0.0);
double calculateDV01(std::string bumpTenor = "ALL" , double bumpSizeUp = 0.00005, double bumpSizeDown = 0.00005 ); // 0.5 bp up and 0.5bp down
double calculateTheta(double bumpSize = 1.0); // by default T+1

std::string capFloorSerialize();

std::string legSerialize();

protected:

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
Date 						_backStubDate;
double 						_backStubManualRate;
String 						_buyFlag;
String						_capFloorType;
const Currency *			_currency;
DayCountConv *		 		_dayCount;
String 						_discountCurve;
Date 						_endDate;
String 						_endDateRollFlag;
Date 						_frontStubDate;
double 						_frontStubManualRate;
double 						_gearFactor;
std::set < std::string > 	_initialQuoteCalendars;
Date 						_initialQuoteDate;
int 						_initialQuoteLag;
int 						_legNo;
String 						_marketIndex;
double 						_notional;
const BusDayConv * 			_payBusDay;
std::set < std::string >  	_payCalendars;
Frequency 					_payFreq;
const DateMarcher *  		_payMarching;
String 						_paymentConvention; // in adavance or in arriars
const Currency * 			_paymentConversionCurrency;
String 						_paymentConversionIndex;
int 						_paymentConversionLag;
int							_payLag;
int 						_payRollDay;
DayOfWeek					_payRollWeek;
String						_pricingMethod;
std::set < std::string >	_quoteCalendars;
int 						_quoteLag;
String						_resetAveraging;
String 						_resetConvention; // in advance or arriars
Frequency					_resetFreq;
String 						_resetType; // auto or manual
int 						_scheduleCustomFlag;
double 						_spread;
Date 						_capStartDate; // usually equal to startDate on trade ticket
String 						_startDateRollFlag;
double 						_strike;
String						_cfSubType;
String						_volId;
PayScheduleList				_payScheduleList;
ResetScheduleList			_resetScheduleList;
AmortScheduleList			_amortScheduleList;
StubResetsList				_stubResetsList;
CapFloorTicketList			_capFloorTicketList;
bool						_isPSGenerated;
bool						_isRSGenerated;
bool						_isCustomized;
};

}

#endif /* CAPFLOORTICKET_H_ */

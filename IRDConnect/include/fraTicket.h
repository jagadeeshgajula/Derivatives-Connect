/*
 * fraTicket.h
 *
 *  Created on: 26-Sep-2010
 *      Author: vishist
 */

#ifndef FRATICKET_H_
#define FRATICKET_H_
#include <iostream>
#include "irdString.h"
#include "date.h"
#include "busDayConv.h"
#include "dayCountConv.h"
#include "tradeTicket.h"
#include "paySchedule.h"
#include "resetSchedule.h"
#include <set>
#include <list>
#include  <boost/shared_ptr.hpp>


using namespace std;
using namespace boost;
using namespace IRDConnect;

namespace IRDConnect {


class FraTicket; // forward declare

typedef std::list < FraTicket * > FraTicketList;

typedef std::list < shared_ptr < PaySchedule > >  PayScheduleList;
typedef std::list < shared_ptr < ResetSchedule > >  ResetScheduleList;

class FraTicket : public TradeTicket
{
public:

FraTicket();
~FraTicket();

FraTicket (
		String   		alternateRef,
		String  		bookingType,
		String  		customerAccount,
		Date  			earlyTermDate,
		String  		earlyTermReason,
		String  		externalSystem,
		String  		externalRef,
		String  		firmAccount,
		String  		flowStatus,
		String  		lastModifiedBy,
		String  		lastVerifiedBy,
		String  		legalEntity,
		String  		location,
		String  		matchingStatus,
		Date  			terminationDate,
		String  		modifiedTimeStamp,
		String  		operationsRef,
		String  		originalTradeRef,
		String  		productType,
		String  		salesPerson,
		Date  			effectiveDate,
		String  		subType,
		Date  			tradeDate,
		String  		trader,
		String  		tradeRef,
		String  		tradeRemarks,
		String  		tradeStatus,
		String  		tradeType,
		double  		tradeVersion,
		String  		verifiedTimeStamp,
		String  		washAccount, // trade ticket until here
const Currency * 			currency,
String buySell, // BUY or SELL
double 			notional, // fra specific starts here
Date 			settlementDate,
int 			quoteLag,
Date 			quoteDate,
Date            startDate,
Date            maturityDate,
std::set < std::string > 			payCalendars,
const BusDayConv * 	busDayConv,
double 			agreedRate,
String 			resetType,
String			rateType, // add-on , discount or simple
double			manualRate,
String 			marketIndex,
DayCountConv * 	dayCount,
std::set < std::string > 			quoteCalendars,
String 			discountCurve,
String 			paymentConvention,
int				precision,
String 			resetConvention);

const Currency * getCurrency(){return _currency;}
void setCurrency(const Currency * currency){ _currency = currency;}

String getBuySell () {return _buySell;}
void setBuySell(String buySell) { _buySell = buySell;}

double getNotional () {return _notional;}
void setNotional(double notional) {_notional = notional;}

int getPrecision () {return _precision;}
void setPrecision(int precision) {_precision = precision;}

Date getSettlementDate () {return _settlementDate;}
void setSettlementDate(Date settlementDate) { _settlementDate = settlementDate;}

int  getQuoteLag () {return _quoteLag;}
void setQuoteLag(int quoteLag) { _quoteLag = quoteLag;}

Date getQuoteDate () {return _quoteDate;}
void setQuoteDate(Date quoteDate) { _quoteDate = quoteDate;}

Date getStartDate () {return _startDate;}
void setStartDate(Date startDate) {_startDate = startDate;}

Date getMaturityDate () {return _maturityDate;}
void setMaturityDate(Date maturityDate) {_maturityDate = maturityDate;}

std::set < std::string > getPayCalendars () {return _payCalendars;}
void setPayCalendars(std::set < std::string > payCalendars) { _payCalendars = payCalendars;}

const BusDayConv * getBusDayConv () {return _busDayConv;}
void setBusDayConv(const BusDayConv * busDayConv) { _busDayConv = busDayConv;}

double getAgreedRate () {return _agreedRate;}
void setAgreedRate(double agreedRate) { _agreedRate = agreedRate;}

String getResetType () {return _resetType;}
void setResetType(String resetType) { _resetType = resetType;}

String getRateType() {return _rateType;}
void setRateType(String rateType) { _rateType = rateType;}

double getManualRate() { return _manualRate; }
void setManualRate(double manualRate) { _manualRate = manualRate; }

String getMarketIndex () {return _marketIndex;}
void setMarketIndex(String marketIndex) { _marketIndex = marketIndex;}

DayCountConv * getDayCount () {return _dayCount;}
void setDayCount(DayCountConv * dayCount) { _dayCount = dayCount;}

std::set < std::string > getQuoteCalendars () {return _quoteCalendars;}
void setQuoteCalendars(std::set < std::string > quoteCalendars) { _quoteCalendars = quoteCalendars;}

String getDiscountCurve () {return _discountCurve;}
void setDiscountCurve(String discountCurve) { _discountCurve = discountCurve;}

String getPaymentConvention () {return _paymentConvention;}
void setPaymentConvention(String paymentConvention) { _paymentConvention = paymentConvention;}

String getResetConvention () {return _resetConvention;}
void setResetConvention(String resetConvention) { _resetConvention = resetConvention;}


bool genPaySchedule();
PayScheduleList & getPayScheduleList() { return _fraPayScheduleList; };
ResetScheduleList & getResetScheduleList() { return _fraResetScheduleList; };

std::string fraResetScheduleSerialize();

bool genAllCashFlows();

double calculatePV(std::string bumpTenor = "" , double bumpSize = 0.0);
double calculateDV01(std::string bumpTenor = "ALL" , double bumpSizeUp = 0.00005, double bumpSizeDown = 0.00005 ); // 0.5 bp up and 0.5bp down
double calculateTheta(double bumpSize = 1.0); // by default T+1

double getPeriodRate();

std::string fraSerialize();

protected:

const Currency * 			_currency;
String			_buySell;
double 			_notional;
Date  			_settlementDate;
int  			_quoteLag;
Date 			_quoteDate;
Date            _startDate;
Date            _maturityDate;
std::set < std::string > 		_payCalendars;
const BusDayConv  *	_busDayConv;
double  		_agreedRate;
String  		_resetType;
String  		_rateType; // ADD_ON OR DISCOUNT OR SIMPLE
double			_manualRate;
String  		_marketIndex;
DayCountConv  * _dayCount;
std::set < std::string >	_quoteCalendars;
String  		_discountCurve;
String 			_paymentConvention;
int				_precision;
String  		_resetConvention;

PayScheduleList  _fraPayScheduleList;
ResetScheduleList  _fraResetScheduleList;
FraTicketList		_fraTicketList;

};

}

#endif /* FRATICKET_H_ */

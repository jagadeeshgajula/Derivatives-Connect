/*
 * capfloorTicket.cpp
 *
 *  Created on: 26-Sep-2010
 *      Author: vishist
 */

#include <iostream>
#include  "capFloorTicket.h"
#include "calendarUtil.h"
#include "fixingRates.h"
#include <math.h>
#include "util.h"

#include "irdXML.h"

using namespace std;
using namespace IRDConnect;

CapFloorTicket::CapFloorTicket(
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
String		tradeRemarks,
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
String						pricingMethod,
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
String						volId )

{
	_amortRollDay				=	amortRollDay;
	_amortRollWeek				= 	amortRollWeek;
	_amortAmount				= 	amortAmount;
	_amortBusDay 				= 	amortBusDay;
	_amortCalendars 			= 	amortCalendars;
	_amortEndDate 				= 	amortEndDate;
	_amortFreq					= 	amortFreq;
	_amortMarching				= 	amortMarching;
	_amortStartDate 			= 	amortStartDate;
	_amortType					= 	amortType;
	_backStubDate				=	backStubDate;
	_backStubManualRate			=	backStubManualRate;
	_buyFlag					=	buyFlag;
	_capFloorType				=	capFloorType;
	_currency					=	currency;
	_dayCount					=	dayCount;
	_discountCurve				=	discountCurve;
	_endDate					=	endDate;
	_endDateRollFlag			=	endDateRollFlag;
	_frontStubDate				=	frontStubDate;
	_frontStubManualRate		=	frontStubManualRate;
	_gearFactor					=	gearFactor;
	_initialQuoteCalendars		= 	initialQuoteCalendars;
	_initialQuoteDate			= 	initialQuoteDate;
	_initialQuoteLag			= 	initialQuoteLag;
	_legNo						=	legNo;
	_marketIndex				=	marketIndex;
	_notional					=	notional;
	_payBusDay					=	payBusDay;
	_payCalendars				=	payCalendars;
	_payFreq					=	payFreq;
	_payMarching				=	payMarching;
	_paymentConvention			=	paymentConvention;
	_paymentConversionCurrency	=	paymentConversionCurrency;
	_paymentConversionIndex		=	paymentConversionIndex;
	_paymentConversionLag		=	paymentConversionLag;
	_payLag						=	payLag;
	_payRollDay					=	payRollDay;
	_payRollWeek				=	payRollWeek;
	_pricingMethod				= 	pricingMethod;	//closed Form, Tree, Mc 3000:10000:40000 etc
	_quoteCalendars				=	quoteCalendars;
	_quoteLag					=	quoteLag;
	_resetAveraging				=	resetAveraging;
	_resetConvention			=	resetConvention;
	_resetFreq					=	resetFreq;
	_resetType					=	resetType;
	_scheduleCustomFlag			=	scheduleCustomFlag;
	_spread						=	spread;
	_capStartDate				=	capStartDate;
	_startDateRollFlag			=	startDateRollFlag;
	_strike						=	strike;
	_cfSubType					= 	cfSubType;
	_volId						=   volId;

	// some deafults
	_isPSGenerated				= 	false;
	_isRSGenerated				=	false;
	_isCustomized				=	false;

}

CapFloorTicket::~CapFloorTicket()
{
	// do nothing;
}

bool CapFloorTicket::genPaySchedule()
{


		BusOrCalConv  busOrCalConv(CAL);

		if ( getPayBusDay() != BusDayConv::find("NONE") && getPayRollWeek() != NULL_DOW )
		{
			busOrCalConv =  BusOrCalConv(BUS);
		}

		RollDayConv  * rollDayConv = new RollDayConv  (getPayRollWeek(),getPayRollDay(), busOrCalConv);

		Date frontStubDate = getFrontStubDate();
		Date backStubDate = getBackStubDate();

		Date startDate = getCapStartDate();
		Date endDate   = getEndDate();

		if ( getStartDateRollFlag() == "Yes" )
		{
			startDate = getPayBusDay()->adjustToBusDay(startDate,*CalendarUtil::getCalendar(getPayCalendars()));
					 logFile << "\nstub routine : Start Date is : " << startDate << endl;
		}

		if ( getEndDateRollFlag() == "Yes" )
		{
			endDate = getPayBusDay()->adjustToBusDay(endDate,*CalendarUtil::getCalendar(getPayCalendars()));
			logFile << "\nstub routine : End Date is : " << endDate << endl;
		}


		if ( frontStubDate == getCapStartDate() )
		{
				// there is no front stub
				frontStubDate = startDate;  // set to rolled date to calculate schedule
		}


		if ( backStubDate == getEndDate() )
		{
			// there is no back stub
			backStubDate = endDate;  // set to rolled date to calculate schedule
		}



		if ( ! isPSGenerated() )
		{
			logFile << "GENERATE PAY SCHEDULE " << endl;

			DateMarcher::GenSchedule  genSchedulePay;

		if ( getPayMarching()->genSchedule (
		frontStubDate,
		backStubDate,
		getPayFreq(),
		*CalendarUtil::getCalendar(getPayCalendars()),
		getPayBusDay(),
		genSchedulePay,
		1,  //evenFinalPeriod,
		rollDayConv  ) )
		{

		logFile << "Start and En Dates : " << startDate << " : " << endDate << endl;

			if ( startDate != genSchedulePay.getESMinDate() )
			{
				logFile << "\nFront Stub Date is : ";
				logFile << genSchedulePay.getESMinDate() << endl;
				setFrontStubDate(genSchedulePay.getESMinDate());
			 }

			if ( endDate != genSchedulePay.getESMaxDate() )
			{
				logFile << "\nBack Stub Date is : ";
				logFile << genSchedulePay.getESMaxDate() << endl;
				setBackStubDate(genSchedulePay.getESMaxDate());

			}


			 genSchedulePay.getEventList().sort(); // for backward dates come in reverse order, so need to order ascending order.

			 std::list<Date>::const_iterator iterEvent = genSchedulePay.getEventList().begin () ;

				int noOfEvents = genSchedulePay.getEventList().size();
				logFile << "No of Elements are front :" << noOfEvents << endl;
				int cnt = 0;

			    for ( ; iterEvent != genSchedulePay.getEventList().end () ; ++iterEvent )
			      {
			        shared_ptr <PaySchedule> paySchedule( new PaySchedule());

			        cnt++;

			        if ( cnt != noOfEvents )
			        {

			        	paySchedule->setCouponStartDate(*iterEvent);
			        	paySchedule->setCouponEndDate(*(++iterEvent));

			        	int payLagCnt = getPayLag();
			        	Date paymentDate = paySchedule->getCouponEndDate();

			        	while ( payLagCnt > 0 )
			        	{
			        		paymentDate += Period(1, Days);
			        		paymentDate = getPayBusDay()->adjustToBusDay(paymentDate, *CalendarUtil::getCalendar(getPayCalendars()));
			        		payLagCnt--;
			        	}

			        	if ( payLagCnt == 0 )
			        		paymentDate = getPayBusDay()->adjustToBusDay(paymentDate, *CalendarUtil::getCalendar(getPayCalendars()));

			        	paySchedule->setPaymentDate(paymentDate);

			        	//paySchedule->setPaymentType("Coupon");
			        	//paySchedule->setNotional(getNotional());
			        	 --iterEvent;
			        	 _payScheduleList.push_back(paySchedule);
			        }

			       }

			 }

		if ( getAmortType() != "NONE" )
			{
				 logFile << "GENERATE Amort SCHEDULE " << endl;

					 	 	BusOrCalConv  busOrCalConv(CAL);
				 	 		if ( getPayBusDay() != BusDayConv::find("NONE") && getPayRollWeek() != NULL_DOW )
			 	 			{
			 	 				busOrCalConv =  BusOrCalConv(BUS);
			 	 			}

				 	 			RollDayConv  * rollDayConv = new RollDayConv  (getPayRollWeek(),getPayRollDay(), busOrCalConv);

				 	 			Date frontStubDate = getFrontStubDate();
				 	 			Date backStubDate = getBackStubDate();
				 	 			Date startDate = getCapStartDate();
				 	 			Date endDate   = getEndDate();

				 	 			if ( getStartDateRollFlag() == "Yes" )
				 	 			{
				 	 				startDate = getPayBusDay()->adjustToBusDay(startDate,*CalendarUtil::getCalendar(getPayCalendars()));
				 	 						 logFile << "\nstub routine : Start Date is : " << startDate << endl;
				 	 			}

				 	 			if ( getEndDateRollFlag() == "Yes" )
				 	 			{
				 	 				endDate = getPayBusDay()->adjustToBusDay(endDate,*CalendarUtil::getCalendar(getPayCalendars()));
				 	 				logFile << "\nstub routine : End Date is : " << endDate << endl;
				 	 			}


				 	 			if ( frontStubDate == getCapStartDate() )
				 	 			{
				 	 					// there is no front stub
				 	 					frontStubDate = startDate;  // set to rolled date to calculate schedule
				 	 			}


				 	 			if ( backStubDate == getEndDate() )
				 	 			{
				 	 				// there is no back stub
				 	 				backStubDate = endDate;  // set to rolled date to calculate schedule
				 	 			}

				 DateMarcher::GenSchedule  genScheduleAmort;
				 double amortNotionalTmp = getNotional(); // initialize to leg notional for now
				 Date amortStubDate(01,01,1901);
			 	 const DateMarcher * amortMarching = getAmortMarching();
				 genScheduleAmort.getEventList().clear();

				 if ( amortMarching->genSchedule (
					getAmortStartDate(),
				 	getAmortEndDate(),
				 	getAmortFreq(),
				 	*CalendarUtil::getCalendar(getAmortCalendars()),
				 	getAmortBusDay(),
				 	genScheduleAmort,
				 	1,  //evenFinalPeriod,
				 	rollDayConv  ) )
				 {

				 	genScheduleAmort.getEventList().sort(); // for backward, dates come in reverse order, so need to order ascending order.
				 	std::list<Date>::const_iterator iterEvent = genScheduleAmort.getEventList().begin () ;
				 	int noOfEvents = genScheduleAmort.getEventList().size();
				 	logFile << "No of Elements are front or back - amort :" << noOfEvents - 1 << endl;;
				 	int cnt = 0;

				 	for ( ; iterEvent != genScheduleAmort.getEventList().end () ; ++iterEvent )
				 	{
				 		shared_ptr <AmortSchedule> amortSchedule( new AmortSchedule());
				 		shared_ptr <AmortSchedule> amortScheduleStub( new AmortSchedule());
				 		cnt++;

				 		if ( cnt != 1 )
				 		{
				 			if ( getAmortType() == "PERCENT" )
				 			{
				 				amortNotionalTmp =  amortNotionalTmp - (amortNotionalTmp * getAmortAmount()/100);
				 			}

				 			if ( getAmortType() == "AMOUNT" )
				 			{
				 				amortNotionalTmp = amortNotionalTmp - getAmortAmount();
				 			}

				 			if ( getAmortType() == "EQUAL" )
				 			{
				 				amortNotionalTmp = amortNotionalTmp - (getNotional()/(noOfEvents - 1));

				 				if ( amortNotionalTmp < 0 )
				 					amortNotionalTmp = 0.0;

				 			}
				 			if ( getAmortType() == "MORTGAGE" )
				 			{
				 				double mortExpN = pow((1 + ( getAmortAmount()/(100 * (int) getPayFreq())) ) , (noOfEvents -2 ));
				 				double mortExpC = pow((1 + ( getAmortAmount()/(100 * (int) getPayFreq())) ) , (cnt -1 ));

				 				amortNotionalTmp = getNotional() * ( (mortExpN - mortExpC) / ( mortExpN -1 ));

				 			}
				 		}

				 		if ( cnt != noOfEvents )
				 		{

				 			amortSchedule->setStartDate(*iterEvent);
				 		    amortSchedule->setEndDate(*(++iterEvent));
				 			 --iterEvent;

				 			if ( getFrontStubDate() != getCapStartDate() && getFrontStubDate() < amortSchedule->getEndDate()
				 					&& cnt == 1 )
				 			{
				 				amortScheduleStub->setStartDate( getCapStartDate() );
				 				amortScheduleStub->setEndDate( getFrontStubDate() );
				 				amortScheduleStub->setAmortNotional(amortNotionalTmp);
				 				_amortScheduleList.push_back(amortScheduleStub);
				 				amortSchedule->setStartDate( getFrontStubDate() );
				 				logFile << "Amort Dates and Notionals for Front Stub : " << amortScheduleStub->getStartDate() << " : "
				 						 			<< amortScheduleStub->getEndDate() << " : " << amortScheduleStub->getAmortNotional() << endl;

				 				if ( getAmortType() == "PERCENT" )
				 				{
				 					 amortNotionalTmp =  amortNotionalTmp - (amortNotionalTmp * getAmortAmount()/100);
				 				}

				 				if ( getAmortType() == "AMOUNT" )
				 				{
				 					 amortNotionalTmp = amortNotionalTmp - getAmortAmount();
				 				}

				 				if ( getAmortType() == "EQUAL" )
				 				{
				 					 amortNotionalTmp = amortNotionalTmp - (getNotional()/(noOfEvents - 1));

				 					if ( amortNotionalTmp < 0 )
				 						amortNotionalTmp = 0.0;

				 				}

				 				if ( getAmortType() == "MORTGAGE" )
				 				{
				 					double mortExpN = pow((1 + ( getAmortAmount()/(100 * (int) getPayFreq())) ) , (noOfEvents - 2 ));
				 					double mortExpC = pow((1 + ( getAmortAmount()/(100 * (int) getPayFreq())) ) , (cnt ));

				 					amortNotionalTmp = getNotional() * ( (mortExpN - mortExpC) / ( mortExpN -1 ));

				 				}


				 			}

				 			amortSchedule->setAmortNotional(amortNotionalTmp);
				 			_amortScheduleList.push_back(amortSchedule);
				 			logFile << "Amort Dates and Notionals : " << amortSchedule->getStartDate() << " : " << amortSchedule->getEndDate() << " : "
				 					<< amortSchedule->getAmortNotional() << endl;
				 		}
				 		if ( cnt == noOfEvents )
				 		{
				 			amortSchedule->setStartDate(*iterEvent);
				 			if ( amortSchedule->getStartDate() < getEndDate() )
				 			{
				 				amortSchedule->setEndDate(*iterEvent);

				 				if ( getAmortType() == "MORTGAGE" )
				 					amortNotionalTmp = 0.0;

				 				amortSchedule->setAmortNotional(amortNotionalTmp);
				 				_amortScheduleList.push_back(amortSchedule);
				 				logFile << "Amort Dates and Notionals - last : " << amortSchedule->getStartDate() << " : " << amortSchedule->getEndDate() << " : "
				 					 << amortSchedule->getAmortNotional() << endl;
				 			}
				 		}

				   }

				 }
		 	   } // amort schedule done here


		}


		if ( ! genResetSchedule() )
		{
			logFile << "Reset Schedule failed to generate " << endl;
			return false;
		}


		setIsRSGenerated(true);
		setIsPSGenerated(true);

		return true;
}

bool CapFloorTicket::genResetSchedule()
{

	if ( ! isRSGenerated() )
		{
			DateMarcher::GenSchedule  genScheduleReset;

			BusOrCalConv busOrCalConv(CAL);

			if ( getPayBusDay() != BusDayConv::find("NONE") && getPayRollDay() == 0 )
			{
				 busOrCalConv = BusOrCalConv(BUS);
			}

			RollDayConv  * rollDayConv = new RollDayConv (getPayRollWeek(), getPayRollDay(), busOrCalConv);

			Date frontStubDate = getFrontStubDate();
			Date backStubDate = getBackStubDate();

			Date startDate = getCapStartDate();
			Date endDate   = getEndDate();

			if ( getStartDateRollFlag() == "Yes" )
			{
				startDate = getPayBusDay()->adjustToBusDay(startDate,*CalendarUtil::getCalendar(getPayCalendars()));
			    logFile << "\nstub routine : Start Date is : " << startDate << endl;
			}

			if ( getEndDateRollFlag() == "Yes" )
			{
				endDate = getPayBusDay()->adjustToBusDay(endDate,*CalendarUtil::getCalendar(getPayCalendars()));
				logFile << "\nstub routine : End Date is : " << endDate << endl;
			}

			if ( frontStubDate == getCapStartDate() )
			{
					// there is no front stub
				frontStubDate = startDate;  // set to rolled date to calculate schedule
			}


			if ( backStubDate == getEndDate() )
			{
				// there is no back stub
				backStubDate = endDate;  // set to rolled date to calculate schedule
			}


			_resetScheduleList.clear(); // clear the lists

			if ( getPayMarching()->genSchedule (frontStubDate,backStubDate,	getResetFreq(),
					*CalendarUtil::getCalendar(getPayCalendars()),	getPayBusDay(),		genScheduleReset,		1, 		rollDayConv  ) )
			{

				genScheduleReset.getEventList().sort(); // for backward dates will come in reverse order, so need to sort in ascending order.
				std::list<Date>::const_iterator iterEventReset = genScheduleReset.getEventList().begin () ;

				int noOfEvents = genScheduleReset.getEventList().size();
				logFile << "No of Elements are front :" << noOfEvents << endl;

				int lagSign = getQuoteLag() >= 0 ? 1 : -1;
				logFile << "lag sign is : " << lagSign << endl;
				const BusDayConv * resetBusDay = lagSign > 0 ? BusDayConv::find("FOL") : BusDayConv::find("PRE") ;
				int lag = getQuoteLag() * lagSign;
				logFile << "lag is : " << lag << endl;
				int resetCnt = 0;

				for ( ; iterEventReset != genScheduleReset.getEventList().end () ; ++iterEventReset )
				{
				    shared_ptr <ResetSchedule> resetSchedule( new ResetSchedule());
	   	        	resetSchedule->setResetStartDate(*iterEventReset);

	   	        	Date quoteDate = resetSchedule->getResetStartDate();
	   	        	resetSchedule->setRateIndexType("IRRATE");

	   	        	resetCnt++;

	   	         if ( resetCnt != noOfEvents )
	   	     		{
	   	     		   	++iterEventReset;
	   	     		   	resetSchedule->setResetEndDate(*iterEventReset);
	   	     		   	--iterEventReset; // CHANGE IT BACK

	   		   	      	logFile << "Reset Start - End Date : " << resetSchedule->getResetStartDate() << ":"
	   		   	      			<< resetSchedule->getResetEndDate() << endl;

		        		if ( getResetConvention() == "IN_ARREARS" )
		        			quoteDate = resetSchedule->getResetEndDate();
	   	     		}

	        		if ( getInitialQuoteDate() != Date(01,01,1901) && resetCnt == 1
	        	        		&& getFrontStubDate() == getCapStartDate()  )  // no front stub
	        	    {
	        	       	 quoteDate = getInitialQuoteDate();
	        	    }
	        	    else
	        	    {
	        	    	int cntReset = lag;

	        	    	while ( cntReset > 0 )
	        	    	{
	        	    		Period period(lagSign * 1,Days);
	        	    		quoteDate = quoteDate + period;
	        	    		quoteDate = resetBusDay->adjustToBusDay(quoteDate,*CalendarUtil::getCalendar(getQuoteCalendars()) );
	        	    		cntReset--;

	        	    	}

					if (  cntReset == 0 )
						quoteDate = resetBusDay->adjustToBusDay(quoteDate,*CalendarUtil::getCalendar(getQuoteCalendars()) );
	        	    }

					resetSchedule->setQuoteDate( quoteDate );
					resetSchedule->setRate(getPeriodRate(FixingRates::getFixingRate(quoteDate, resetSchedule->getResetStartDate(), getMarketIndex())));

					if ( resetSchedule->getResetStartDate() != backStubDate && getBackStubDate() == getEndDate() )
						_resetScheduleList.push_back(resetSchedule);
					else if ( getBackStubDate() != getEndDate() )
					{
						_resetScheduleList.push_back(resetSchedule);
					}



					if ( getBackStubDate() != getEndDate() && getBackStubDate() == resetSchedule->getResetStartDate() )
					{
						// we are going to force generate stub tenors
						setIsPSGenerated(true);

						if ( ! generateStubs() )
							logFile << "failed stub generation" << endl;

						setIsPSGenerated(false);

							displayPaySchedule().sort();
							PayScheduleList::const_iterator iterPay = displayPaySchedule().begin();

							Date couponStartDate(01,01,1901);
							Date couponEndDate(01,01,1901);

							for ( ; iterPay != displayPaySchedule().end() ; ++iterPay )
							{

								if ( (*iterPay)->getCouponStartDate() == getBackStubDate() )
								{
									couponStartDate = (*iterPay)->getCouponStartDate();
									couponEndDate = (*iterPay)->getCouponEndDate();
									break; // no need to continue, got the dates
								}
							}

							_stubResetsList.sort();
							resetSchedule->setResetEndDate(couponEndDate);

							StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
							String marketIndexA = "";
							String marketIndexB = "";
							Period stubTenorA;
							Period stubTenorB;

							for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
							{

								if ( (*iterStubReset)->getStartDate() == resetSchedule->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubA" )
								{
									marketIndexA = (*iterStubReset)->getStubMarketIndex();
									stubTenorA = (*iterStubReset)->getStubTenor();

								}
								else if ( (*iterStubReset)->getStartDate() == resetSchedule->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubB" )
								{
									marketIndexB = (*iterStubReset)->getStubMarketIndex();
									stubTenorB = (*iterStubReset)->getStubTenor();

								}
							}

							if ( FixingRates::getFixingRate(quoteDate,resetSchedule->getResetStartDate() , getMarketIndex()) == -1
										&& quoteDate < Date::todaysDate() )
									resetSchedule->setRateSettingType("HISTORIC");
								else if ( FixingRates::getFixingRate(quoteDate, resetSchedule->getResetStartDate(), getMarketIndex()) != 0
										&& quoteDate <= Date::todaysDate() )
									resetSchedule->setRateSettingType("RATESET");
								else if ( quoteDate > Date::todaysDate() )
									resetSchedule->setRateSettingType("PROJECTED");

							resetSchedule->setRate(getPeriodRate(FixingRates::getFixingRate( resetSchedule->getQuoteDate(),
													marketIndexA, marketIndexB, couponStartDate ,
												couponEndDate, getPayBusDay() )) );

						 	logFile << "Reset Start - End Date : " << resetSchedule->getResetStartDate() << ":"
						 			<< resetSchedule->getResetEndDate() << endl;

							_resetScheduleList.pop_back();
							_resetScheduleList.push_back(resetSchedule); // update with latest info

					}

				  }

			     // take care of front and back stubs now

			     if ( getFrontStubDate() != getCapStartDate() )
			     {
	     		     shared_ptr <ResetSchedule> resetScheduleStub( new ResetSchedule());

				     resetScheduleStub->setResetStartDate(startDate);
				     resetScheduleStub->setResetEndDate(getFrontStubDate());
				     resetScheduleStub->setRateIndexType("IRRATE");

				     Date quoteDate = resetScheduleStub->getResetStartDate();

		        		if ( getResetConvention() == "IN_ARREARS" )
		        	        	quoteDate = resetScheduleStub->getResetEndDate();

				 	if ( getInitialQuoteDate() != Date(01,01,1901)  )  // no front stub
				    {
				       	 quoteDate = getInitialQuoteDate();
				    }
				    else
				    {

				     int cntReset = lag;

				     while ( cntReset > 0 )
				     {
				     	Period period(lagSign * 1,Days);
				     	quoteDate = quoteDate + period;
				     	quoteDate = resetBusDay->adjustToBusDay(quoteDate,*CalendarUtil::getCalendar(getQuoteCalendars()) );
				     	cntReset--;

				     }

				     if (  cntReset == 0 )
							quoteDate = resetBusDay->adjustToBusDay(quoteDate,*CalendarUtil::getCalendar(getQuoteCalendars()) );

				    }

				     resetScheduleStub->setQuoteDate( quoteDate );
				     resetScheduleStub->setRate(getPeriodRate(FixingRates::getFixingRate(quoteDate, resetScheduleStub->getResetStartDate(), getMarketIndex())));

			    	 displayPaySchedule().sort();
				     PayScheduleList::const_iterator iterPay = displayPaySchedule().begin();

				     	_resetScheduleList.push_front(resetScheduleStub);

						setIsPSGenerated(true);

						if ( ! generateStubs() )
							logFile << "failed stub generation" << endl;

						setIsPSGenerated(false);

				     	Date couponStartDate(01,01,1901);
				     	Date couponEndDate(01,01,1901);

				     		for ( ; iterPay != displayPaySchedule().end() ; ++iterPay )
				     		{

				     			if ( (*iterPay)->getCouponEndDate() == getFrontStubDate() )
				     			{
				     				couponStartDate = (*iterPay)->getCouponStartDate();
				     				couponEndDate = (*iterPay)->getCouponEndDate();
				     				break; // no need to continue, got the dates
				     			}
				     		}

				     		_stubResetsList.sort();

				     		StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
				     		String marketIndexA = "";
				     		String marketIndexB = "";
				     		Period stubTenorA;
				     		Period stubTenorB;

				     		for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
				     		{

				     			logFile << "details " << (*iterStubReset)->getStartDate() << " : " << startDate << endl;

				     			if ( (*iterStubReset)->getStartDate() == startDate && (*iterStubReset)->getStubType() == "FStubA" )
				     			{
				     				marketIndexA = (*iterStubReset)->getStubMarketIndex();
				     				stubTenorA = (*iterStubReset)->getStubTenor();
				     			}
				     			else if ( (*iterStubReset)->getStartDate() == startDate && (*iterStubReset)->getStubType() == "FStubB" )
				     			{
				     				marketIndexB = (*iterStubReset)->getStubMarketIndex();
				     				stubTenorB = (*iterStubReset)->getStubTenor();
				     			}
				     		}

				     			resetScheduleStub->setRate(getPeriodRate(FixingRates::getFixingRate( quoteDate,
				     							marketIndexA, marketIndexB, couponStartDate ,
				     								couponEndDate, getPayBusDay() )) );

				     logFile << "Reset Start - End Date : " << resetScheduleStub->getResetStartDate() << ":" << resetScheduleStub->getResetEndDate() << endl;
				     _resetScheduleList.pop_front();

				     _resetScheduleList.push_front(resetScheduleStub);

				  }

			      ResetScheduleList::const_iterator iterReset = displayResetSchedule().begin() ;

			      for ( ; iterReset != displayResetSchedule().end() ; ++iterReset )
	   		      {
					logFile <<"\n Reset Start Date : Quote Date : Period Rate  - ";
					logFile << (*iterReset)->getResetStartDate() << " : " << (*iterReset)->getQuoteDate() << " : "
							<< (*iterReset)->getRate() << " : " << (*iterReset)->getRateIndexType() << endl;

	   		       }

			} // genSchedule finished

				setIsRSGenerated(true); // resets generated now
		} // schedule generation finished

		return true;

}


double CapFloorTicket::getPeriodRate( double rate)  // gets period rate including spread and gear factor
{

		return rate * getGearFactor() + getSpread()/10000; // note spread is in basis points

}


bool CapFloorTicket::generateStubs()
{

	Date startDate = getCapStartDate();
	Date endDate = getEndDate();
	Date fDate = getCapStartDate();
	Date bDate = getEndDate();


	if ( getStartDateRollFlag() == "Yes" )
	{
		startDate = getPayBusDay()->adjustToBusDay(startDate,*CalendarUtil::getCalendar(getPayCalendars()));
		logFile << "\nstub routine : Start Date is : " << startDate << endl;
	}

	if ( getEndDateRollFlag() == "Yes" )
	{
		endDate = getPayBusDay()->adjustToBusDay(endDate,*CalendarUtil::getCalendar(getPayCalendars()));
		 logFile << "\nstub routine : End Date is : " << endDate << endl;
	}


	if (! isPSGenerated() ) // generate payment schedule if not generated already
		if ( ! genPaySchedule() )
			return false; // issues in generating payment schedule

		shared_ptr <StubResets> fsResetsA( new StubResets());
		shared_ptr <StubResets> fsResetsB( new StubResets());
		shared_ptr <StubResets> bsResetsA( new StubResets());
		shared_ptr <StubResets> bsResetsB( new StubResets());

		Period fsTenorA(0,Days);
		Period fsTenorB(0,Days);
		Period bsTenorA(0,Days);
		Period bsTenorB(0,Days);

		if ( getFrontStubDate() != fDate )
		{
			int daysDiff = getFrontStubDate().serialNumber() - startDate.serialNumber();

			if ( daysDiff > 0 && daysDiff <= 2 )
			{
				fsTenorA = Period(2,Days);
				fsTenorB = Period(2,Days);
				logFile << "Stubf Tenors are : 2D:2D" << endl;
			}

			if ( daysDiff <= 7 && daysDiff > 2 )
			{
				fsTenorA = Period(2,Days);
				fsTenorB = Period(1,Weeks);
				logFile << "Stubf Tenors are : 2D:1W " << endl;
			}

			if ( daysDiff <= 14 && daysDiff > 7)
			{
				fsTenorA = Period(1, Weeks);
				fsTenorB = Period(2, Weeks);
				logFile << "Stubf Tenors are : 1W:2W" << endl;
			}

			if ( daysDiff <= startDate.monthLength(startDate.month(),Date::isLeap(startDate.year())) && daysDiff > 14 )
			{
				fsTenorA = Period(2, Weeks);
				fsTenorB = Period(1, Months);
				logFile << "Stubf Tenors are : 2W:1M" << endl;
			}

			if ( daysDiff > startDate.monthLength(startDate.month(),Date::isLeap(startDate.year()) ) )
			{
				int month = 0;
				Date tmpDate = startDate;

				while ( tmpDate < getFrontStubDate()  )
				{
					tmpDate += Period(1,Months);
					month++;
				}


				fsTenorA = Period(month-1,Months);
				fsTenorB = Period(month,Months);

				logFile << "Stubf Tenors are : " << month -1 << "M::" << month << "M" << endl;

			}

			ResetScheduleList::const_iterator iterReset = displayResetSchedule().begin() ;

			for ( ; iterReset != displayResetSchedule().end() ; ++iterReset )
			{
				if ( getFrontStubDate() == (*iterReset)->getResetStartDate() &&
						(*iterReset)->getRateIndexType() == "IRRATE" )
				{
					// note, it is the event that starts before the front stub, we are interested in :-) ...

					fsResetsA->setStartDate((*(--iterReset))->getResetStartDate());
					++iterReset;
					fsResetsA->setQuoteDate((*(--iterReset))->getQuoteDate());
					++iterReset;
					fsResetsA->setStubRateType("P"); // projected first time even if it is in the past.
					fsResetsA->setStubMarketIndex(FixingRates::getFixingQuote(getMarketIndex(),fsTenorA));
					fsResetsA->setStubType("FStubA");
					fsResetsA->setStubTenor(fsTenorA);
					fsResetsA->setManualStub(false);

					_stubResetsList.push_back(fsResetsA);

					fsResetsB->setStartDate((*(--iterReset))->getResetStartDate());
					++iterReset;
					fsResetsB->setQuoteDate((*(--iterReset))->getQuoteDate());
					++iterReset;
					fsResetsB->setStubRateType("P"); // projected first time even if it is in the past
					fsResetsB->setStubMarketIndex(FixingRates::getFixingQuote(getMarketIndex(),fsTenorB));
					fsResetsB->setStubType("FStubB");
					fsResetsB->setStubTenor(fsTenorB);
					fsResetsB->setManualStub(false);

					_stubResetsList.push_back(fsResetsB);
				}

			}

		}

		if ( getBackStubDate() != bDate )
		{
			int daysDiff = endDate.serialNumber() - getBackStubDate().serialNumber();

			if ( daysDiff > 0 && daysDiff <= 2 )
			{
				bsTenorA = Period(2, Days);
				bsTenorB = Period(2, Days);
				logFile << "Stub Tenors are : 2D:2D" << endl;
			}


			if ( daysDiff <= 7 && daysDiff > 2 )
			{
				bsTenorA = Period(2, Days);
				bsTenorB = Period(1, Weeks);
				logFile << "Stub Tenors are : 2D:1W" << endl;
			}

			if ( daysDiff <= 14 && daysDiff > 7)
			{
				bsTenorA = Period(1, Weeks);
				bsTenorB = Period(2, Weeks);
				logFile << "Stub Tenors are : 1W:2W" << endl;
			}

			if ( daysDiff <= endDate.monthLength(endDate.month(),Date::isLeap(endDate.year())) && daysDiff > 14 )
			{
				bsTenorA = Period(2, Weeks);
				bsTenorB = Period(1, Months);
				logFile << "Stub Tenors are : 2W:1M" << endl;
			}

			if ( daysDiff > endDate.monthLength(endDate.month(),Date::isLeap(endDate.year()) ) )
			{
				int month = 0;
				Date tmpDate = endDate;

				while ( tmpDate > getBackStubDate()  )
				{
					tmpDate = tmpDate - Period(1,Months);
					month++;
				}

			  bsTenorA = Period(month -1 , Months );
			  bsTenorB = Period(month, Months );

			  logFile << "Stub Tenors are : " << month -1 << "M::" << month <<"M" << endl;

			}

			ResetScheduleList::const_iterator iterReset = displayResetSchedule().begin() ;

			for ( ; iterReset != displayResetSchedule().end() ; ++iterReset )
			{
				if ( getBackStubDate() == (*iterReset)->getResetStartDate() &&
						(*iterReset)->getRateIndexType() == "IRRATE" )
				{
						bsResetsA->setStartDate((*iterReset)->getResetStartDate());
						bsResetsA->setQuoteDate((*iterReset)->getQuoteDate());
						bsResetsA->setStubRateType("P"); // projected first time even if it is in the past.
						bsResetsA->setStubMarketIndex(FixingRates::getFixingQuote(getMarketIndex(),bsTenorA));
						bsResetsA->setStubType("BStubA");
						bsResetsA->setStubTenor(bsTenorA);
						bsResetsA->setManualStub(false);
						_stubResetsList.push_back(bsResetsA);

						bsResetsB->setStartDate((*iterReset)->getResetStartDate());
						bsResetsB->setQuoteDate((*iterReset)->getQuoteDate());
						bsResetsB->setStubRateType("P"); // projected first time even if it is in the past
						bsResetsB->setStubMarketIndex(FixingRates::getFixingQuote(getMarketIndex(),bsTenorB));
						bsResetsB->setStubType("BStubB");
						bsResetsB->setStubTenor(bsTenorB);
						bsResetsB->setManualStub(false);
						_stubResetsList.push_back(bsResetsB);

				}

			}

		}

	 // now we have stub tenors generated

		return true;
}

bool CapFloorTicket::genCashFlows()
{

		if (! isPSGenerated() ) // generate payment schedule if not generated already
			if ( ! genPaySchedule() )
				return false; // issues in generating payment schedule



		 // payment schedule
					         PayScheduleList::const_iterator iterPay1 = displayPaySchedule().begin() ;

					         std::list<Date> _dates;

					         for ( ; iterPay1 != displayPaySchedule().end() ; ++iterPay1 )
					         {

					        	logFile << "PaySchedule list " << endl;
					        	 logFile <<"Start Date : " << (*iterPay1)->getCouponStartDate() << endl;
					        	 logFile << "End Date : " << (*iterPay1)->getCouponEndDate() << endl;
					        	 logFile << "Payment Date is : " << (*iterPay1)->getPaymentDate() << endl;
					        	 logFile << endl;
					        	 _dates.push_back((*iterPay1)->getCouponStartDate() );

					         }

					         _dates.sort();

					         std::list<Date>::const_iterator iterD = _dates.begin() ;


					       	 for ( ; iterD != _dates.end() ; ++iterD )
					       	{

					       	logFile << "Date list " << endl;
					       	logFile <<"Start Date : " << (*iterD) << endl;

					       	}



		PayScheduleList::const_iterator iterPay = displayPaySchedule().begin();
		Date amortStubDate(01,01,1901);
		double lastAmortNotional = getNotional();
		double dcfNot = 0.0;
		double periodRate = 0.0;

		iterD = _dates.begin(); // dates are not coming in order
		for ( ; iterD != _dates.end() ; ++iterD )
		{

		    iterPay = displayPaySchedule().begin();

		  for ( ; iterPay != displayPaySchedule().end() ; ++iterPay )
		  {

			  if ( (*iterPay)->getCouponStartDate() != (*iterD))
				continue;

			bool finalPeriod = ( getEndDate() != getBackStubDate() &&
							getBackStubDate() == (*iterPay)->getCouponStartDate() ) ? true : false ;
			bool stubPeriod =  ( (getEndDate() != getBackStubDate() && getBackStubDate() == (*iterPay)->getCouponStartDate()) ||
								( getCapStartDate() != getFrontStubDate() && getFrontStubDate() == (*iterPay)->getCouponStartDate() ) ) ? true : false ;

					 ResetScheduleList::const_iterator iterReset = displayResetSchedule().begin();
					 int resetCnt = 0;
					 double tmpPeriodRate = 0.0;

					 for ( ; iterReset != displayResetSchedule().end() ; ++iterReset )
					 {
						if ( (*iterReset)->getRateIndexType() == "IRRATE" )
						{


					 	if ( ( (*iterPay)->getCouponStartDate() <= (*iterReset)->getResetStartDate() &&
					 			(*iterPay)->getCouponEndDate() > (*iterReset)->getResetStartDate() &&
					 			getResetAveraging() != "NONE" )	|| ( (*iterPay)->getCouponStartDate() == (*iterReset)->getResetStartDate()
					 					&& getResetAveraging() == "NONE" ) )
					 	{


					 		if ( getFrontStubDate() != getCapStartDate() && (*iterPay)->getCouponEndDate() == getFrontStubDate() ) // there is a front stub
					 		{
					 			_stubResetsList.sort();

					 			StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
					 			String marketIndexA = "";
					 			String marketIndexB = "";
					 			Period stubTenorA;
					 			Period stubTenorB;

					 			for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
					 			{
					 				if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "FStubA" )
					 				{
					 					marketIndexA = (*iterStubReset)->getStubMarketIndex();
					 					stubTenorA = (*iterStubReset)->getStubTenor();
					 				}
					 				else if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "FStubB" )
					 				{
					 					marketIndexB = (*iterStubReset)->getStubMarketIndex();
					 					stubTenorB = (*iterStubReset)->getStubTenor();
					 				}
					 			}

					 			   periodRate = getPeriodRate(FixingRates::getFixingRate((*iterReset)->getQuoteDate(), marketIndexA,
					 					   marketIndexB, (*iterPay)->getCouponStartDate(),
					 					   (*iterPay)->getCouponEndDate() , getPayBusDay()));


					 			  resetCnt++;
					 			  if ( getResetAveraging() == "WEIGHTED_CAL" )
					 			  {
					 				  tmpPeriodRate += periodRate * ( (*iterPay)->getCouponEndDate().serialNumber() - (*iterPay)->getCouponStartDate().serialNumber() );
					 				  logFile << "tmpPeriod Rate front is : " << tmpPeriodRate << endl;
					 			  }
					 			  else if ( getResetAveraging() == "UNWEIGHTED" )
					 			  {
					 				 tmpPeriodRate += periodRate;
					 				  logFile << "tmpPeriod Rate front is : " << tmpPeriodRate << endl;
					 			  }

					 		}
					 		else if ( getBackStubDate() != getEndDate() && (*iterPay)->getCouponStartDate() == getBackStubDate() ) // there is a back stub
					 		{
					 				_stubResetsList.sort();

					 				StubResetsList::const_iterator iterStubReset = _stubResetsList.begin() ;
					 				String marketIndexA = "";
					 				String marketIndexB = "";
					 				Period stubTenorA;
					 				Period stubTenorB;


					 			for ( ; iterStubReset != _stubResetsList.end() ; ++iterStubReset )
					 			{
					 				if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubA" )
					 				{
					 					marketIndexA = (*iterStubReset)->getStubMarketIndex();
					 					stubTenorA = (*iterStubReset)->getStubTenor();

					 				}
					 				else if ( (*iterStubReset)->getStartDate() == (*iterReset)->getResetStartDate() && (*iterStubReset)->getStubType() == "BStubB" )
					 				{
					 					marketIndexB = (*iterStubReset)->getStubMarketIndex();
					 					stubTenorB = (*iterStubReset)->getStubTenor();
					 				}
					 			}

					 				periodRate = getPeriodRate(FixingRates::getFixingRate( (*iterReset)->getQuoteDate(), marketIndexA,
					 						marketIndexB , (*iterPay)->getCouponStartDate(),
					 						(*iterPay)->getCouponEndDate(), getPayBusDay() ));

					 				resetCnt++;

					 				if ( getResetAveraging() == "WEIGHTED_CAL" )
					 				{
					 				  tmpPeriodRate += periodRate * ( (*iterPay)->getCouponEndDate().serialNumber() - (*iterPay)->getCouponStartDate().serialNumber() );
					 				  logFile << "tmpPeriod Rate front is : " << tmpPeriodRate << endl;
					 				}
					 				else if ( getResetAveraging() == "UNWEIGHTED" )
					 				{
					 				  tmpPeriodRate += periodRate;
					 				  logFile << "tmpPeriod Rate front is : " << tmpPeriodRate << endl;
					 				}

					 		}
					 		else
					 		{
					 				periodRate = getPeriodRate(FixingRates::getFixingRate((*iterReset)->getQuoteDate(), (*iterReset)->getResetStartDate(),getMarketIndex()));
					 				resetCnt++;

					 				logFile << " Period rate is : " << periodRate << endl;
					 				if ( getResetAveraging() == "WEIGHTED_CAL" )
					 				{
					 					tmpPeriodRate += periodRate * ( (*(++iterReset))->getResetStartDate().serialNumber() - (*(--iterReset))->getResetStartDate().serialNumber()) ;
					 					logFile << "tmpPeriod Rate back is : " << tmpPeriodRate << endl;
					 				}
					 				else if ( getResetAveraging() == "UNWEIGHTED" )
					 				{
					 				    tmpPeriodRate += periodRate;
					 					logFile << "tmpPeriod Rate back is : " << tmpPeriodRate << endl;
					 				}
					 		}

					 	}
					}
				  }

					 if ( getResetAveraging() == "WEIGHTED_CAL" )
						 periodRate = tmpPeriodRate/( (*iterPay)->getCouponEndDate().serialNumber() - (*iterPay)->getCouponStartDate().serialNumber() );
					 else if ( getResetAveraging() == "UNWEIGHTED" )
						 periodRate = tmpPeriodRate / resetCnt;


			if ( getBuyFlag() == "Yes"  && getCapFloorType() == "CAP" )
			{

				if ( ( periodRate - getStrike()/100) > 0.0 )
					periodRate = (periodRate - getStrike()/100); // in the money
				else
					periodRate = 0.0; // out of the money
			}
			else if ( getBuyFlag() == "Yes"  && getCapFloorType() == "FLOOR" )
			{
				if ( (  getStrike()/100 - periodRate ) > 0 )
					periodRate = ( getStrike()/100 - periodRate ); // in the money
				else
					periodRate = 0.0; // out of the money
			}
			else if ( getBuyFlag() == "No"  && getCapFloorType() == "CAP" )
			{
				if ( ( periodRate - getStrike()/100) > 0 )
						periodRate = (periodRate - getStrike()/100) * -1.0; // sell : out of the money
				else
					periodRate = 0.0; // sell: in the money
			}
			else if ( getBuyFlag() == "No"  && getCapFloorType() == "FLOOR" )
			{
				if ( (  getStrike()/100 - periodRate ) > 0 )
						periodRate = ( getStrike()/100 - periodRate ) * -1.0; // sell: out of the money
				else
					periodRate = 0.0; // in the money

			}

			 logFile << "ultimate period rate is : " << periodRate << endl;

			dcfNot = getNotional() * getDayCount()->getFraction((*iterPay)->getCouponStartDate(),
									 			(*iterPay)->getCouponEndDate(), finalPeriod,stubPeriod, (int) getPayFreq() );


			logFile << "dcf notional at this stage is : " << dcfNot << endl;


			if ( getAmortType() != "NONE" )
			{

				dcfNot = 0.0;
				//displayAmortSchedule().reverse();
				AmortScheduleList::const_iterator iterAmort = displayAmortSchedule().begin();

				if ( (*iterPay)->getCouponStartDate() <= getAmortEndDate() )
				{
					 for ( ; iterAmort != displayAmortSchedule().end() ; ++iterAmort )
					 {
						logFile << "Amort Dates: " << (*iterAmort)->getStartDate() << " : " << (*iterAmort)->getEndDate() << endl;

					 if (  ( (*iterPay)->getCouponStartDate() >= (*iterAmort)->getStartDate()  &&
					 		 (*iterPay)->getCouponStartDate() < (*iterAmort)->getEndDate()  &&
					 		(*iterPay)->getCouponEndDate() >= (*iterAmort)->getEndDate()  ) )
					 	{
					 		if ( amortStubDate > (*iterAmort)->getStartDate() )
					 		{
					 			dcfNot += (*iterAmort)->getAmortNotional() * getDayCount()->getFraction( amortStubDate,
					 							 		 		         (*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() ) * periodRate;

					 			lastAmortNotional = (*iterAmort)->getAmortNotional();
					 			logFile << "Notional 1-1 is : " << lastAmortNotional << endl;
					 		}
					 		else
					 		{
					 			dcfNot += (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
					 							 		(*iterAmort)->getEndDate(), finalPeriod,stubPeriod, (int) getAmortFreq() ) * periodRate;

					 			lastAmortNotional = (*iterAmort)->getAmortNotional();
					 			logFile << "Notional 11 is : " << lastAmortNotional << endl;
					 		}


					 		logFile << "Payment Amount 1: " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate()
					 				 << " : " << (*iterAmort)->getStartDate() << " : " << amortStubDate << " : " << (*iterAmort)->getEndDate() << " : " <<  dcfNot << endl;
					 		amortStubDate = (*iterAmort)->getEndDate();
					 		logFile << "Notional 1 is : " << lastAmortNotional << endl;
					 		logFile << "Period rate 1 is : " << periodRate << endl;
					 	}
					 	else if ( (*iterPay)->getCouponEndDate() > (*iterAmort)->getStartDate() &&
					 			 amortStubDate <= (*iterAmort)->getStartDate() )
					 	{
					 		if ( (*iterPay)->getCouponEndDate() >= (*iterAmort)->getEndDate() )
					 		{
					 			if ( (*iterAmort)->getStartDate() == getAmortEndDate() )
					 			{
					 				dcfNot += (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
					 						(*iterPay)->getCouponEndDate(), finalPeriod,stubPeriod,  (int) getAmortFreq() ) * periodRate;

					 				amortStubDate = (*iterPay)->getCouponEndDate();
					 				lastAmortNotional = (*iterAmort)->getAmortNotional();

					 				logFile << "Payment Amount stub 1: " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate()
					 					<< " : " << (*iterAmort)->getStartDate() << " : " << (*iterPay)->getCouponEndDate() << " : " <<  dcfNot << endl;
					 				logFile << "Period rate is 0: " << periodRate << endl;
					 				logFile << "Notional 2 is : " << lastAmortNotional << endl;

					 			}
					 			else
					 			{
					 				dcfNot += (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
					 						 (*iterAmort)->getEndDate(), finalPeriod,stubPeriod,  (int) getAmortFreq() ) * periodRate;

					 				amortStubDate = (*iterAmort)->getEndDate();
					 				lastAmortNotional = (*iterAmort)->getAmortNotional();

					 				logFile << "Payment Amount stub 2: " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate()
					 				<< " : " << (*iterAmort)->getStartDate() << " : " << (*iterAmort)->getEndDate() << " : " <<  dcfNot << endl;
					 				logFile << "Period rate is : " << periodRate << endl;
					 				logFile << "Notional 3 is : " << lastAmortNotional << endl;
					 			}


					 		}
					 		else
					 		{
					 			dcfNot += (*iterAmort)->getAmortNotional() * getDayCount()->getFraction((*iterAmort)->getStartDate(),
					 						(*iterPay)->getCouponEndDate(), finalPeriod,stubPeriod,  (int) getAmortFreq() ) * periodRate;

					 			amortStubDate = (*iterPay)->getCouponEndDate();
					 			lastAmortNotional = (*iterAmort)->getAmortNotional();

					 			 logFile << "Payment Amount stub 3: " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate()
					 					 << " : " << (*iterAmort)->getStartDate() << " : " << (*iterAmort)->getEndDate() << " : " <<  dcfNot << endl;
					 			logFile << "Period rate is 2 : " << periodRate << endl;
					 			logFile << "Notional 4 is : " << lastAmortNotional << endl;
					 		}
					 	}
					 }


				 	 (*iterPay)->setNotional(lastAmortNotional);
				 	(*iterPay)->setPeriodRate(periodRate);
					 (*iterPay)->setAmount(dcfNot);
					 logFile << "Payment Amount 2 : " << (*iterPay)->getCouponStartDate() << " : "
							 << (*iterPay)->getCouponEndDate() << " : " << (*iterPay)->getAmount()
							  << endl;

				}
				else
				{
					logFile << "Notional final is : " << lastAmortNotional << endl;
					dcfNot = lastAmortNotional * getDayCount()->getFraction((*iterPay)->getCouponStartDate(),
							(*iterPay)->getCouponEndDate(), finalPeriod,stubPeriod, (int) getPayFreq() );


				(*iterPay)->setNotional(lastAmortNotional);
				(*iterPay)->setPeriodRate(periodRate);
				(*iterPay)->setAmount(dcfNot * periodRate );
					logFile << "Payment Amount outside amort : " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate()
							<< " : " << lastAmortNotional << ": " << (*iterPay)->getAmount() <<
							":"  << endl;
				}
			}
			else
			{
					(*iterPay)->setAmount(dcfNot * periodRate );
					logFile << "Payment Amount not amort : " << (*iterPay)->getCouponStartDate() << " : "
							<< (*iterPay)->getCouponEndDate() << " : " << (*iterPay)->getAmount() << endl;

			}
		  }
		}

		 return true;

}

double CapFloorTicket::calculatePV(std::string bumpTenor, double bumpSize)
{

	double pv = 0.0;
	boost::shared_ptr<IRDConnect::Curve>  curvePtr;

	if ( bumpTenor != "" && bumpSize != 0.0 )
		{
			curvePtr = CurveCache::instance().find(Util::getCurveDate(), std::string(getDiscountCurve()), bumpTenor, bumpSize) ;
		}
		else
		{
			curvePtr = CurveCache::instance().find(Util::getCurveDate(), std::string(getDiscountCurve())) ;
		}

		AdditionalPaymentsList::const_iterator iterEvent = getAdditionalPayments().begin () ;
		for ( ; iterEvent != getAdditionalPayments().end () ; ++iterEvent )
		{
			if ( (*iterEvent)->getPaymentDate() > Date::todaysDate() )
				pv += (*iterEvent)->getAmount() * curvePtr->getZcdf((*iterEvent)->getPaymentDate());

		}

		PremiumsList::const_iterator iterEventPrem = getPremiums().begin () ;

		for ( ; iterEventPrem != getPremiums().end () ; ++iterEventPrem )
		{
			if ( (*iterEventPrem)->getPaymentDate() > Date::todaysDate())
				pv += (*iterEventPrem)->getPremiumBP() * curvePtr->getZcdf((*iterEventPrem)->getPaymentDate());

		}

		PayScheduleList::const_iterator iterCap = displayPaySchedule().begin();

		for ( ; iterCap != displayPaySchedule().end() ; ++iterCap )
		{
			if ((*iterCap)->getPaymentDate() > Date::todaysDate() )
				pv +=  curvePtr->getZcdf((*iterCap)->getPaymentDate()) *  (*iterCap)->getAmount();
		}

	return pv;

}

double CapFloorTicket::calculateDV01(std::string bumpTenor, double bumpSizeUp, double bumpSizeDown)
{


	cout << "CapFloor PV - dv01 " << " : " << " : UP : " << getDiscountCurve() << calculatePV(bumpTenor, bumpSizeUp)
										<< " DOWN : " << getDiscountCurve() << calculatePV(bumpTenor, -1 * bumpSizeDown ) << endl;
	return calculatePV(bumpTenor, bumpSizeUp) - calculatePV(bumpTenor, -1 * bumpSizeDown ) ;

}

double CapFloorTicket::calculateTheta(double bumpSize)
{


	cout << "CapFloor PV Theta " << " : " <<  " : T : " << getDiscountCurve() << ":" <<  calculatePV() << endl;
	cout << "CapFloor PV Theta " << " : " <<  " : T+1 : " << getDiscountCurve() << ":" << calculatePV("Theta", bumpSize) << endl;
	return calculatePV("Theta", bumpSize) - calculatePV() ;

}

std::string CapFloorTicket::capFloorSerialize()
{

	  CMarkup xml;
	 // xml.Load(xmlFileName);
	  xml.AddElem( "TradeTicket" );
	 // xml.SetAttrib( "classtype", "CXyz" ); // not needed now as we don't have attributes
	  xml.IntoElem();

	  //std::string alternateRef = getAlternateRef().str();
	  	 xml.AddElem("ModificationReason", "Assignment");
	  	 xml.AddElem("Tenor", "2");
	  	 xml.AddElem("RiskPartyA", "NA");
	  	 xml.AddElem("BrokerAccount", "HBGCINT");
	  	 xml.AddElem("Comments", "Hello SwapTicket");
	  	 xml.AddElem("AlternateRef", getAlternateRef().getStr());
	     	 xml.AddElem("BookingType", getBookingType().getStr());
	     	 xml.AddElem("CustomerAccount", getCustomerAccount().getStr());
	     	 xml.AddElem("EarlyTermDate", getEarlyTermDate().string());
	     	 xml.AddElem("EarlyTermReason", getEarlyTermReason().getStr());
	     	 xml.AddElem("ExternalSystem", getExternalSystem().getStr());
	     	 xml.AddElem("ExternalRef", getExternalRef().getStr());
	     	 xml.AddElem("FirmAccount", getFirmAccount().getStr());
	     	 xml.AddElem("FlowStatus", getFlowStatus().getStr());
	     	 xml.AddElem("LastModifiedBy", getLastModifiedBy().getStr());
	     	 xml.AddElem("LastVerifiedBy", getLastVerifiedBy().getStr());
	     	 xml.AddElem("LegalEntity", getLegalEntity().getStr());
	     	 xml.AddElem("Location", getLocation().getStr());
	     	 xml.AddElem("MatchingStatus", getMatchingStatus().getStr());
	     	 xml.AddElem("TerminationDate", getTerminationDate().string());
	     	 xml.AddElem("ModifiedTimeStamp", getModifiedTimeStamp().getStr());
	     	 xml.AddElem("OperationsRef", getOperationsRef().getStr());
	     	 xml.AddElem("OriginalTradeRef", getOriginalTradeRef().getStr());
	     	 xml.AddElem("ProductType", getProductType().getStr());
	     	 xml.AddElem("SalesPerson", getSalesPerson().getStr());
	     	 xml.AddElem("EffectiveDate", getEffectiveDate().string());
	     	 xml.AddElem("SubType", getSubType().getStr());
	     	 xml.AddElem("TradeDate", getTradeDate().string());
	     	 xml.AddElem("Trader", getTrader().getStr());
	     	 xml.AddElem("TradeRef", getTradeRef().getStr());
	     	 xml.AddElem("TradeStatus", getTradeStatus().getStr());
	     	 xml.AddElem("TradeType", getTradeType().getStr());
	     	 xml.AddElem("VerifiedTimeStamp", getVerifiedTimeStamp().getStr());
	     	 xml.AddElem("WashAccount", getWashAccount().getStr());

	     	 xml.AddElem( "CapFloorTicket" );
	     	 xml.IntoElem();
	     	 xml.AddElem("AmortAmount", getAmortAmount());
	     	 xml.AddElem("AmortFreq", getAmortFreq());
	     	 xml.AddElem("AmortType", getAmortType().getStr());
	     	 xml.AddElem("AmortRollDay", getAmortRollDay());
	     	 xml.AddElem("AmortRollWeek", getAmortRollWeek());
	     	 xml.AddElem("AmortBusDay", getAmortBusDay()->getStr());

	          std::string amortCalendarsRec = "";
	             int amortCalSizeRec = getAmortCalendars().size ();
	             int amortCalRec = 1;

	             std::set<std::string>::const_iterator amortCalIterRec = getAmortCalendars().begin () ;

	             for (; amortCalIterRec != getAmortCalendars().end() ; ++amortCalIterRec)
	             	 {
	            	 	 if ( amortCalRec > amortCalSizeRec )
	            	 		 break;
	            	 	 if ( amortCalRec > 1 )
	            	 	 {
	            	 		 amortCalendarsRec += ",";
	            	 		 amortCalendarsRec += *amortCalIterRec;
	            	 	 }
	            	 	 else
	            	 		 amortCalendarsRec = *amortCalIterRec;

	            	 	 amortCalRec ++;
	          			}
	        xml.AddElem("AmortCalendars", amortCalendarsRec);
	        xml.AddElem("AmortStartDate", getAmortStartDate().string());
	        xml.AddElem("AmortMarching",  getAmortMarching()->getStr());
	      	xml.AddElem("AmortEndDate",  getAmortEndDate().string());
	      	xml.AddElem("PricingMethod", getPricingMethod().getStr());
	      	xml.AddElem("BackStubDate", getBackStubDate().string());
	      	xml.AddElem("BackStubManualRate", getBackStubManualRate());
	      	xml.AddElem("BuyFlag", getBuyFlag().getStr());
	      	xml.AddElem("CapFloorType", getCapFloorType().getStr());
	      	xml.AddElem("Currency", getCurrency()->getCurrencyCode());
	     	xml.AddElem("DayCount", getDayCount()->getStr());
	    	xml.AddElem("DiscountCurve", getDiscountCurve().getStr());
	    	xml.AddElem("EndDate", getEndDate().string());
	    	xml.AddElem("EndDateRollFlag", getEndDateRollFlag().getStr());
	    	xml.AddElem("FrontStubDate", getFrontStubDate().string());
	        xml.AddElem("FrontStubManualRate", getFrontStubManualRate());
	        xml.AddElem("GearFactor", getGearFactor());

	        std::string initialQuoteCalendarsRec = "";
	             int initialQuoteCalSizeRec = getInitialQuoteCalendars().size ();
	             int initialCalRec = 1;

	             std::set<std::string>::const_iterator initialCalIterRec = getInitialQuoteCalendars().begin () ;

	             	for (; initialCalIterRec != getAmortCalendars().end() ; ++initialCalIterRec)
	             	{
	             		if ( initialCalRec > initialQuoteCalSizeRec )
	             		break;
	             		if ( initialCalRec > 1 )
	             		{
	             			initialQuoteCalendarsRec += ",";
	             			initialQuoteCalendarsRec += *initialCalIterRec;
	             			}
	             			else
	             				initialQuoteCalendarsRec = *initialCalIterRec;

	             			initialCalRec ++;
	             		}
	        xml.AddElem("InitialQuoteCalendars", initialQuoteCalendarsRec);

	        xml.AddElem("InitialQuoteDate", getInitialQuoteDate().string());
	        xml.AddElem("InitialQuoteLag", getInitialQuoteLag());
	        xml.AddElem("MarketIndex", getMarketIndex().getStr());
	        xml.AddElem("Notional", getNotional());

	        xml.AddElem("PayBusDay", getPayBusDay()->getStr());

	    	std::string payCalendars = "";
	    	      			int payCalSize = getPayCalendars().size ();
	    	      			int payCal = 1;

	    	      			std::set<std::string>::const_iterator payCalIter = getPayCalendars().begin () ;

	    	      			for (; payCalIter != getPayCalendars().end() ; ++payCalIter)
	    	      			{
	    	      				if ( payCal > payCalSize )
	    	      					break;
	    	      						if ( payCal > 1 )
	    	      					{
	    	      							payCalendars += ",";
	    	      							payCalendars += *payCalIter;
	    	      					}
	    	      					else
	    	      							payCalendars = *payCalIter;

	    	    payCal ++;
	    	    }
	    	  xml.AddElem("PayCalendars", payCalendars);

	    	  xml.AddElem("PayFreq", getPayFreq());
	    	  xml.AddElem("PayMarching", getPayMarching()->getStr());
	    	  xml.AddElem("PayLag", getPayLag());
	    	  xml.AddElem("PayRollDay", getPayRollDay());
	    	  xml.AddElem("PayRollWeek", getPayRollWeek());

	    	  std::string quoteCalendars = "";
	    		 int quoteCalSize = getQuoteCalendars().size ();
	    		 int quoteCal = 1;

	    		 std::set<std::string>::const_iterator quoteCalIter = getQuoteCalendars().begin () ;

	    		 for (; quoteCalIter != getQuoteCalendars().end() ; ++quoteCalIter)
	    		 {
	    			 if ( quoteCal > quoteCalSize )
	    				 break;
	    			 if ( quoteCal > 1 )
	    			 {
	    				 quoteCalendars += ",";
	    				 quoteCalendars += *quoteCalIter;
	    			 }
	    			 else
	    				 quoteCalendars = *quoteCalIter;

	    			 quoteCal ++;
	    		 }
	    		 xml.AddElem("QuoteCalendars", quoteCalendars);

	    		   xml.AddElem("QuoteLag", getQuoteLag());
	    		   xml.AddElem("ResetAveraging", getResetAveraging().getStr());

	    		  xml.AddElem("ResetConvention", getResetConvention().getStr());
	    		  xml.AddElem("ResetFreq", getResetFreq());
	    		  xml.AddElem("ResetType", getResetType().getStr());
	    		  xml.AddElem("ScheduleCustomFlag", getScheduleCustomFlag());
	    		  xml.AddElem("Spread", getSpread());
	    		  xml.AddElem("CapStartDate", getCapStartDate().string());
	    		  xml.AddElem("StartDateRollFlag", getStartDateRollFlag().getStr());
	    		  xml.AddElem("Strike", getStrike());
	    		  xml.AddElem("CFSubType", getCFSubType().getStr());
	    		  xml.AddElem("VolId", getVolId().getStr());
	    		  xml.AddElem("PaymentConversionLag", getPaymentConversionLag());
	    		  xml.AddElem("PaymentConvention", getPaymentConvention().getStr());
	    		  xml.AddElem("PaymentConversionCurrency", getPaymentConversionCurrency()->getCurrencyCode());
	    		  xml.AddElem("PaymentConversionIndex", getPaymentConversionIndex().getStr());


            xml.OutOfElem();
	        xml.OutOfElem();
	        // you may need gointo as many times you have inner loops like pay schedulelist etc.
	        // xml.AddElem( "SwapLegFields", getFirstPayLeg()->get swapleg fields  ); this is needed check later
	      //  cout << xml.GetDoc() << endl; // check this print out every time you change some code
	        return xml.GetDoc();
}

std::string CapFloorTicket::legSerialize()
{
	CMarkup xml;

           xml.AddElem( "Schedules" );
	   	   xml.IntoElem();

	  xml.AddElem( "PayScheduleList" );
	 xml.IntoElem();


	PayScheduleList::const_iterator iterPay = displayPaySchedule().begin();

			for ( ; iterPay != displayPaySchedule().end() ; ++iterPay )
			{
					  xml.AddElem("PaySchedule");
				 	  xml.IntoElem();

				 	 xml.AddElem("CouponStartDate", (*iterPay)->getCouponStartDate().string());
				 	 xml.AddElem("Amount", String::doubleToFourDecString((*iterPay)->getAmount(),getCurrency()->getNumDecimal()));
				 	 xml.AddElem("ConvertedAmount", (*iterPay)->getConvertedAmount());
				 	 xml.AddElem("CouponEndDate", (*iterPay)->getCouponEndDate().string());
				 	 xml.AddElem("PaymentDate", (*iterPay)->getPaymentDate().string());
				 	 xml.AddElem("PeriodRate", (*iterPay)->getPeriodRate());
				 	 xml.AddElem("Notional", (*iterPay)->getNotional());
				    xml.OutOfElem();  // come out from Payment schedule

				   // logFile << "Payment Dates " << (*iterPay)->getCouponStartDate() << " : " << (*iterPay)->getCouponEndDate() << endl;
			}
		    xml.OutOfElem();

		       		    xml.AddElem( "AmortScheduleList" );
		    		   	  // xml.SetAttrib( "classtype", "CXyz" ); // not needed now as we don't have attributes
		    		   	  xml.IntoElem();


		    		   	AmortScheduleList::const_iterator iterAmort = displayAmortSchedule().begin();

		    		   			for ( ; iterAmort != displayAmortSchedule().end() ; ++iterAmort )
		    		   			{
		    		   					  xml.AddElem("AmortSchedule");
		    		   				 	  xml.IntoElem();

		    		   				 	  	 xml.AddElem("AmortNotional", (*iterAmort)->getAmortNotional());
		    		   				 	  	 xml.AddElem("StartDate", (*iterAmort)->getStartDate().string());
		    		   				 	     xml.AddElem("EndDate", (*iterAmort)->getEndDate().string());

		    		   				 	  xml.OutOfElem();  // come out from amort schedule

		    		   			}


		    		   		    xml.OutOfElem();

		    		   		 xml.AddElem( "ResetScheduleList" );
		    		   		 	  // xml.SetAttrib( "classtype", "CXyz" ); // not needed now as we don't have attributes
		    		   		 	  xml.IntoElem();


		    		   		 	ResetScheduleList::const_iterator iterReset = displayResetSchedule().begin();

		    		   		 			for ( ; iterReset != displayResetSchedule().end() ; ++iterReset )
		    		   		 			{
		    		   		 					  xml.AddElem("ResetSchedule");
		    		   		 				 	  xml.IntoElem();

		    		   		 				 	 xml.AddElem("QuoteDate", (*iterReset)->getQuoteDate().string());
		    		   		 				 	 xml.AddElem("Rate", (*iterReset)->getRate());
		    		   		 				 	 xml.AddElem("RateIndexType", (*iterReset)->getRateIndexType().getStr());
		    		   		 				 	// xml.AddElem("RateType", (*iterReset)->getRateType().getStr());
		    		   		 				 	 xml.AddElem("ResetStartDate", (*iterReset)->getResetStartDate().string());
		    		   		 				 	 xml.AddElem("ResetEndDate", (*iterReset)->getResetEndDate().string());
		    		   		 				    xml.OutOfElem();  // come out from Reset schedule
		    		   		 			}

		    		   	xml.OutOfElem(); //reset end
		    		   	xml.OutOfElem(); //Schedules end

return xml.GetDoc();
}


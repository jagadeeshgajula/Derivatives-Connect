/*
 * swapOption.cpp
 *
 *  Created on: 17-Aug-2010
 *      Author: vishist
 */

#include <iostream>
#include "swapTicket.h"
#include "tradeTicket.h"
#include "swapLeg.h"

#include "swapOption.h"
#include "premiums.h"
#include "irdXML.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


SwapOption::SwapOption(){
// do nothing;

}

SwapOption::SwapOption(

String 		buyFlag, // Yes or No
String		exerciseFlag, // Yes or No
String 		exerciseType, // CASH OR PHYSICAL
Date 		expiryDate,
String 		optionStyle, // european or american or bermudian
String 		optionType, // option to enter or option to cancel
String 		position, // PayFixed or RecFixed
String		pricingMethod, // closed Form, Tree, Mc 3000:10000:40000 etc
double		strike,
Date 		swapEndDate,
int 		swapLag,
const BusDayConv * swapLagBusDay,
String 		swapRef, // appear only if exercised and EXERCISE type is PHYSICAL
Date 		swapStartDate,
String		volId,
SwapTicket * 	swapTicket )

{
_buyFlag			=	buyFlag;
_exerciseFlag 		= 	exerciseFlag;
_exerciseType		=	exerciseType;
_expiryDate			=	expiryDate;
_optionStyle		=	optionStyle;
_optionType			=	optionType;
_position			=	position;
_pricingMethod		=	pricingMethod;
_strike				=	strike;
_swapEndDate		=	swapEndDate;
_swapLag			=	swapLag;
_swapLagBusDay		= 	swapLagBusDay;
_swapRef			=	swapRef;
_swapStartDate		=	swapStartDate;
_volId				= 	volId;
_swapTicket			= 	swapTicket;
}

SwapOption::~SwapOption()
{
	// do nothing
}


bool SwapOption::genAllCashFlows()
{

	if ( ! getSwapTicket()->genAllCashFlows() )
	{
		cout << "sorry failed to generate cashflows " << endl;
		return false;
	}

	// let us print premiums here

		PremiumsList::const_iterator iterEvent = getSwapTicket()->getPremiums().begin () ;

			int noOfEvents = getSwapTicket()->getPremiums().size();
			cout << "No of Elements in fee :" << noOfEvents << endl;
			cout << "Let us PRINT PREMIUMS HERE " << endl;


			for ( ; iterEvent != getSwapTicket()->getPremiums().end () ; ++iterEvent )
			{

				cout << (*iterEvent)->getPremiumType()
						<< ":" << (*iterEvent)->getAmount()  << ":"
						<<  (*iterEvent)->getPaymentDate() << endl;
			}


			AdditionalPaymentsList::const_iterator iterEventFee = getSwapTicket()->getAdditionalPayments().begin () ;


					cout << "Let us PRINT FEE HERE " << endl;


					for ( ; iterEventFee != getSwapTicket()->getAdditionalPayments().end () ; ++iterEventFee )
					{

						cout << (*iterEventFee)->getPaymentType()
								<< ":" << (*iterEventFee)->getFirmAccount() << ":"
								<< (*iterEventFee)->getCustomerAccount() << ":"
								<<  (*iterEventFee)->getPaymentDate() << ":" <<
								(*iterEventFee)->getAmount() << ":" << endl;
					}

return true;

}

/*
//TradeTicket tt = new TradeTicket();
std::string SwapOption::serialize()
{
	  CMarkup xml;

	  xml.AddElem( "TradeTicket" );

	  xml.IntoElem();

	  //std::string alternateRef = getAlternateRef().str();
	  	 xml.AddElem("ModificationReason", "Assignment");
	  	 xml.AddElem("Tenor", "2");
	  	 xml.AddElem("RiskPartyA", "NA");
	  	 xml.AddElem("BrokerAccount", "HBGCINT");
	  	 xml.AddElem("Comments", "Hello SwapTicket");
	  	 xml.AddElem("AlternateRef", getSwapTicket()->getAlternateRef().getStr());
	     	 xml.AddElem("BookingType", getSwapTicket()->getBookingType().getStr());
	     	 xml.AddElem("CustomerAccount", getSwapTicket()->getCustomerAccount().getStr());
	     	 xml.AddElem("EarlyTermDate", getSwapTicket()->getEarlyTermDate().string());
	     	 xml.AddElem("EarlyTermReason", getSwapTicket()->getEarlyTermReason().getStr());
	     	 xml.AddElem("ExternalSystem", getSwapTicket()->getExternalSystem().getStr());
	     	 xml.AddElem("ExternalRef", getSwapTicket()->getExternalRef().getStr());
	     	 xml.AddElem("FirmAccount", getSwapTicket()->getFirmAccount().getStr());
	     	 xml.AddElem("FlowStatus", getSwapTicket()->getFlowStatus().getStr());
	     	 xml.AddElem("LastModifiedBy", getSwapTicket()->getLastModifiedBy().getStr());
	     	 xml.AddElem("LastVerifiedBy", getSwapTicket()->getLastVerifiedBy().getStr());
	     	 xml.AddElem("LegalEntity", getSwapTicket()->getLegalEntity().getStr());
	     	 xml.AddElem("Location", getSwapTicket()->getLocation().getStr());
	     	 xml.AddElem("MatchingStatus", getSwapTicket()->getMatchingStatus().getStr());
	     	 xml.AddElem("MaturityDate", getSwapTicket()->getMaturityDate().string());
	     	 xml.AddElem("ModifiedTimeStamp", getSwapTicket()->getModifiedTimeStamp().getStr());
	     	 xml.AddElem("OperationsRef", getSwapTicket()->getOperationsRef().getStr());
	     	 xml.AddElem("OriginalTradeRef", getSwapTicket()->getOriginalTradeRef().getStr());
	     	 xml.AddElem("ProductType", getSwapTicket()->getProductType().getStr());
	     	 xml.AddElem("SalesPerson", getSwapTicket()->getSalesPerson().getStr());
	     	 xml.AddElem("StartDate", getSwapTicket()->getStartDate().string());
	     	 xml.AddElem("SubType", getSwapTicket()->getSubType().getStr());
	     	 xml.AddElem("TradeDate", getSwapTicket()->getTradeDate().string());
	     	 xml.AddElem("Trader", getSwapTicket()->getTrader().getStr());
	     	 xml.AddElem("TradeRef", getSwapTicket()->getTradeRef().getStr());
	     	 xml.AddElem("TradeStatus", getSwapTicket()->getTradeStatus().getStr());
	     	 xml.AddElem("TradeType", getSwapTicket()->getTradeType().getStr());
	     	 xml.AddElem("VerifiedTimeStamp", getSwapTicket()->getVerifiedTimeStamp().getStr());
	     	 xml.AddElem("WashAccount", getSwapTicket()->getWashAccount().getStr());
	     	 xml.AddElem("Option");
	     	 xml.IntoElem();

	     	 xml.AddElem("BuyFlag", getBuyFlag().getStr());
	     	 xml.AddElem("ExerciseFlag", getExerciseFlag().getStr());
	     	 xml.AddElem("ExpiryDate", getExpiryDate().string());
	     	 xml.AddElem("ExerciseType", getExerciseType().getStr());
	     	 xml.AddElem("OptionStyle", getOptionStyle().getStr());
	     	 xml.AddElem("OptionType", getOptionType().getStr());
	     	 xml.AddElem("SWTPosition", getPosition().getStr());
	     	 xml.AddElem("PricingMethod", getPricingMethod().getStr());
	     	 xml.AddElem("Strike", getStrike());
	     	 xml.AddElem("SwapEndDate", getSwapEndDate().string());
	     	 xml.AddElem("SwapLag", getSwapLag());
	     	 xml.AddElem("SwapLagBusDay", getSwapLagBusDay()->getStr());
	     	 xml.AddElem("SwapRef", getSwapRef().getStr());
	     	 xml.AddElem("SwapStartDate", getSwapStartDate().string());
	     	 xml.AddElem("VolId", getVolId().getStr());

	     	 xml.OutOfElem();
	     	 xml.AddElem( "SwapLegList");
	     	 xml.IntoElem();
	     	 xml.AddElem( "SwapLeg");
	     	 xml.IntoElem();
			xml.AddElem("AccrualBusDay", getSwapTicket()->getFirstPayLeg()->getAccrualBusDay()->getStr());
			std::string accrualCalendars = "";
			int accrualCalSize = getSwapTicket()->getFirstPayLeg()->getAccrualCalendars().size ();
			int accrualCal = 1;
			std::set<std::string>::const_iterator accrualCalIter = getSwapTicket()->getFirstPayLeg()->getAccrualCalendars().begin () ;

			for (; accrualCalIter != getSwapTicket()->getFirstPayLeg()->getAccrualCalendars().end() ; ++accrualCalIter)
			{
				if ( accrualCal > accrualCalSize )
					break;

				if ( accrualCal > 1 )
				{
					accrualCalendars += ",";
					accrualCalendars += *accrualCalIter;
				}
				else
					accrualCalendars = *accrualCalIter;

				accrualCal ++;
			}
			xml.AddElem("AccrualCalendars", accrualCalendars);
			xml.AddElem("AccrualFreq", getSwapTicket()->getFirstPayLeg()->getAccrualFreq());
			xml.AddElem("AccrualMarching", getSwapTicket()->getFirstPayLeg()->getAccrualMarching()->getStr());
			xml.AddElem("AccrualRollDay", getSwapTicket()->getFirstPayLeg()->getAccrualRollDay());
			xml.AddElem("AccrualRollWeek", getSwapTicket()->getFirstPayLeg()->getAccrualRollWeek());
			xml.AddElem("AmortRollDay", getSwapTicket()->getFirstPayLeg()->getAmortRollDay());
			xml.AddElem("AmortRollWeek", getSwapTicket()->getFirstPayLeg()->getAmortRollWeek());
			xml.AddElem("AmortAmount", getSwapTicket()->getFirstPayLeg()->getAmortAmount());
			xml.AddElem("AmortBusDay", getSwapTicket()->getFirstPayLeg()->getAmortBusDay()->getStr());
		    int amortCalSize = getSwapTicket()->getFirstPayLeg()->getAmortCalendars().size ();
			std::string amortCalendars = "";
			int amortCal = 1;

			std::set<std::string>::const_iterator amortCalIter = getSwapTicket()->getFirstPayLeg()->getAmortCalendars().begin () ;

			for (; amortCalIter != getSwapTicket()->getFirstPayLeg()->getAmortCalendars().end() ; ++amortCalIter)
			{
				if ( amortCal > amortCalSize )
					break;

				if ( amortCal > 1 )
				{
					amortCalendars += ",";
					amortCalendars += *amortCalIter;
						}
					else
						amortCalendars = *amortCalIter;

					amortCal ++;
				}
			xml.AddElem("AmortCalendars", amortCalendars);
			// xml.AddElem("AmortCalendars", getFirstPayLeg()->getAmortCalendars().getStr());
			xml.AddElem("AmortEndDate", getSwapTicket()->getFirstPayLeg()->getAmortEndDate().string());
			xml.AddElem("AmortFreq", getSwapTicket()->getFirstPayLeg()->getAmortFreq());
			xml.AddElem("AmortMarching", getSwapTicket()->getFirstPayLeg()->getAmortMarching()->getStr());
			xml.AddElem("AmortStartDate", getSwapTicket()->getFirstPayLeg()->getAmortStartDate().string());
			xml.AddElem("AmortType", getSwapTicket()->getFirstPayLeg()->getAmortType().getStr());
			xml.AddElem("AveragingMethod", getSwapTicket()->getFirstPayLeg()->getAveragingMethod().getStr());
			xml.AddElem("BackStubDate", getSwapTicket()->getFirstPayLeg()->getBackStubDate().string());
			xml.AddElem("BackStubManualRate", getSwapTicket()->getFirstPayLeg()->getBackStubManualRate());
			xml.AddElem("CompFreq", getSwapTicket()->getFirstPayLeg()->getCompFreq());
			xml.AddElem("CompoundingConv", getSwapTicket()->getFirstPayLeg()->getCompoundingConv().getStr());

		//	xml.AddElem("Currency", getFirstPayLeg()->getCurrency()->getCurrencyCode());
			xml.AddElem("Currency", getSwapTicket()->getFirstPayLeg()->getCurrency()->getCurrencyCode());
			//xml.AddElem("Currency", getFirstPayLeg()->getCurrency().getStr());
			xml.AddElem("DayCount", getSwapTicket()->getFirstPayLeg()->getDayCount()->getStr());
			xml.AddElem("DiscountCurve", getSwapTicket()->getFirstPayLeg()->getDiscountCurve().getStr());
			xml.AddElem("EndDate", getSwapTicket()->getFirstPayLeg()->getEndDate().string());
			xml.AddElem("EndDateRollFlag", getSwapTicket()->getFirstPayLeg()->getEndDateRollFlag().getStr());
			xml.AddElem("EndOfMonthIndicator", getSwapTicket()->getFirstPayLeg()->getEndOfMonthIndicator().getStr());
			xml.AddElem("FixedQuote", getSwapTicket()->getFirstPayLeg()->getFixedQuote());
			xml.AddElem("FrontStubDate", getSwapTicket()->getFirstPayLeg()->getFrontStubDate().string());
			xml.AddElem("FrontStubManualRate", getSwapTicket()->getFirstPayLeg()->getFrontStubManualRate());
			xml.AddElem("GearFactor", getSwapTicket()->getFirstPayLeg()->getGearFactor());

			std::string initialQuoteCalendars = "";
			int initialCalSize = getSwapTicket()->getFirstPayLeg()->getInitialQuoteCalendars().size ();
			int initialCal = 1;

			std::set<std::string>::const_iterator initialCalIter = getSwapTicket()->getFirstPayLeg()->getInitialQuoteCalendars().begin () ;

			for (; initialCalIter != getSwapTicket()->getFirstPayLeg()->getInitialQuoteCalendars().end() ; ++initialCalIter)
			{
				if ( initialCal > initialCalSize )
					break;
						if ( initialCal > 1 )
					{
							initialQuoteCalendars += ",";
							initialQuoteCalendars += *initialCalIter;
					}
					else
							initialQuoteCalendars = *initialCalIter;

					initialCal ++;
			}
			xml.AddElem("InitialQuoteCalendars", initialQuoteCalendars);
			xml.AddElem("InitialQuoteDate", getSwapTicket()->getFirstPayLeg()->getInitialQuoteDate().string());
			xml.AddElem("InitialQuoteLag", getSwapTicket()->getFirstPayLeg()->getInitialQuoteLag());
			xml.AddElem("LegNo", getSwapTicket()->getFirstPayLeg()->getLegNo());
			xml.AddElem("LegType", getSwapTicket()->getFirstPayLeg()->getLegType().getStr());
			xml.AddElem("MarketIndex", getSwapTicket()->getFirstPayLeg()->getMarketIndex().getStr());
			xml.AddElem("Notional", getSwapTicket()->getFirstPayLeg()->getNotional());
			xml.AddElem("NotionalExchange", getSwapTicket()->getFirstPayLeg()->getNotionalExchange().getStr() );
          	xml.AddElem("PayBusDay", getSwapTicket()->getFirstPayLeg()->getPayBusDay()->getStr());
            std::string payCalendars = "";
            int payCalSize = getSwapTicket()->getFirstPayLeg()->getPayCalendars().size ();
            int payCal = 1;

            std::set<std::string>::const_iterator payCalIter = getSwapTicket()->getFirstPayLeg()->getPayCalendars().begin () ;

            for (; payCalIter != getSwapTicket()->getFirstPayLeg()->getPayCalendars().end() ; ++payCalIter)
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

            // xml.AddElem("PayCalendars", getFirstPayLeg()->getPayCalendars().getStr());

          	xml.AddElem("PayFreq", getSwapTicket()->getFirstPayLeg()->getPayFreq());
          	xml.AddElem("PayLag", getSwapTicket()->getFirstPayLeg()->getPayLag());
          	xml.AddElem("PayMarching", getSwapTicket()->getFirstPayLeg()->getPayMarching()->getStr());
          	xml.AddElem("PaymentConvention", getSwapTicket()->getFirstPayLeg()->getPaymentConvention().getStr());
         	xml.AddElem("PaymentConversionCurrency", getSwapTicket()->getFirstPayLeg()->getPaymentConversionCurrency()->getCurrencyCode());
          	//xml.AddElem("PaymentConversionCurrency", getFirstPayLeg()->getPaymentConversionCurrency());
          	xml.AddElem("PaymentConversionIndex", getSwapTicket()->getFirstPayLeg()->getPaymentConversionIndex().getStr());
          	xml.AddElem("PaymentConversionLag", getSwapTicket()->getFirstPayLeg()->getPaymentConversionLag());
          	xml.AddElem("PayRollDay", getSwapTicket()->getFirstPayLeg()->getPayRollDay());
          	xml.AddElem("PayRollWeek", getSwapTicket()->getFirstPayLeg()->getPayRollWeek());
          	xml.AddElem("Position", getSwapTicket()->getFirstPayLeg()->getPosition().getStr());

          	std::string quoteCalendars = "";
          	int quotecalSize = getSwapTicket()->getFirstPayLeg()->getQuoteCalendars().size ();
          	int quotecal = 1;
          	std::set<std::string>::const_iterator quotecalIter = getSwapTicket()->getFirstPayLeg()->getQuoteCalendars().begin () ;

          	for (; quotecalIter != getSwapTicket()->getFirstPayLeg()->getQuoteCalendars().end() ; ++quotecalIter)
          	{
          		if ( quotecal > quotecalSize )
          			break;
          		if ( quotecal > 1 )
          		{
          			quoteCalendars += ",";
          			quoteCalendars += *quotecalIter;
          		}
          		else
          			quoteCalendars = *quotecalIter;

          		quotecal ++;
          	}
		   xml.AddElem("QuoteCalendars", quoteCalendars);
		   //xml.AddElem("QuoteCalendars", getFirstPayLeg()->getQuoteCalendars().getStr());
		   xml.AddElem("QuoteLag", getSwapTicket()->getFirstPayLeg()->getQuoteLag());
		   xml.AddElem("RateCutOff", getSwapTicket()->getFirstPayLeg()->getRateCutOff());
		   xml.AddElem("ResetAveraging", getSwapTicket()->getFirstPayLeg()->getResetAveraging().getStr());
		   xml.AddElem("ResetBusDay", getSwapTicket()->getFirstPayLeg()->getResetBusDay()->getStr());
		   // xml.AddElem("ResetBusDay", getFirstPayLeg()->getResetBusDay().getStr());
		   xml.AddElem("ResetConvention", getSwapTicket()->getFirstPayLeg()->getResetConvention().getStr());
		   xml.AddElem("ResetFreq", getSwapTicket()->getFirstPayLeg()->getResetFreq());
		   xml.AddElem("ResetMarching", getSwapTicket()->getFirstPayLeg()->getResetMarching()->getStr());
		   xml.AddElem("ResetRollDay", getSwapTicket()->getFirstPayLeg()->getResetRollDay());
		   xml.AddElem("ResetRollWeek", getSwapTicket()->getFirstPayLeg()->getResetRollWeek());
		   xml.AddElem("ResetType", getSwapTicket()->getFirstPayLeg()->getResetType().getStr());
		   xml.AddElem("ScheduleCustomFlag", getSwapTicket()->getFirstPayLeg()->getScheduleCustomFlag());
		   xml.AddElem("Spread", getSwapTicket()->getFirstPayLeg()->getSpread());
		   xml.AddElem("StartDate", getSwapTicket()->getFirstPayLeg()->getStartDate().string());
		   xml.AddElem("StartDateRollFlag", getSwapTicket()->getFirstPayLeg()->getStartDateRollFlag().getStr());
		   xml.OutOfElem();

		  xml.AddElem( "SwapLeg");
		  xml.IntoElem();

		   xml.AddElem("AccrualBusDay", getSwapTicket()->getFirstReceiveLeg()->getAccrualBusDay()->getStr());

		   std::string accrualCalendarsRec = "";
		   int accrualCalSizeRec = getSwapTicket()->getFirstReceiveLeg()->getAccrualCalendars().size ();
		   int accrualCalRec = 1;

		   std::set<std::string>::const_iterator accrualCalIterRec = getSwapTicket()->getFirstReceiveLeg()->getAccrualCalendars().begin () ;

		   for (; accrualCalIterRec != getSwapTicket()->getFirstReceiveLeg()->getAccrualCalendars().end() ; ++accrualCalIterRec)
		   {
			   if ( accrualCalRec > accrualCalSizeRec )
				   break;
			   if ( accrualCalRec > 1 )
			   {
				   accrualCalendarsRec += ",";
				   accrualCalendarsRec += *accrualCalIterRec;
			   }
			   else
				   accrualCalendarsRec = *accrualCalIterRec;

			   accrualCalRec ++;
		   }
		   	xml.AddElem("AccrualCalendars", accrualCalendarsRec);

		   	xml.AddElem("AccrualFreq", getSwapTicket()->getFirstReceiveLeg()->getAccrualFreq());
     		xml.AddElem("AccrualMarching", getSwapTicket()->getFirstReceiveLeg()->getAccrualMarching()->getStr());
        	xml.AddElem("AccrualRollDay", getSwapTicket()->getFirstReceiveLeg()->getAccrualRollDay());
     		xml.AddElem("AccrualRollWeek", getSwapTicket()->getFirstReceiveLeg()->getAccrualRollWeek());
     		xml.AddElem("AmortRollDay", getSwapTicket()->getFirstReceiveLeg()->getAmortRollDay());
     		xml.AddElem("AmortRollWeek", getSwapTicket()->getFirstReceiveLeg()->getAmortRollWeek());
     		xml.AddElem("AmortAmount", getSwapTicket()->getFirstReceiveLeg()->getAmortAmount());
     		xml.AddElem("AmortBusDay", getSwapTicket()->getFirstReceiveLeg()->getAmortBusDay()->getStr());
     		//xml.AddElem("AmortBusDay", getFirstReceiveLeg()->getAmortBusDay().getStr());


     		std::string amortCalendarsRec = "";
     		int amortCalSizeRec = getSwapTicket()->getFirstReceiveLeg()->getAmortCalendars().size ();
     		int amortCalRec = 1;

     		std::set<std::string>::const_iterator amortCalIterRec = getSwapTicket()->getFirstReceiveLeg()->getAmortCalendars().begin () ;

     		for (; amortCalIterRec != getSwapTicket()->getFirstReceiveLeg()->getAmortCalendars().end() ; ++amortCalIterRec)
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
     		// xml.AddElem("AmortCalendars", getFirstReceiveLeg()->getAmortCalendars().getStr());
     		xml.AddElem("AmortEndDate", getSwapTicket()->getFirstReceiveLeg()->getAmortEndDate().string());
     		xml.AddElem("AmortFreq", getSwapTicket()->getFirstReceiveLeg()->getAmortFreq());
     		xml.AddElem("AmortMarching", getSwapTicket()->getFirstReceiveLeg()->getAmortMarching()->getStr());
     		xml.AddElem("AmortStartDate", getSwapTicket()->getFirstReceiveLeg()->getAmortStartDate().string());
     		xml.AddElem("AmortType", getSwapTicket()->getFirstReceiveLeg()->getAmortType().getStr());
     		xml.AddElem("AveragingMethod", getSwapTicket()->getFirstReceiveLeg()->getAveragingMethod().getStr());
     		xml.AddElem("BackStubDate", getSwapTicket()->getFirstReceiveLeg()->getBackStubDate().string());
     		xml.AddElem("BackStubManualRate", getSwapTicket()->getFirstReceiveLeg()->getBackStubManualRate());
     		xml.AddElem("CompFreq", getSwapTicket()->getFirstReceiveLeg()->getCompFreq());
     		xml.AddElem("CompoundingConv", getSwapTicket()->getFirstReceiveLeg()->getCompoundingConv().getStr());
     		xml.AddElem("Currency", getSwapTicket()->getFirstReceiveLeg()->getCurrency()->getCurrencyCode());
     		//xml.AddElem("Currency", getFirstReceiveLeg()->getCurrency().getStr());
     		xml.AddElem("DayCount", getSwapTicket()->getFirstReceiveLeg()->getDayCount()->getStr());
     		xml.AddElem("DiscountCurve", getSwapTicket()->getFirstReceiveLeg()->getDiscountCurve().getStr());
     		xml.AddElem("EndDate", getSwapTicket()->getFirstReceiveLeg()->getEndDate().string());
     		xml.AddElem("EndDateRollFlag", getSwapTicket()->getFirstReceiveLeg()->getEndDateRollFlag().getStr());
     		xml.AddElem("EndOfMonthIndicator", getSwapTicket()->getFirstReceiveLeg()->getEndOfMonthIndicator().getStr());
     		xml.AddElem("FixedQuote", getSwapTicket()->getFirstReceiveLeg()->getFixedQuote());
     		xml.AddElem("FrontStubDate", getSwapTicket()->getFirstReceiveLeg()->getFrontStubDate().string());
     		xml.AddElem("FrontStubManualRate", getSwapTicket()->getFirstReceiveLeg()->getFrontStubManualRate());
     		xml.AddElem("GearFactor", getSwapTicket()->getFirstReceiveLeg()->getGearFactor());

     		std::string initialQuoteCalendarsRec = "";
     		int initialQuoteCalSizeRec = getSwapTicket()->getFirstReceiveLeg()->getInitialQuoteCalendars().size ();
     		int initialCalRec = 1;

     		std::set<std::string>::const_iterator initialCalIterRec = getSwapTicket()->getFirstReceiveLeg()->getInitialQuoteCalendars().begin () ;

     		for (; initialCalIterRec != getSwapTicket()->getFirstReceiveLeg()->getAmortCalendars().end() ; ++initialCalIterRec)
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

     	    xml.AddElem("InitialQuoteDate", getSwapTicket()->getFirstReceiveLeg()->getInitialQuoteDate().string());
     	    xml.AddElem("InitialQuoteLag", getSwapTicket()->getFirstReceiveLeg()->getInitialQuoteLag());
     	    xml.AddElem("LegNo", getSwapTicket()->getFirstReceiveLeg()->getLegNo());
     	    xml.AddElem("LegType", getSwapTicket()->getFirstReceiveLeg()->getLegType().getStr());
     	    xml.AddElem("MarketIndex", getSwapTicket()->getFirstReceiveLeg()->getMarketIndex().getStr());
     	    xml.AddElem("Notional", getSwapTicket()->getFirstReceiveLeg()->getNotional());
     	    xml.AddElem("NotionalExchange", getSwapTicket()->getFirstReceiveLeg()->getNotionalExchange().getStr() );
     	    xml.AddElem("PayBusDay", getSwapTicket()->getFirstReceiveLeg()->getPayBusDay()->getStr());

     	    std::string payCalendarsRec = "";
     	    int payCalSizeRec = getSwapTicket()->getFirstReceiveLeg()->getPayCalendars().size ();
     	    int payCalRec = 1;

     	    std::set<std::string>::const_iterator payCalIterRec = getSwapTicket()->getFirstReceiveLeg()->getPayCalendars().begin () ;

     	    for (; payCalIterRec != getSwapTicket()->getFirstReceiveLeg()->getPayCalendars().end() ; ++payCalIterRec)
     	    {
     	    	if ( payCalRec > payCalSizeRec )
     	    		break;
     	    			if ( payCalRec > 1 )
     	    				{
     	    					payCalendarsRec += ",";
     	    					payCalendarsRec += *payCalIterRec;
     	    				}
     	    		else
     	    				payCalendarsRec = *payCalIterRec;

     	    		payCalRec ++;
     	    }
     	    xml.AddElem("PayCalendars", payCalendarsRec);

     	    // xml.AddElem("PayCalendars", getFirstReceiveLeg()->getPayCalendars().getStr());
     	    xml.AddElem("PayFreq", getSwapTicket()->getFirstReceiveLeg()->getPayFreq());
     	    xml.AddElem("PayLag", getSwapTicket()->getFirstReceiveLeg()->getPayLag());
     	    xml.AddElem("PayMarching", getSwapTicket()->getFirstReceiveLeg()->getPayMarching()->getStr());
     	    xml.AddElem("PaymentConvention", getSwapTicket()->getFirstReceiveLeg()->getPaymentConvention().getStr());
     	    xml.AddElem("PaymentConversionCurrency", getSwapTicket()->getFirstReceiveLeg()->getPaymentConversionCurrency()->getCurrencyCode());
     	    // xml.AddElem("PaymentConversionCurrency", getFirstReceiveLeg()->getPaymentConversionCurrency()->getStr());
     	    xml.AddElem("PaymentConversionIndex", getSwapTicket()->getFirstReceiveLeg()->getPaymentConversionIndex().getStr());
     	    xml.AddElem("PaymentConversionLag", getSwapTicket()->getFirstReceiveLeg()->getPaymentConversionLag());
     	    xml.AddElem("PayRollDay", getSwapTicket()->getFirstReceiveLeg()->getPayRollDay());
     	    xml.AddElem("PayRollWeek", getSwapTicket()->getFirstReceiveLeg()->getPayRollWeek());
     	    xml.AddElem("Position", getSwapTicket()->getFirstReceiveLeg()->getPosition().getStr());

     	    std::string quoteCalendarsRec = "";
     	    int quoteCalSizeRec = getSwapTicket()->getFirstReceiveLeg()->getQuoteCalendars().size ();
     	    int quoteCalRec = 1;
     	    std::set<std::string>::const_iterator quoteCalIterRec = getSwapTicket()->getFirstReceiveLeg()->getQuoteCalendars().begin () ;

     	    for (; quoteCalIterRec != getSwapTicket()->getFirstReceiveLeg()->getQuoteCalendars().end() ; ++quoteCalIterRec)
     	    {
     	    	if ( quoteCalRec > quoteCalSizeRec )
     	    		break;
     	    	if ( quoteCalRec > 1 )
     	    	{
     	    		quoteCalendarsRec += ",";
     	    		quoteCalendarsRec += *quoteCalIterRec;
     	    	}
     	    	else
     	    		quoteCalendarsRec = *quoteCalIterRec;

     	    	quoteCalRec ++;
     	    }
     	    xml.AddElem("QuoteCalendars", quoteCalendarsRec);
     	    // xml.AddElem("QuoteCalendars", getFirstReceiveLeg()->getQuoteCalendars().getStr());
     	    xml.AddElem("QuoteLag", getSwapTicket()->getFirstReceiveLeg()->getQuoteLag());
     	    xml.AddElem("RateCutOff", getSwapTicket()->getFirstReceiveLeg()->getRateCutOff());
     	    xml.AddElem("ResetAveraging", getSwapTicket()->getFirstReceiveLeg()->getResetAveraging().getStr());
     	    xml.AddElem("ResetBusDay", getSwapTicket()->getFirstReceiveLeg()->getResetBusDay()->getStr());
     	    // xml.AddElem("ResetBusDay", getFirstReceiveLeg()->getResetBusDay().getStr());
     	    xml.AddElem("ResetConvention", getSwapTicket()->getFirstReceiveLeg()->getResetConvention().getStr());
     	    xml.AddElem("ResetFreq", getSwapTicket()->getFirstReceiveLeg()->getResetFreq());
     	    xml.AddElem("ResetMarching", getSwapTicket()->getFirstReceiveLeg()->getResetMarching()->getStr());
     	    xml.AddElem("ResetRollDay", getSwapTicket()->getFirstReceiveLeg()->getResetRollDay());
     	    xml.AddElem("ResetRollWeek", getSwapTicket()->getFirstReceiveLeg()->getResetRollWeek());
     	    xml.AddElem("ResetType", getSwapTicket()->getFirstReceiveLeg()->getResetType().getStr());
     	    xml.AddElem("ScheduleCustomFlag", getSwapTicket()->getFirstReceiveLeg()->getScheduleCustomFlag());
     	    xml.AddElem("Spread", getSwapTicket()->getFirstReceiveLeg()->getSpread());
     	    xml.AddElem("StartDate", getSwapTicket()->getFirstReceiveLeg()->getStartDate().string());
     	    xml.AddElem("StartDateRollFlag", getSwapTicket()->getFirstReceiveLeg()->getStartDateRollFlag().getStr());
     	    xml.OutOfElem();
	        xml.OutOfElem();
	        xml.OutOfElem();
	        // you may need gointo as many times you have inner loops like pay schedulelist etc.
	        // xml.AddElem( "SwapLegFields", getFirstPayLeg()->get swapleg fields  ); this is needed check later
	      //  cout << xml.GetDoc() << endl; // check this print out every time you change some code
	        return xml.GetDoc();
}
*/
}

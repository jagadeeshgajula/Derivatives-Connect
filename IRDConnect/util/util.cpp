/*
 * util.cpp
 *
 *  Created on: 01-Oct-2010
 *      Author: vishist
 */
#include "tradeTicket.h"
#include <iostream>
#include "irdString.h"
#include "util.h"
#include "swapLeg.h"
#include "swapTicket.h"
#include "swapOption.h"
#include "irdXML.h"
#include "currency.h"
#include "moneyMkt.h"
#include "calendarUtil.h"
#include "premiums.h"
#include "fraTicket.h"


using namespace std;
using namespace IRDConnect;
namespace IRDConnect {

Date Util::CURVE_DATE = Date(1,1,1901);
Date Util::VALUATION_DATE = Date(1,1,1901) ;

//static SwapTicketList _swapTicketList;

int Util::genSeqNo( String seqType)

{

if ( seqType == "DEALID")

{
//do nothing
}
 return 10;

}

Period Util::convPeriod(String period)
{

	if ( period == "1D")
	{
	              return Period(1,Days);
	}
	else if ( period == "1W")
	{
	               return Period(1,Weeks);
	}
	else if ( period == "1M")
	{
		return Period(1,Months);
	}
	else if ( period == "2M")
	{
		return     Period(2,Months);
	}
	else if ( period == "3M")
	{
	    // logFile << "It came here " << endl;
	    return  Period(3,Months);
	}
	else if ( period == "4M")
	{
		return	 Period(4,Months);
	}
	else if ( period == "5M")
	{
		return	 Period(5,Months);
	}
	else if ( period == "6M")
	{
		return	 Period(6,Months);
	}
	else if ( period == "7M")
	{
		return	 	 Period(7,Months);
	}
	else if ( period == "8M")
	{
		return  	 Period(8,Months);
	}
	else if ( period == "9M")
	{
		return  	 Period(9,Months);
	}
	else if ( period == "10M")
	{
		return  	 Period(10,Months);
	}
	else if ( period == "11M")
	{
		return    	 Period(11,Months);
	}
	else if ( period == "12M")
	{
		return      	 Period(12,Months);
	}
	else if ( period == "15M")
	{
		return      	 Period(15,Months);
	}
	else if ( period == "18M")
	{
		return      	 Period(18,Months);
	}
	else if ( period == "21M")
	{
		return      	 Period(21,Months);
	}
		else if ( period == "2W")
	{
		return Period(2,Weeks);
	}
	else if ( period == "1Y")
	{
		return  	 Period(1,Years);
	}
	else if ( period == "2Y")
	{
		return      	 Period(2,Years);
	}

	return Period(0,Days);
}
Frequency Util::convFrequency( int i )
{
	// logFile << "Frequency passed is : " << i << endl;

	if ( i == -1 )
		return Frequency(NoFrequency);
	else if ( i == 0 )
		return Frequency(Once);
	if ( i == 1 )
		return Frequency(Annual);
	else if ( i == 2 )
		return Frequency(Semiannual);
	else if ( i == 3 )
		return Frequency(EveryFourthMonth);
	else if ( i == 4 )
			return Frequency(Quarterly);
	else if ( i == 6 )
				return Frequency(Bimonthly);
	else if ( i == 12 )
				return Frequency(Monthly);
	else if ( i == 26 )
				return Frequency(Biweekly);
	else if ( i == 52 )
				return Frequency(Weekly);
	else if ( i == 365 )
				return Frequency(Daily);


	return Frequency(NoFrequency);
}


DayOfWeek Util::convDayOfWeek( int j )
{
	//// logFile << "Frequency passed is : " << i << endl;
   if (j == 0)
	   return  DayOfWeek(NULL_DOW);

	if ( j == 1 )
		return DayOfWeek(SUN);
	else if ( j == 2 )
		return DayOfWeek(MON);
	if ( j == 3 )
		return DayOfWeek(TUE);
	else if ( j == 4 )
		return DayOfWeek(WED);
	else if ( j == 5 )
		return DayOfWeek(THU);
	else if ( j == 6 )
		return DayOfWeek(FRI);
	else if ( j == 7 )
		return DayOfWeek(SAT);



	return DayOfWeek(NULL_DOW);
}


int Util::loadMoneyMktList(MoneyMktList & moneyMktList)
 {

	//MoneyMkt  MKT ;

 		CMarkup xml;

 		//// logFile << "file name is : " << xmlFileName << endl;

 	 // xml.Load('"' + xmlFileName + '"');
 xml.Load("/home/vishist/moneyMkt.xml");
 //xml.FindElem(); // Object
 	  //xml.IntoElem();

 xml.FindElem("MoneyMktList");
 xml.IntoElem();

 	 int runningSeq = 0;
 	 int seq = 0;

 	 xml.FindElem("Seq" );
 	 seq = atoi(MCD_2PCSZ(xml.GetData()));

 	 // logFile << " Seq is : " << seq << endl;

 	 while ( runningSeq != seq )
 	 {
 xml.FindElem("QuoteId" );
 	 //MKT.setQuoteId((MCD_2PCSZ(xml.GetData())));
 	 const char * quoteId = (MCD_2PCSZ(xml.GetData())) ;
 	 String quote = quoteId ; // there is some memory issue if used quoteId in next record
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
 		 // logFile <<"\nQuoteId is:"<< (MCD_2PCSZ(xml.GetData())) << endl;

 xml.FindElem("SettlementDateOffset");
 	 //MKT.setSettlementDateOffset(atoi(MCD_2PCSZ(xml.GetData())));
 	 int settlementDateOffset = atoi(MCD_2PCSZ(xml.GetData()));
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
 		 // logFile << "SettlementDateOffset is:"<<(atoi(MCD_2PCSZ(xml.GetData()))) << endl;

 xml.FindElem("MaturityDateOffset");
 	 String maturityDateOffset = (String(MCD_2PCSZ(xml.GetData())));
 	 const Period  period = Util::convPeriod(maturityDateOffset);

 	 //const Period  period = Period(3,Months);
 	 // MKT.setMaturityDateOffset( maturityDateOffset1 );
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
 		// logFile << "MaturityDateOffset is : " <<(String(MCD_2PCSZ(xml.GetData()))) << "Period is : " << period << endl;

 xml.FindElem("MarketSource");
 	 //MKT.setMarketSource(MCD_2PCSZ(xml.GetData()));
 	 const char * marketSource = (MCD_2PCSZ(xml.GetData())) ;
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
 		// logFile << "MarketSource is:"<<(MCD_2PCSZ(xml.GetData())) << endl;

 xml.FindElem("CompFreq");
 	 const char * compFreqMKt = MCD_2PCSZ(xml.GetData()) ; // pass the integer from frequency.h enum
 	 Frequency compFreq = Util::convFrequency( atoi(compFreqMKt  ));
 	 //MKT.setCompFreq(compFreq);
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
 		// logFile << "CompFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

 xml.FindElem("PayFreq");
 	 const char * payFreqMKt = MCD_2PCSZ(xml.GetData()) ; // pass the integer from frequency.h enum
 	 Frequency payFreq = Util::convFrequency( atoi( payFreqMKt  ));
 	 //MKT.setPayFreq(payFreq);
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
 		// logFile << "PayFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

 xml.FindElem("QuoteDescription");
 	 // MKT.setQuoteDescription(MCD_2PCSZ(xml.GetData()));
 	 const char * quoteDescription = MCD_2PCSZ(xml.GetData());
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
 		// logFile << "QuoteDescription is : " << MCD_2PCSZ(xml.GetData()) << endl;

 xml.FindElem("SrcPage");
 	 //MKT.setSrcPage(MCD_2PCSZ(xml.GetData()));
 	 const char * srcPageTemp = MCD_2PCSZ(xml.GetData()) ;
 	 String srcPage = srcPageTemp;
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
 		// logFile <<  "SrcPage is : " << MCD_2PCSZ(xml.GetData()) << endl;

 xml.FindElem("Precision");
 	 // MKT.setPrecision(atof(MCD_2PCSZ(xml.GetData())));
 	 double precision = (atof(MCD_2PCSZ(xml.GetData()))) ;
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
 		// logFile <<  "Precision is : " << (atof(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

 xml.FindElem("Rate");
 	 //MKT.setRate(atof(MCD_2PCSZ(xml.GetData())));
 	 double rate = (atof(MCD_2PCSZ(xml.GetData()))) ;
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "Rate is : " << (atof(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

 xml.FindElem("MmMasterId" );
 	 //MKT.setMMMasterId(xml.GetData());
 	 const char * mmMasterIdTemp =  MCD_2PCSZ(xml.GetData()) ;
 	 String mmMasterId = mmMasterIdTemp;
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<"\nMmMasterId is:"<< xml.GetData() << endl;

 xml.FindElem("Ccy");
 	 const Currency * ccy =  Currency::find(MCD_2PCSZ(xml.GetData()));
 	 //MKT.setCurrency(ccy);
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "Currency is : " << MCD_2PCSZ(xml.GetData()) << endl;

 xml.FindElem("Bdc");
 	 const char * bdcMa = MCD_2PCSZ(xml.GetData());
 	 std::string bdcM = bdcMa;
 	 const BusDayConv * busDayConv =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
 	 //MKT.setBusDayConv( bdc );
 	 //// logFile << *busDayConv << endl;
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "Bdc is:" <<MCD_2PCSZ(xml.GetData()) << endl;

 xml.FindElem("Dcc");
 	 String dccPay = MCD_2PCSZ(xml.GetData());
 	 // const char * dayCount1 = dayCountPay;
 	 DayCountConv * dayCountConv =  DayCountConv::find(MCD_2PCSZ(xml.GetData()));
 	 //MKT.setDayCountConv( dcc1 );
 	 // MKT.getDayCountConv()->setCalendar("LON");
 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "Dcc is : " << MCD_2PCSZ(xml.GetData()) << endl;

 xml.FindElem("Calendar");
 	 const char * calendarMa = MCD_2PCSZ(xml.GetData());
 	 std::set < std::string > calendar;
 	 calendar.insert(calendarMa);
 	 //MKT.setCalendar( CalendarUtil::getCalendar( calendar));
 	 	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "Calendar is:" <<MCD_2PCSZ(xml.GetData()) << endl;


 	   	xml.FindElem("FwdCurve");
 	   	String fwdCurve = MCD_2PCSZ(xml.GetData());
 	   //	MKT.setFwdCurve(MCD_2PCSZ(xml.GetData()));
 	   		// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "FwdCurve is : " << MCD_2PCSZ(xml.GetData()) << endl;

 	   	xml.FindElem("MarketType");
 	   	String marketType = MCD_2PCSZ(xml.GetData()) ;
 	   	//MKT.setMarketType(MCD_2PCSZ(xml.GetData()));
 	   		// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "MarketType is : " << MCD_2PCSZ(xml.GetData()) << endl;


 	   	xml.FindElem("QuoteType");
 	   	String quoteType = MCD_2PCSZ(xml.GetData()) ;
 	   	//MKT.setQuoteType(MCD_2PCSZ(xml.GetData()));
 	   		// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "QuoteTypee is : " << MCD_2PCSZ(xml.GetData()) << endl;

 	   	xml.FindElem("Description");
 	   	String description = MCD_2PCSZ(xml.GetData()) ;
 	   	//MKT.setDescription(MCD_2PCSZ(xml.GetData()));
 	   		// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile <<  "Description is : " << MCD_2PCSZ(xml.GetData()) << endl;

 	   		// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "QuoteId passed is : " << quoteId << ": " << quote  << " : " << period << endl;

 	   	MoneyMkt  * moneyMkt = new MoneyMkt (
 	   	 			  quote,
 	   	 			  settlementDateOffset,
 	   	 			  period,
 	   	 	          marketSource, // Bloomberg/Reuters/telerate etc
 	   	 	          compFreq,
 	   	 	          payFreq,
 	   	 	          quoteDescription,// details of the instrument
 	   	 	          srcPage,  // where this rate available
 	   	 	          precision,
 	   	 	          rate,
 	   	 	          mmMasterId, // instrumentId
 	   	 	          ccy,
 	   	 	          busDayConv,
 	   	 	          dayCountConv,
 	   	 	          CalendarUtil::getCalendar(calendar),
 	   	 	          fwdCurve,
 	   	 	          marketType, // euro-dollar/repo/prime rate etc
 	   	 	          quoteType,
 	   	 	          description

 	   	 	 );

 	   	//// logFile << "QuoteId is : " << moneyMkt->getQuoteId() << endl;
	   	//// logFile << "MaturityDayOffset is : " << moneyMkt->getMaturityDateOffset() << endl;

	   	moneyMktList.push_back(moneyMkt);
 	 runningSeq++;

 	}


	  xml.OutOfElem();
 	  return 1;

 	}


int Util::loadCurrencyList(CurrencyList & _ccyList)
{

	CMarkup xml;

		xml.Load("/home/vishist/currency.xml");


		xml.FindElem("CurrencyList");
    	xml.IntoElem();

    	int runningSeq = 0;


    	 xml.FindElem("Seq" );
    	 int seq=  atoi(MCD_2PCSZ(xml.GetData()));
    	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<"\nSeq no is:"<< xml.GetData() << endl;

   while ( runningSeq != seq )
   {

    	  xml.FindElem("CurrencyCd" );
    	  const std::string ccyCd =  MCD_2PCSZ(xml.GetData());
    	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<"\nCurrencyCode is:"<< xml.GetData() << endl;

    	  xml.FindElem("AccrualBusDay");
    	  const BusDayConv * bdc1 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
    	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "AccrualBusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;

    	  xml.FindElem("AccrualCalendarsPrimary");
    	  std::set < std::string > cal1;
    	     cal1.insert(MCD_2PCSZ(xml.GetData()) );
    	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "AccrualCalendarsPrimary is:" <<MCD_2PCSZ(xml.GetData()) << endl;

    	  xml.FindElem("AccrualCalendarsSecondary");
    	  std::set < std::string > cal2;
    	  cal2.insert(MCD_2PCSZ(xml.GetData()) );
    	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "AccrualCalendarsSecondary is:" <<MCD_2PCSZ(xml.GetData()) << endl;

    	  xml.FindElem("AccrualFixFreq");
    	  const char * accrualFixFreq = MCD_2PCSZ(xml.GetData()) ; // pass the integer from frequency.h enum
    	  Frequency fixFreq = Util::convFrequency( atoi(  accrualFixFreq  ));
    	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "AccrualFixFreq is:" <<MCD_2PCSZ(xml.GetData()) << endl;

    	  xml.FindElem("AccrualFreq");
    	  Frequency fltFreq = Util::convFrequency( atoi( MCD_2PCSZ(xml.GetData()) ));
    	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "AccrualFreq is:" <<MCD_2PCSZ(xml.GetData()) << endl;

    	  xml.FindElem("DayCount");
          DayCountConv * fltDcc =  DayCountConv::find(MCD_2PCSZ(xml.GetData()));
          // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "DayCount is : " << MCD_2PCSZ(xml.GetData()) << endl;

          xml.FindElem("DayCountFixed");
          DayCountConv * fixDcc =  DayCountConv::find(MCD_2PCSZ(xml.GetData()));
           // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "DayCountFixed is : " << MCD_2PCSZ(xml.GetData()) << endl;

          xml.FindElem("DiscountCurve");
          const std::string discCurve = MCD_2PCSZ(xml.GetData()) ;
           // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "DiscountCurve is : " << MCD_2PCSZ(xml.GetData()) << endl;

          xml.FindElem("Market");
          const char * mkt = MCD_2PCSZ(xml.GetData()) ;
           // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "Market is : " << MCD_2PCSZ(xml.GetData()) << endl;

          xml.FindElem("MarketSourcePage");
          const char * mktSrc = MCD_2PCSZ(xml.GetData()) ;
          // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "MarketSourcePage is : " << MCD_2PCSZ(xml.GetData()) << endl;

          xml.FindElem("RoundingConvention");
          const RoundingConv * roundConv  = RoundingConv::find(MCD_2PCSZ(xml.GetData())) ;
          // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "RoundingConvention is : " << MCD_2PCSZ(xml.GetData()) << endl;

          xml.FindElem("CurrencyDecimals");
          unsigned int ccyDecimals = (atoi(MCD_2PCSZ(xml.GetData())));
          // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "CurrencyDecimals is:" <<atoi(MCD_2PCSZ(xml.GetData())) << endl;

          xml.FindElem("ValueDayLag");
          int valueDayLag = (atoi(MCD_2PCSZ(xml.GetData())));
          // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "ValueDayLag is:" <<atoi(MCD_2PCSZ(xml.GetData())) << endl;

          xml.FindElem("OISCurve");
          const char * oisCurve = MCD_2PCSZ(xml.GetData()) ;
          // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "oisCurve is : " << MCD_2PCSZ(xml.GetData()) << endl;

           xml.FindElem("EuroConversionRate");
           double eurConvRate = (atof(MCD_2PCSZ(xml.GetData())));
          // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "EuroConversionRate is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

          xml.FindElem("EuroSettleDate");
          Date euroSettleEffDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
          // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "EuroSettleDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

          xml.FindElem("XccyCurve");
          const char * xccyCurve = MCD_2PCSZ(xml.GetData()) ;
          // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "XccyCurve is : " << MCD_2PCSZ(xml.GetData()) << endl;

          xml.FindElem("EMUFlg");
          const char * emuFlg = MCD_2PCSZ(xml.GetData()) ;
          // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "EMUFlg is : " << MCD_2PCSZ(xml.GetData()) << endl;

    	  Currency * ccy = new Currency(
    			  ccyCd,
    			  discCurve,
    			  fltDcc,
    			  bdc1,
    			  CalendarUtil::getCalendar(cal1),
    			  CalendarUtil::getCalendar(cal2),
    			  mkt,
    			  mktSrc,
    			  roundConv,
    			  oisCurve,
    			  fltFreq,
    			  fixFreq,
    			  fixDcc,
    			  ccyDecimals,
    			  valueDayLag,
    			  emuFlg,
    			  eurConvRate,
    			  euroSettleEffDate,
    			  xccyCurve);

    	  _ccyList.push_back(ccy);

    	  runningSeq++;
    }

    xml.OutOfElem();
    	      return 1;
}

int Util::loadFraTicket(FraTicket * fraTicket, std::string xmlFileName)
{
	CMarkup xml;

	xml.Load(xmlFileName);

	xml.FindElem("TradeTicket");
	// logFile << "FraTicket is :" << MCD_2PCSZ(xml.GetData()) << endl;
	xml.IntoElem();


	  xml.FindElem("AlternateRef" );
	  fraTicket->setAlternateRef(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<"\nAlternateRef is:"<< xml.GetData() << endl;

	  xml.FindElem("BookingType");
	  fraTicket->setBookingType(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "BookingType is:" << xml.GetData()<< endl;

	  //return 1;
	  xml.FindElem("CustomerAccount");
	  fraTicket->setCustomerAccount(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "Customer Account is:" << xml.GetData()<< endl;

	  xml.FindElem("EarlyTermDate");
	  Date earlyTermDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	  fraTicket->setEarlyTermDate(earlyTermDate);
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "EarlyTermDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

	  xml.FindElem("EarlyTermReason");
	  fraTicket->setEarlyTermReason(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "EarlyTermReason is:" << xml.GetData()<< endl;

	  xml.FindElem("ExternalSystem");
	  fraTicket->setExternalSystem(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "ExternalSystem is:" << xml.GetData()<< endl;

	  xml.FindElem("ExternalRef");
	  fraTicket->setExternalRef(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "ExternalRef is:" << xml.GetData()<< endl;

	  xml.FindElem("FirmAccount");
	  fraTicket->setFirmAccount(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "FirmAccount is:" << xml.GetData()<< endl;

	  xml.FindElem("FlowStatus");
	  fraTicket->setFlowStatus(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "FlowStatus is:" << xml.GetData()<< endl;

	  xml.FindElem("LastModifiedBy");
	  fraTicket->setLastModifiedBy(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "LastModifiedBy is:" << xml.GetData()<< endl;

	  xml.FindElem("LastVerifiedBy");
	  fraTicket->setLastVerifiedBy(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "LastVerifiedBy is:" << xml.GetData()<< endl;

	  xml.FindElem("LegalEntity");
	  fraTicket->setLegalEntity(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "LegalEntity is:" << xml.GetData()<< endl;

	  xml.FindElem("Location");
	  fraTicket->setLocation(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Location is:" << xml.GetData()<< endl;

	  xml.FindElem("MatchingStatus");
	  fraTicket->setMatchingStatus(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "MatchingStatus is:" << xml.GetData()<< endl;

	  xml.FindElem("TerminationDate");
	  fraTicket->setTerminationDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	  //// logFile << "TerminationDate is:" << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y")<< endl;

	  xml.FindElem("ModifiedTimeStamp");
	  fraTicket->setModifiedTimeStamp(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "VerifiedTimeStamp is:" << xml.GetData()<< endl;

	  xml.FindElem("OperationsRef");
	  fraTicket->setOperationsRef(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "OperationsRef is:" << xml.GetData()<< endl;

	  xml.FindElem("OriginalTradeRef");
	  fraTicket->setOriginalTradeRef(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "OriginalTradeRef is:" << xml.GetData()<< endl;

	  xml.FindElem("ProductType");
	  fraTicket->setProductType(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "ProductType is:" << xml.GetData()<< endl;

	  xml.FindElem("SalesPerson");
	  fraTicket->setSalesPerson(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "SalesPerson is:" << xml.GetData()<< endl;

	  xml.FindElem("EffectiveDate");
	  Date effectiveDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	  fraTicket->setEffectiveDate(effectiveDate);
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "EffectiveDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

	  xml.FindElem("SubType");
	  fraTicket->setSubType(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "SubType is:" << xml.GetData()<< endl;

	  xml.FindElem("TradeDate");
	  Date tradeDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	  fraTicket->setTradeDate(tradeDate);
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "TradeDate is:" <<Date(MCD_2PCSZ(xml.GetData()), "d/m/Y")<< endl;

	  xml.FindElem("Trader");
	  fraTicket->setTrader(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Trader is:" << xml.GetData()<< endl;

	  xml.FindElem("TradeRef");
	  fraTicket->setTradeRef(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  	  // logFile << "TradeRef is:" << xml.GetData()<< endl;

	  xml.FindElem("TradeStatus");
	  fraTicket->setTradeStatus(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "TradeStatus is:" << xml.GetData()<< endl;

	  xml.FindElem("TradeType");
	  fraTicket->setTradeType(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "TradeType is:" << xml.GetData()<< endl;

	  xml.FindElem("VerifiedTimeStamp");
	  fraTicket->setVerifiedTimeStamp(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "VerifiedTimeStamp is:" << xml.GetData()<< endl;

	  xml.FindElem("WashAccount");
	  fraTicket->setWashAccount(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  	  // logFile << "WashAccount is:  " << xml.GetData()<< endl;

	xml.FindElem("FraTicket");
	// logFile << "FraTicket is :" << MCD_2PCSZ(xml.GetData()) << endl;
	xml.IntoElem();


  	xml.FindElem("Notional");
	fraTicket->setNotional(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double - NEED TO RUN IN THE SAME ORDER of xml
	//if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile << "Notional is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

	xml.FindElem("SettlementDate");
	Date settlementDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	fraTicket->setSettlementDate(settlementDate);
	//if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile <<  "SettlementDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/y") << endl;

	xml.FindElem("Currency");
	const Currency * currencyFra =  Currency::find(MCD_2PCSZ(xml.GetData()));
	fraTicket->setCurrency(currencyFra);
	//if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "Currency is : " << MCD_2PCSZ(xml.GetData()) << endl;

	xml.FindElem("BuySell");
	fraTicket->setBuySell(xml.GetData());
	//// logFile << "BuySell is:" << xml.GetData()<< endl;


	 xml.FindElem("QuoteLag");
	 fraTicket->setQuoteLag(atoi(MCD_2PCSZ(xml.GetData())));
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile << "QuoteLag is:"<<(atoi(MCD_2PCSZ(xml.GetData()))) << endl;


	 xml.FindElem("QuoteDate");
	 Date QuoteDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	 fraTicket->setQuoteDate(QuoteDate);
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile <<  "QuoteDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/y") << endl;


	 xml.FindElem("StartDate");
	 Date effDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	 fraTicket->setStartDate(effDate);
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 	//  // logFile << "StartDate : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/y") << endl;

	 xml.FindElem("MaturityDate");
	 Date maturityDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	 fraTicket->setMaturityDate(maturityDate);
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
		// logFile << "MaturityDate : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/y") << endl;

	 xml.FindElem("PayCalendars");
	 const char * payCalendarsFra = MCD_2PCSZ(xml.GetData()) ;
	 std::set < std::string > payCalendars;
	 payCalendars.insert(payCalendarsFra);
	 fraTicket->setPayCalendars( payCalendars);
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "payCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;


	 xml.FindElem("BusDayConvention");
	 const BusDayConv * busDayConv =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
	 fraTicket->setBusDayConv( busDayConv );
	 //// logFile << *busDayConv << endl;
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 	// logFile << "Bdc is:" <<MCD_2PCSZ(xml.GetData()) << endl;


	 xml.FindElem("AgreedRate");
	 fraTicket->setAgreedRate(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "AgreedRate is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

	 xml.FindElem("ResetType");
	 fraTicket->setResetType(xml.GetData());
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile << "ResetType is:" << xml.GetData()<< endl;

	 xml.FindElem("RateType");
	 fraTicket->setRateType(xml.GetData());
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "RateType is:" << xml.GetData()<< endl;

	 xml.FindElem("ManualRate");
	 fraTicket->setManualRate(atof(MCD_2PCSZ(xml.GetData())));
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 	 // logFile << "ManualRate :" << (atof(MCD_2PCSZ(xml.GetData())));

	 xml.FindElem("MarketIndex");
	 fraTicket->setMarketIndex(xml.GetData());
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "MarketIndex is:" << xml.GetData()<< endl;

	xml.FindElem("DayCount"); // change in xml to DayCount
	DayCountConv * dayCountConv =  DayCountConv::find(MCD_2PCSZ(xml.GetData()));
	fraTicket->setDayCount( dayCountConv );
	fraTicket->getDayCount()->setCalendar(payCalendars);
	 // logFile << "DayCount is:" << MCD_2PCSZ(xml.GetData())<< endl;

	 xml.FindElem("Precision");
		 fraTicket->setPrecision(atoi(MCD_2PCSZ(xml.GetData())));

	xml.FindElem("QuoteCalendars");
	const char * quoteCalendarsFra = MCD_2PCSZ(xml.GetData());
	std::set < std::string >quoteCalendars1 ;
	quoteCalendars1.insert(quoteCalendarsFra);
	fraTicket->setQuoteCalendars( quoteCalendars1);
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile << "QuoteCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

	xml.FindElem("DiscountCurve");
	fraTicket->setDiscountCurve(MCD_2PCSZ(xml.GetData()));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "DiscountCurve is : " << MCD_2PCSZ(xml.GetData()) << endl;


	xml.FindElem("PaymentConvention");
	fraTicket->setPaymentConvention(MCD_2PCSZ(xml.GetData()));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "PaymentConvention is : " << MCD_2PCSZ(xml.GetData()) << endl;

	fraTicket->setPrecision(7);

	xml.FindElem("ResetConvention");
	fraTicket->setResetConvention(MCD_2PCSZ(xml.GetData()));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "ResetConvention is : " << MCD_2PCSZ(xml.GetData()) << endl;



	  xml.OutOfElem();// out of trade ticket
	  xml.OutOfElem(); // out of fra ticket

	  /*

	  fraTicket  = new FraTicket(
			  fra.getCurrency(),
			  fra.getBuySell(),
			  fra.getNotional(),
			  fra.getSettlementDate(),
			  fra.getQuoteLag(),
			  fra.getQuoteDate(),
			  fra.getPayCalendars(),
			  fra.getBusDayConv(),
			  fra.getAgreedRate(),
			  fra.getResetType(),
			  fra.getResetApplied(),
			  fra.getRateType(), // ADD_ON OR DISCOUNT OR SIMPLE
			  fra.getMarketIndex(),
			  fra.getDayCount(),
			  fra.getQuoteCalendars(),
			  fra.getDiscountCurve(),
			  fra.getPaymentConvention(),
			  fra.getResetConvention()
			  );
*/
	  return 1;

}

int Util::loadSwapOption(SwapOption * swapOption , std::string xmlFileName)
{

	CMarkup xml;
	SwapOption swo;
	//SwapTicket swapTicket;


		//SwapLeg slp;

		//xml.Load("/home/vishist/swapOption.xml");

		  xml.Load(xmlFileName);

		  xml.FindElem("TradeTicket");
		  // logFile << "TradeTicket is :" << MCD_2PCSZ(xml.GetData()) << endl;
		  xml.IntoElem();


		  xml.FindElem("Option");
		 // logFile << "SwapOption is :" << MCD_2PCSZ(xml.GetData()) << endl;
		  xml.IntoElem();



    if ( xml.FindElem("BuyFlag" ))
	   swo.setBuyFlag(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	// logFile <<"\nBuyFlag is:"<< xml.GetData() << endl;

		  xml.FindElem("ExerciseFlag");
		  swo.setExerciseFlag(xml.GetData());
		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "ExerciseFlag is:" << xml.GetData()<< endl;


		  xml.FindElem("ExerciseType");
		  swo.setExerciseType(xml.GetData());
		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "ExerciseType is:" << xml.GetData()<< endl;

	  xml.FindElem("ExpiryDate");
			  Date expiryDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
			  swo.setExpiryDate(expiryDate);
			  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
		  // logFile <<  "ExpiryDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;


		  xml.FindElem("OptionStyle");
		  swo.setOptionStyle(xml.GetData());
		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "OptionStyle is:" << xml.GetData()<< endl;

		  xml.FindElem("OptionType");
		  swo.setOptionType(xml.GetData());
		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "OptionType is:" << xml.GetData()<< endl;

		  xml.FindElem("SWTPosition");
		  swo.setPosition(xml.GetData());
		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "SWT Position is:" << xml.GetData()<< endl;

		  xml.FindElem("PricingMethod");
		  swo.setPricingMethod(xml.GetData());
		   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "PricingMethod is:" << xml.GetData()<< endl;

		  xml.FindElem("Strike");
		  swo.setStrike(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Strike is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

		   xml.FindElem("SwapEndDate");
		   Date swapEndDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
		   swo.setSwapEndDate(swapEndDate);
		   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "swapEndDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;


		   xml.FindElem("SwapLag");
		   swo.setSwapLag(atoi(MCD_2PCSZ(xml.GetData())));
		   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "SwapLag is:"<<(atoi(MCD_2PCSZ(xml.GetData()))) << endl;

		   xml.FindElem("SwapLagBusDay");
		   const char * swapLagBusDayOption = MCD_2PCSZ(xml.GetData());
		   std::string swapLagBusDayP = swapLagBusDayOption;
		   const BusDayConv * swapLagBusDay1 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
		   swo.setSwapLagBusDay( swapLagBusDay1);
		   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "SwapLagBusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;


		   xml.FindElem("SwapRef");
		   swo.setSwapRef(xml.GetData());
		   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "SwapRef is:" << xml.GetData()<< endl;

		   xml.FindElem("SwapStartDate");
		   Date swapStartDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
		   swo.setSwapStartDate(swapStartDate);
		   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "SwapStartDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

		   xml.FindElem("VolId");
		   swo.setVolId(xml.GetData());
		   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Volid is:" << xml.GetData()<< endl;

	   xml.OutOfElem();
	   xml.OutOfElem();

	   SwapTicket * swapTicket = new SwapTicket(); // empty object at this stage

	    swapOption =  new SwapOption(

	           swo.getBuyFlag(),
	           swo.getExerciseFlag(),
	           swo.getExerciseType(),
	           swo.getExpiryDate(),
	           swo.getOptionStyle(),
	           swo.getOptionType(),
	           swo.getPosition(),
	           swo.getPricingMethod(),
	           swo.getStrike(),
	           swo.getSwapEndDate(),
	           swo.getSwapLag(),
	           swo.getSwapLagBusDay(),
	           swo.getSwapRef(),
	           swo.getSwapStartDate(),
	           swo.getVolId(),
	           swapTicket
	   );


	   return 1;

}

int Util::loadSwapTicket(SwapTicket * swapTicket , std::string xmlFileName)
{
	SwapLeg slp;
	SwapLeg slr;

	CMarkup xml;

  xml.Load(xmlFileName);

  xml.FindElem("TradeTicket");
  // logFile << "TradeTicket is :" << MCD_2PCSZ(xml.GetData()) << endl;
  xml.IntoElem();

  if ( xml.FindElem("AlternateRef" ))
  swapTicket->setAlternateRef(xml.GetData());
  //if ( getenv("IRD_DEBUG") == std::string("Yes"))
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
  	 	//  // logFile <<"\nAlternateRef is:"<< xml.GetData() << endl;

  xml.FindElem("BookingType");
  	  swapTicket->setBookingType(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile << "BookingType is:" << xml.GetData()<< endl;

  //return 1;
  xml.FindElem("CustomerAccount");
  	  swapTicket->setCustomerAccount(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "Customer Account is:" << xml.GetData()<< endl;

  xml.FindElem("EarlyTermDate");
  	  Date earlyTermDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  	  swapTicket->setEarlyTermDate(earlyTermDate);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "EarlyTermDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

  xml.FindElem("EarlyTermReason");
  	  swapTicket->setEarlyTermReason(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile << "EarlyTermReason is:" << xml.GetData()<< endl;

  xml.FindElem("ExternalSystem");
  	  swapTicket->setExternalSystem(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "ExternalSystem is:" << xml.GetData()<< endl;

  xml.FindElem("ExternalRef");
  	  swapTicket->setExternalRef(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "ExternalRef is:" << xml.GetData()<< endl;

  xml.FindElem("FirmAccount");
  	  swapTicket->setFirmAccount(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "FirmAccount is:" << xml.GetData()<< endl;

  xml.FindElem("FlowStatus");
  	  swapTicket->setFlowStatus(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "FlowStatus is:" << xml.GetData()<< endl;

  xml.FindElem("LastModifiedBy");
  	  swapTicket->setLastModifiedBy(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "LastModifiedBy is:" << xml.GetData()<< endl;

  xml.FindElem("LastVerifiedBy");
  	  swapTicket->setLastVerifiedBy(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "LastVerifiedBy is:" << xml.GetData()<< endl;

  xml.FindElem("LegalEntity");
  	  swapTicket->setLegalEntity(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "LegalEntity is:" << xml.GetData()<< endl;

  xml.FindElem("Location");
  	  swapTicket->setLocation(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Location is:" << xml.GetData()<< endl;

  xml.FindElem("MatchingStatus");
  	  swapTicket->setMatchingStatus(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "MatchingStatus is:" << xml.GetData()<< endl;

  xml.FindElem("TerminationDate");
  	  swapTicket->setTerminationDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "MaturityDate is:" << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y")<< endl;

  xml.FindElem("ModifiedTimeStamp");
 	  swapTicket->setModifiedTimeStamp(xml.GetData());
 	//if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "ModifiedTimeStamp is:" << xml.GetData()<< endl;

  xml.FindElem("OperationsRef");
  	  swapTicket->setOperationsRef(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "OperationsRef is:" << xml.GetData()<< endl;

  xml.FindElem("OriginalTradeRef");
  	  swapTicket->setOriginalTradeRef(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "OriginalTradeRef is:" << xml.GetData()<< endl;

  xml.FindElem("ProductType");
  	  swapTicket->setProductType(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "ProductType is:" << xml.GetData()<< endl;

  xml.FindElem("SalesPerson");
  	  swapTicket->setSalesPerson(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "SalesPerson is:" << xml.GetData()<< endl;

  xml.FindElem("EffectiveDate");
  	  Date effectiveDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  	  swapTicket->setEffectiveDate(effectiveDate);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "EffectiveDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

  xml.FindElem("SubType");
  	  swapTicket->setSubType(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "SubType is:" << xml.GetData()<< endl;

  xml.FindElem("TradeDate");
  	  Date tradeDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  	  swapTicket->setTradeDate(tradeDate);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "TradeDate is:" <<Date(MCD_2PCSZ(xml.GetData()), "d/m/Y")<< endl;

  xml.FindElem("Trader");
  	  swapTicket->setTrader(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Trader is:" << xml.GetData()<< endl;

  xml.FindElem("TradeRef");
  	  swapTicket->setTradeRef(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "TradeRef is:" << xml.GetData()<< endl;

  xml.FindElem("TradeStatus");
  	  swapTicket->setTradeStatus(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "TradeStatus is:" << xml.GetData()<< endl;

  xml.FindElem("TradeType");
  	  swapTicket->setTradeType(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "TradeType is:" << xml.GetData()<< endl;

  xml.FindElem("VerifiedTimeStamp");
  	  swapTicket->setVerifiedTimeStamp(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "VerifiedTimeStamp is:" << xml.GetData()<< endl;

  xml.FindElem("WashAccount");
  	  swapTicket->setWashAccount(xml.GetData());
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "WashAccount is:  " << xml.GetData()<< endl;

  xml.FindElem("SwapLegList");
   xml.IntoElem();

  xml.FindElem("SwapLeg");
  xml.IntoElem();
  // logFile << " \nSwap Leg1 is :" << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AccrualBusDay");
   	  const char * accrualBusDayPay = MCD_2PCSZ(xml.GetData());
   	  std::string accrualBusDayP = accrualBusDayPay;
   	  const BusDayConv * accrualBusDay1 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
   	  slp.setAccrualBusDay( accrualBusDay1);
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualBusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;

   xml.FindElem("AccrualCalendars");
      const char * accrualCalendarsPay = MCD_2PCSZ(xml.GetData());
      std::set < std::string > accrualCalendars1;
      accrualCalendars1.insert(accrualCalendarsPay);
      slp.setAccrualCalendars( accrualCalendars1);
    // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AccrualFreq");
    const char * accrualFreqPay = MCD_2PCSZ(xml.GetData()) ; // pass the integer from frequency.h enum
    Frequency accrualFreq1 = Util::convFrequency( atoi(  accrualFreqPay  ));
    slp.setAccrualFreq(accrualFreq1);
    // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualFreq is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AccrualMarching");
   	//const char * accrualMarchingPay = MCD_2PCSZ(xml.GetData());
    //std::string accrualMarchingP = accrualMarchingPay;
   	const DateMarcher * accrualMarching1 =  DateMarcher::find(MCD_2PCSZ(xml.GetData()));
   	slp.setAccrualMarching( accrualMarching1 );
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualMarching is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AccrualRollDay");
  	  slp.setAccrualRollDay(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualRollDay is:"<<(atoi(MCD_2PCSZ(xml.GetData()))) << endl;

  xml.FindElem("AccrualRollWeek");
  	  const char * accrualRollWeekPay = (MCD_2PCSZ(xml.GetData())) ;
  	  // DayOfWeek  accrualRollWeek1(DayOfWeek ((int) accrualRollWeekPay  ));
  	  DayOfWeek accrualRollWeek1 = Util::convDayOfWeek( atoi(  accrualRollWeekPay   ));
  	  slp.setAccrualRollWeek(accrualRollWeek1);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualRollWeek is:"<<MCD_2PCSZ(xml.GetData())<< endl;


  xml.FindElem("AmortRollDay");
  	  slp.setAmortRollDay(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "AmortRollDay is:"<<(atoi(MCD_2PCSZ(xml.GetData()))) << endl;

  xml.FindElem("AmortRollWeek");
  	  const char * amortRollWeekPay = (MCD_2PCSZ(xml.GetData())) ;
  	  //DayOfWeek  amortRollWeek1(DayOfWeek ((int) amortRollWeekPay  ));
  	  DayOfWeek amortRollWeek1 = Util::convDayOfWeek( atoi(  amortRollWeekPay   ));
  	  slp.setAmortRollWeek(amortRollWeek1);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortRollWeek is:"<<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AmortAmount");
  	  slp.setAmortAmount(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortAmount is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

  xml.FindElem("AmortBusDay");
  	  const char * amortBusDayPay = MCD_2PCSZ(xml.GetData());
  	  std::string amortBusDayP = amortBusDayPay;
  	  const BusDayConv * amortBusDay1 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
  	  slp.setAmortBusDay( amortBusDay1);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortBusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AmortCalendars");
  	 const char * amortCalendarsPay = MCD_2PCSZ(xml.GetData()) ;
  	 std::set < std::string > amortCalendars1;
  	 amortCalendars1.insert(amortCalendarsPay);
  	 slp.setAmortCalendars( amortCalendars1);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AmortEndDate");
  	  Date amortEndDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  	  slp.setAmortEndDate(amortEndDatePay);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "AmortEndDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

  xml.FindElem("AmortFreq");
  	  const char * amortFreqPay = MCD_2PCSZ(xml.GetData()) ;
  	  Frequency amortFreq1 = Util::convFrequency( atoi(  amortFreqPay  ));
  	  slp.setAmortFreq(amortFreq1);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

  xml.FindElem("AmortMarching");
  	  //const char * accrualMarchingPay = MCD_2PCSZ(xml.GetData());
      //std::string accrualMarchingP = accrualMarchingPay;
  	  const DateMarcher * amortMarching1 =  DateMarcher::find(MCD_2PCSZ(xml.GetData()));
  	  slp.setAmortMarching( amortMarching1 );
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortMarching is:" <<MCD_2PCSZ(xml.GetData()) << endl;

   xml.FindElem("AmortStartDate");
     Date amortStartDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
     slp.setAmortStartDate(amortStartDatePay);
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "AmortStartDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

   xml.FindElem("AmortType");
     slp.setAmortType(MCD_2PCSZ(xml.GetData()));
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "AmortType  is : " << MCD_2PCSZ(xml.GetData()) << endl;

   xml.FindElem("AveragingMethod");
   	   slp.setAveragingMethod(MCD_2PCSZ(xml.GetData()));
    // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "AveragingMethod is : " << MCD_2PCSZ(xml.GetData()) << endl;

   xml.FindElem("BackStubDate");
   	   Date backStubDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
   	   slp.setBackStubDate(backStubDatePay);
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "Back Stub Date  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

   xml.FindElem("BackStubManualRate");
     slp.setBackStubManualRate(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "BackStubManualRate is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

   xml.FindElem("CompFreq");
   	   const char * compFreqPay = MCD_2PCSZ(xml.GetData()) ; // pass the integer from frequency.h enum
   	   Frequency compFreq1 = Util::convFrequency( atoi( compFreqPay  ));
   	   slp.setCompFreq(compFreq1);
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "CompFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

   xml.FindElem("CompoundingConv");
   	   slp.setCompoundingConv(MCD_2PCSZ(xml.GetData()));
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "CompoundingConv is : " << MCD_2PCSZ(xml.GetData()) << endl;

   xml.FindElem("Currency");
   	   const Currency * currencyPay =  Currency::find(MCD_2PCSZ(xml.GetData()));
   	   slp.setCurrency(currencyPay);
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	   // logFile <<  "Currency is : " << MCD_2PCSZ(xml.GetData()) << endl;

   xml.FindElem("DayCount");
   	   String dayCountPay = MCD_2PCSZ(xml.GetData());
   	   // const char * dayCount1 = dayCountPay;
   	   DayCountConv * dayCount1 =  DayCountConv::find(MCD_2PCSZ(xml.GetData()));
   	   std::set < std::string > dccPayCalendars = slp.getAccrualCalendars();
   	   slp.setDayCount( dayCount1 );
   	   slp.getDayCount()->setCalendar(dccPayCalendars);
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "DayCount is : " << MCD_2PCSZ(xml.GetData()) << endl;

   xml.FindElem("DiscountCurve");
       slp.setDiscountCurve(MCD_2PCSZ(xml.GetData()));
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	   // logFile <<  "DiscountCurve is : " << MCD_2PCSZ(xml.GetData()) << endl;

   xml.FindElem("EndDate");
     	Date endDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
     	slp.setEndDate(endDatePay);
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	   // logFile <<  "End Date  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

   xml.FindElem("EndDateRollFlag");
   	   slp.setEndDateRollFlag(MCD_2PCSZ(xml.GetData()));
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	   // logFile <<  "EndDateRollFlag is : " << MCD_2PCSZ(xml.GetData()) << endl;

   xml.FindElem("EndOfMonthIndicator");
     	 slp.setEndOfMonthIndicator(MCD_2PCSZ(xml.GetData()));
     // if ( getenv("IRD_DEBUG") == std::string("Yes"))
    	 // logFile <<  "EndOfMonthIndicator is : " << MCD_2PCSZ(xml.GetData()) << endl;

   xml.FindElem("FixedQuote");
   	   slp.setFixedQuote(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
   	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Fixed Quote is : " <<  atof(MCD_2PCSZ(xml.GetData())) << endl;

   xml.FindElem("FrontStubDate");
   	   Date frontStubDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
   	   slp.setFrontStubDate(frontStubDatePay);
   //	if ( getenv("IRD_DEBUG") == std::string("Yes"))
   		// logFile <<  "FrontStubDate is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

   xml.FindElem("FrontStubManualRate");
   	   slp.setFrontStubManualRate(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	   // logFile << "FrontStubManualRate is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

   xml.FindElem("GearFactor");
     	 slp.setGearFactor(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
     	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
     		 // logFile << "GearFactor is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

   xml.FindElem("InitialQuoteCalendars");
   	   const char * initialQuoteCalendarsPay = MCD_2PCSZ(xml.GetData()) ;
   	   std::set < std::string > initialQuoteCalendars1;
   	   initialQuoteCalendars1.insert(initialQuoteCalendarsPay);
   	   slp.setInitialQuoteCalendars( initialQuoteCalendars1);
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
		 // logFile << "InitialQuoteCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

	xml.FindElem("InitialQuoteDate");
		Date initialQuoteDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
		slp.setInitialQuoteDate(initialQuoteDatePay);
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
		 // logFile <<  "InitialQuoteDate is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

	xml.FindElem("InitialQuoteLag");
	 	 slp.setInitialQuoteLag(atoi(MCD_2PCSZ(xml.GetData()))); // this is int man - convert char * to int
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "InitialQuoteLag is:" <<atoi(MCD_2PCSZ(xml.GetData())) << endl;

	 xml.FindElem("LegNo");
	 slp.setLegNo(atoi(MCD_2PCSZ(xml.GetData()))); // this is int man - convert char * to int
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "LegNo is:" <<atoi(MCD_2PCSZ(xml.GetData())) << endl;

	 xml.FindElem("LegType");
	 slp.setLegType(MCD_2PCSZ(xml.GetData()));
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "LegType is : " << MCD_2PCSZ(xml.GetData()) << endl;

	 xml.FindElem("MarketIndex");
	 slp.setMarketIndex(MCD_2PCSZ(xml.GetData()));
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "MarketIndex is : " << MCD_2PCSZ(xml.GetData()) << endl;

	 xml.FindElem("Notional");
	 slp.setNotional(atof(MCD_2PCSZ(xml.GetData())));
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Notional for first leg is :" << atoi(MCD_2PCSZ(xml.GetData())) << endl;

xml.FindElem("NotionalExchange");
  slp.setNotionalExchange(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "NotionalExchange is : " << MCD_2PCSZ(xml.GetData()) << endl;

xml.FindElem("PayBusDay");
  const char * payBusDayPay = MCD_2PCSZ(xml.GetData());
   std::string payBusDayP = payBusDayPay;
  const BusDayConv * payBusDay1 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
  slp.setPayBusDay( payBusDay1 );
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "PayBusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;

xml.FindElem("PayCalendars");
  const char * payCalendarsPay = MCD_2PCSZ(xml.GetData()) ;
  std::set < std::string > payCalendars1;
   payCalendars1.insert(payCalendarsPay);
   slp.setPayCalendars( payCalendars1);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "payCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

xml.FindElem("PayFreq");
  const char * payFreqPay = MCD_2PCSZ(xml.GetData()) ;
  Frequency payFreq1 = Util::convFrequency( atoi(  payFreqPay  ));
  slp.setPayFreq(payFreq1);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "PayFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

  xml.FindElem("PayLag");
    slp.setPayLag(atoi(MCD_2PCSZ(xml.GetData())));

xml.FindElem("PayMarching");
  const char * payMarchingPay = MCD_2PCSZ(xml.GetData());
    std::string payMarchingP = payMarchingPay;
  const DateMarcher * payMarching1 =  DateMarcher::find(MCD_2PCSZ(xml.GetData()));
  slp.setPayMarching( payMarching1 );
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "PayMarching is:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

xml.FindElem("PaymentConvention");
  slp.setPaymentConvention(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "PaymentConvention is : " << MCD_2PCSZ(xml.GetData()) << endl;

xml.FindElem("PaymentConversionCurrency");
  const Currency * paymentConversionCurrency1 =  Currency::find(MCD_2PCSZ(xml.GetData()));
   slp.setPaymentConversionCurrency(paymentConversionCurrency1);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "PaymentConversionCurrency is : " << MCD_2PCSZ(xml.GetData()) << endl;

xml.FindElem("PaymentConversionIndex");
  slp.setPaymentConversionIndex(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "PaymentConversionIndex is : " << MCD_2PCSZ(xml.GetData()) << endl;

xml.FindElem("PaymentConversionLag");
  slp.setPaymentConversionLag(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "PaymentConversionLag is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;

xml.FindElem("PayRollDay");
  slp.setPayRollDay(atoi(MCD_2PCSZ(xml.GetData()))); // this is int man - convert char * to int
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "PayRollDay is:" <<atoi(MCD_2PCSZ(xml.GetData())) << endl;

xml.FindElem("PayRollWeek");
  const char * payRollWeekPay = (MCD_2PCSZ(xml.GetData())) ;
   //DayOfWeek  payRollWeek1(DayOfWeek ((int) payRollWeekPay  ));
   DayOfWeek payRollWeek1 = Util::convDayOfWeek( atoi(  payRollWeekPay   ));
   slp.setPayRollWeek(payRollWeek1);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "PayRollWeek is:"<<MCD_2PCSZ(xml.GetData())<< endl;

xml.FindElem("Position");
  slp.setPosition(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "Position is : " << MCD_2PCSZ(xml.GetData()) << endl;


xml.FindElem("QuoteCalendars");
  const char * quoteCalendarsPay = MCD_2PCSZ(xml.GetData());
  std::set < std::string >quoteCalendars1 ;
  quoteCalendars1.insert(quoteCalendarsPay);
  slp.setQuoteCalendars( quoteCalendars1);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "QuoteCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

xml.FindElem("QuoteLag");
  slp.setQuoteLag(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "QuoteLag is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

xml.FindElem("RateCutOff");
  slp.setRateCutOff(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "RateCutOff is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

xml.FindElem("ResetAveraging");
   slp.setResetAveraging(MCD_2PCSZ(xml.GetData()));
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "ResetAveraging is : " << MCD_2PCSZ(xml.GetData()) << endl;


   xml.FindElem("ResetBusDay");
       const BusDayConv * resetBusDay1 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
       slp.setResetBusDay( resetBusDay1);
       // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Reset BusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;

xml.FindElem("ResetConvention");
  slp.setResetConvention(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "ResetConvention is : " << MCD_2PCSZ(xml.GetData()) << endl;

xml.FindElem("ResetFreq");
  const char * resetFreqPay = MCD_2PCSZ(xml.GetData()) ;
  Frequency resetFreq1 = Util::convFrequency( atoi(  resetFreqPay  ));
  slp.setResetFreq(resetFreq1);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "ResetFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output


  xml.FindElem("ResetMarching");
     const DateMarcher * resetMarching1 =  DateMarcher::find(MCD_2PCSZ(xml.GetData()));
     slp.setResetMarching( resetMarching1 );
     // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Reset Marching is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("ResetRollDay");
    slp.setResetRollDay(atoi(MCD_2PCSZ(xml.GetData())));
    // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Reset RollDay is:"<<(atoi(MCD_2PCSZ(xml.GetData()))) << endl;

    xml.FindElem("ResetRollWeek");
    const char * resetRollWeekPay = (MCD_2PCSZ(xml.GetData())) ;
     DayOfWeek resetRollWeek1 = Util::convDayOfWeek( atoi(  resetRollWeekPay   ));
     slp.setResetRollWeek(resetRollWeek1);
    // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Reset RollWeek is:"<<MCD_2PCSZ(xml.GetData())<< endl;


xml.FindElem("ResetType");
  slp.setResetType(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "ResetType is : " << MCD_2PCSZ(xml.GetData()) << endl;

xml.FindElem("ScheduleCustomFlag");
  slp.setScheduleCustomFlag(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "ScheduleCustomFlag is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

xml.FindElem("Spread");
  slp.setSpread(atof(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "Spread is : " << (atof(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

xml.FindElem("StartDate");
  Date startDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  slp.setStartDate(startDatePay);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "StartDate is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

xml.FindElem("StartDateRollFlag");
  slp.setStartDateRollFlag(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "StartDateRollFlag is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.OutOfElem();

 xml.FindElem("SwapLeg");
  xml.IntoElem();
//   xml.FindElem("LegType");
 // // logFile << "second leg type is :" << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AccrualBusDay");
  const char * accrualBusDayRec = MCD_2PCSZ(xml.GetData());
  std::string accrualBusDayR = accrualBusDayRec;
  const BusDayConv * accrualBusDay2 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
  slr.setAccrualBusDay( accrualBusDay2 );
  //// logFile << *busDayConv << endl;
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualBusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AccrualCalendars");
  const char * accrualCalendarsRec = MCD_2PCSZ(xml.GetData());
  std::set < std::string > accrualCalendars2;
  accrualCalendars2.insert(accrualCalendarsRec);
  slr.setAccrualCalendars( accrualCalendars2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AccrualFreq");
  const char * accrualFreqRec = MCD_2PCSZ(xml.GetData()) ; // pass the integer from frequency.h enum
  Frequency accrualFreq2 = Util::convFrequency( atoi( accrualFreqRec)  );
  slr.setAccrualFreq(accrualFreq2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualFreq is:" <<MCD_2PCSZ(xml.GetData()) << endl;


  xml.FindElem("AccrualMarching");
 // const String accrualMarchingRec = MCD_2PCSZ(xml.GetData());
  const char * accrualMarchingRec = MCD_2PCSZ(xml.GetData());
  std::string accrualMarchingR = accrualMarchingRec;
  const DateMarcher * accrualMarching2 =  DateMarcher::find(MCD_2PCSZ(xml.GetData()));
  slr.setAccrualMarching( accrualMarching2 );
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualMarching is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AccrualRollDay");
  slr.setAccrualRollDay(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualRollDay:"<<(atoi(MCD_2PCSZ(xml.GetData()))) << endl;

  xml.FindElem("AccrualRollWeek");
  const char * accrualRollWeekRec = (MCD_2PCSZ(xml.GetData())) ;
 // DayOfWeek  accrualRollWeek2(DayOfWeek ((int) accrualRollWeekRec  ));
  DayOfWeek accrualRollWeek2 = Util::convDayOfWeek( atoi(  accrualRollWeekRec   ));
  slr.setAccrualRollWeek(accrualRollWeek2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AccrualRollWeek:"<<MCD_2PCSZ(xml.GetData())<< endl;


  xml.FindElem("AmortRollDay");
  slr.setAmortRollDay(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortRollDay is:"<<(atoi(MCD_2PCSZ(xml.GetData()))) << endl;

  xml.FindElem("AmortRollWeek");
  const char * amortRollWeekRec = (MCD_2PCSZ(xml.GetData())) ;
  //DayOfWeek  amortRollWeek2(DayOfWeek ((int) amortRollWeekRec  ));
  DayOfWeek amortRollWeek2 = Util::convDayOfWeek( atoi(  amortRollWeekRec   ));
  slr.setAmortRollWeek(amortRollWeek2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortRollWeek is:"<<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AmortAmount");
  slr.setAmortAmount(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortAmount is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

  xml.FindElem("AmortBusDay");
    const char * amortBusDayRec = MCD_2PCSZ(xml.GetData());
     std::string amortBusDayR = amortBusDayRec;
     const BusDayConv * amortBusDay2 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
     slr.setAmortBusDay( amortBusDay2);
    // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortBusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;


  xml.FindElem("AmortCalendars");
  const char * amortCalendarsRec = MCD_2PCSZ(xml.GetData());
  std::set < std::string > amortCalendars2;
  amortCalendars2.insert(amortCalendarsRec);
  slr.setAmortCalendars( amortCalendars2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AmortEndDate");
  Date amortEndDateRec(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  slr.setAmortEndDate(amortEndDateRec);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "AmortEndDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

  xml.FindElem("AmortFreq");
  const char * amortFreqRec= MCD_2PCSZ(xml.GetData()) ; // pass the integer from frequency.h enum
  Frequency amortFreq2 = Util::convFrequency( atoi( amortFreqRec  ));
  slr.setAmortFreq(amortFreq2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<"AmortFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

  xml.FindElem("AmortMarching");
    //const char * accrualMarchingPay = MCD_2PCSZ(xml.GetData());
      //std::string accrualMarchingP = accrualMarchingPay;
     const DateMarcher * amortMarching2 =  DateMarcher::find(MCD_2PCSZ(xml.GetData()));
     slr.setAmortMarching( amortMarching2 );
     // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "AmortMarching is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AmortStartDate");
  Date amortStartDateRec(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  slr.setAmortStartDate(amortStartDateRec);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "AmortStartDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

  xml.FindElem("AmortType");
  slr.setAmortType(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "AmortType  is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("AveragingMethod");
  slr.setAveragingMethod(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "AveragingMethod is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("BackStubDate");
  Date backStubDateRec(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  slr.setBackStubDate(backStubDateRec);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "Back Stub Date  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

  xml.FindElem("BackStubManualRate");
  slr.setBackStubManualRate(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "BackStubManualRate is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

  xml.FindElem("CompFreq");
  const char * compFreqRec = MCD_2PCSZ(xml.GetData()) ; // pass the integer from frequency.h enum
  Frequency compFreq2 = Util::convFrequency( atoi(compFreqRec  ));
  slr.setCompFreq(compFreq2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "CompFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

  xml.FindElem("CompoundingConv");
  slr.setCompoundingConv(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "CompoundingConv is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("Currency");
  const Currency * currencyRec =  Currency::find(MCD_2PCSZ(xml.GetData()));
  slr.setCurrency(currencyRec);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "Currency is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("DayCount");
  String dayCountRec = MCD_2PCSZ(xml.GetData());
// const char * dayCountR = dayCountRec;
  DayCountConv * dayCount2 =  DayCountConv::find(MCD_2PCSZ(xml.GetData()));
  std::set < std::string > dccRecCalendars = slr.getAccrualCalendars();
   slr.setDayCount( dayCount2 );
  slr.getDayCount()->setCalendar(dccRecCalendars);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "DayCount is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("DiscountCurve");
  slr.setDiscountCurve(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "DiscountCurve is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("EndDate");
  Date endDateRec(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  slr.setEndDate(endDateRec);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "EndDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

  xml.FindElem("EndDateRollFlag");
  slr.setEndDateRollFlag(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "EndDateRollFlag is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("EndOfMonthIndicator");
  slr.setEndOfMonthIndicator(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "EndOfMonthIndicator is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("FixedQuote");
  slr.setFixedQuote(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
    // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Fixed Quote is : " <<  atof(MCD_2PCSZ(xml.GetData())) << endl;

  xml.FindElem("FrontStubDate");
  Date frontStubDateRec(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  slr.setFrontStubDate(frontStubDateRec);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "FrontStubDate is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

  xml.FindElem("FrontStubManualRate");
  slr.setFrontStubManualRate(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "FrontStubManualRate is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

  xml.FindElem("GearFactor");
  slr.setGearFactor(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))<ModifiedTimeStamp>/12/12/2012 9:15AM</ModifiedTimeStamp>
	  // logFile << "GearFactor is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

  xml.FindElem("InitialQuoteCalendars");
  const char * initialQuoteCalendarsRec = MCD_2PCSZ(xml.GetData());
  std::set < std::string >initialQuoteCalendars2;
  initialQuoteCalendars2.insert(initialQuoteCalendarsRec);
  slr.setInitialQuoteCalendars( initialQuoteCalendars2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "InitialQuoteCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("InitialQuoteDate");
  Date initialQuoteDateRec(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
  slr.setInitialQuoteDate(initialQuoteDateRec);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "InitialQuoteDate is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

  xml.FindElem("InitialQuoteLag");
  slr.setInitialQuoteLag(atoi(MCD_2PCSZ(xml.GetData()))); // this is int man - convert char * to int
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "InitialQuoteLag is:" <<atoi(MCD_2PCSZ(xml.GetData())) << endl;

  xml.FindElem("LegNo");
  slr.setLegNo(atoi(MCD_2PCSZ(xml.GetData()))); // this is int man - convert char * to int
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "LegNo is:" <<atoi(MCD_2PCSZ(xml.GetData())) << endl;

  xml.FindElem("LegType");
  slr.setLegType(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "LegType is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("MarketIndex");
  slr.setMarketIndex(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "MarketIndex is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("Notional");
    slr.setNotional(atof(MCD_2PCSZ(xml.GetData())));
    // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Notional for first leg is :" << atoi(MCD_2PCSZ(xml.GetData())) << endl;

  xml.FindElem("NotionalExchange");
  slr.setNotionalExchange(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "NotionalExchange is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("PayBusDay");
  const char* payBusDayRec = MCD_2PCSZ(xml.GetData());
  std::string payBusDayR = payBusDayRec;
  const BusDayConv * payBusDay2 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
  slr.setPayBusDay( payBusDay2 );
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "PayBusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("PayCalendars");
  const char * payCalendarsRec = MCD_2PCSZ(xml.GetData());
  std::set < std::string > payCalendars2;
  payCalendars2.insert(payCalendarsRec);
  slr.setPayCalendars( payCalendars2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "payCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("PayFreq");
  const char * payFreqRec = MCD_2PCSZ(xml.GetData()) ; // pass the integer from frequency.h enum
  Frequency payFreq2 = Util::convFrequency( atoi( payFreqRec  ));
  slr.setPayFreq(payFreq2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "PayFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

  xml.FindElem("PayLag");
    slr.setPayLag(atoi(MCD_2PCSZ(xml.GetData())));
    // if ( getenv("IRD_DEBUG") == std::string("Yes"))
    	  // logFile << "PayLag :" << (atoi(MCD_2PCSZ(xml.GetData())));

  xml.FindElem("PayMarching");
  const char * payMarchingRec = MCD_2PCSZ(xml.GetData());
    std::string payMarchingR = payMarchingRec;
  const DateMarcher * payMarching2 =  DateMarcher::find(MCD_2PCSZ(xml.GetData()));
  slr.setPayMarching( payMarching2 );
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<"PayMarching is:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

  xml.FindElem("PaymentConvention");
  slr.setPaymentConvention(MCD_2PCSZ(xml.GetData()));
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "PaymentConvention is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("PaymentConversionCurrency");
  const Currency * paymentConversionCurrencyRec =  Currency::find(MCD_2PCSZ(xml.GetData()));
  slr.setPaymentConversionCurrency(paymentConversionCurrencyRec);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "PaymentConversionCurrency is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("PaymentConversionIndex");
  slr.setPaymentConversionIndex(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "PaymentConversionIndex is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("PaymentConversionLag");
  slr.setPaymentConversionLag(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "PaymentConversionLag is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;

  xml.FindElem("PayRollDay");
  slr.setPayRollDay(atoi(MCD_2PCSZ(xml.GetData()))); // this is int man - convert char * to int
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "PayRollDay is:" <<atoi(MCD_2PCSZ(xml.GetData())) << endl;

  xml.FindElem("PayRollWeek");
  const char * payRollWeekRec = MCD_2PCSZ(xml.GetData());
 // DayOfWeek  payRollWeek2(DayOfWeek ((int) payRollWeekRec  ));
  DayOfWeek payRollWeek2 = Util::convDayOfWeek( atoi(  payRollWeekRec   ));
  slr.setPayRollWeek(payRollWeek2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "PayRollWeek is:"<<MCD_2PCSZ(xml.GetData())<< endl;

  xml.FindElem("Position");
  slr.setPosition(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "Position is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("QuoteCalendars");
  const char * quoteCalendarsRec = MCD_2PCSZ(xml.GetData());
  std::set < std::string >quoteCalendars2 ;
  quoteCalendars2.insert(quoteCalendarsRec);
  slr.setQuoteCalendars( quoteCalendars2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "QuoteCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("QuoteLag");
  slr.setQuoteLag(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "QuoteLag is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

  xml.FindElem("RateCutOff");
  slr.setRateCutOff(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "RateCutOff is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

  xml.FindElem("ResetAveraging");
   slr.setResetAveraging(MCD_2PCSZ(xml.GetData()));
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "ResetAveraging is : " << MCD_2PCSZ(xml.GetData()) << endl;


   xml.FindElem("ResetBusDay");
      const BusDayConv * resetBusDay2 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
      slr.setResetBusDay( resetBusDay2);
    // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Reset BusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("ResetConvention");
  	  slr.setResetConvention(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "ResetConvention is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("ResetFreq");
  	  const char * resetFreqRec = MCD_2PCSZ(xml.GetData()) ; // pass the integer from frequency.h enum
  	  Frequency resetFreq2 = Util::convFrequency( atoi(  resetFreqRec  ));
  	  slr.setResetFreq(resetFreq2);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Reset Freq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output


  xml.FindElem("ResetMarching");
     const DateMarcher * resetMarching2 =  DateMarcher::find(MCD_2PCSZ(xml.GetData()));
     slr.setResetMarching( resetMarching2 );
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "Reset Marching is:" <<MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("ResetRollDay");
    slr.setResetRollDay(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Reset RollDay is:"<<(atoi(MCD_2PCSZ(xml.GetData()))) << endl;

  xml.FindElem("ResetRollWeek");
  	  const char * resetRollWeekRec = (MCD_2PCSZ(xml.GetData())) ;
  	  DayOfWeek resetRollWeek1Rec1 = Util::convDayOfWeek( atoi(  resetRollWeekRec   ));
  	  slr.setResetRollWeek(resetRollWeek1Rec1);
   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "Reset RollWeek is:"<<MCD_2PCSZ(xml.GetData())<< endl;

  xml.FindElem("ResetType");
  	  slr.setResetType(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "ResetType is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.FindElem("ScheduleCustomFlag");
  	  slr.setScheduleCustomFlag(atoi(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "ScheduleCustomFlag is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

  xml.FindElem("Spread");
  	  slr.setSpread(atof(MCD_2PCSZ(xml.GetData())));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "Spread is : " << (atof(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

  xml.FindElem("StartDate");
     Date startDateRec(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
     slr.setStartDate(startDateRec);
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "Start Date is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

  xml.FindElem("StartDateRollFlag");
    slr.setStartDateRollFlag(MCD_2PCSZ(xml.GetData()));
  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
    // logFile <<  "StartDateRollFlag is : " << MCD_2PCSZ(xml.GetData()) << endl;

  xml.OutOfElem();
  xml.OutOfElem();
  xml.OutOfElem();

SwapLeg * paySwapLeg = new SwapLeg(
        slp.getAccrualBusDay(),
        slp.getAccrualCalendars(),
        slp.getAccrualFreq(),
        slp.getAccrualMarching(),
        slp.getAccrualRollDay(),
        slp.getAccrualRollWeek(),
        slp.getAmortRollDay(),
        slp.getAmortRollWeek(),
        slp.getAmortAmount(),
        slp.getAmortBusDay(),
        slp.getAmortCalendars(),
        slp.getAmortEndDate(),
		slp.getAmortFreq(),
	    slp.getAmortMarching(),
	    slp.getAmortStartDate(),
		slp.getAmortType(),
		slp.getAveragingMethod(),
		slp.getBackStubDate(),
		slp.getBackStubManualRate(),
		slp.getCompFreq(),
		slp.getCompoundingConv(),
		slp.getCurrency(),
		slp.getDayCount(),
		slp.getDiscountCurve(),
		slp.getEndDate(),
		slp.getEndDateRollFlag(),
		slp.getEndOfMonthIndicator(),
		slp.getFixedQuote(),
		slp.getFrontStubDate(),
		slp.getFrontStubManualRate(),
		slp.getGearFactor(),
		slp.getInitialQuoteCalendars(),
		slp.getInitialQuoteDate(),
		slp.getInitialQuoteLag(),
		slp.getLegNo(),
		slp.getLegType(),
		slp.getMarketIndex(),
		slp.getNotional(),
		slp.getNotionalExchange(),
		slp.getPayBusDay(),
		slp.getPayCalendars(),
		slp.getPayFreq(),
		slp.getPayMarching(),
		slp.getPaymentConvention(),
		slp.getPaymentConversionCurrency(),
		slp.getPaymentConversionIndex(),
		slp.getPaymentConversionLag(),
		slp.getPayLag(),
		slp.getPayRollDay(),
		slp.getPayRollWeek(),
		slp.getPosition(),
		7,
		slp.getQuoteCalendars(),
		slp.getQuoteLag(),
		slp.getRateCutOff(),
		slp.getResetAveraging(),
		slp.getResetBusDay(),
		slp.getResetConvention(),
		slp.getResetFreq(),
		slp.getResetMarching(),
		slp.getResetRollDay(),
		slp.getResetRollWeek(),
		slp.getResetType(),
		slp.getScheduleCustomFlag(),
		slp.getSpread(),
		slp.getStartDate(),
		slp.getStartDateRollFlag()
);

SwapLeg * recvSwapLeg = new SwapLeg(
		slr.getAccrualBusDay(),
		slr.getAccrualCalendars(),
		slr.getAccrualFreq(),
		slr.getAccrualMarching(),
		slr.getAccrualRollDay(),
		slr.getAccrualRollWeek(),
		slr.getAmortRollDay(),
		slr.getAmortRollWeek(),
		slr.getAmortAmount(),
		slr.getAmortBusDay(),
		slr.getAmortCalendars(),
		slr.getAmortEndDate(),
		slr.getAmortFreq(),
	    slr.getAmortMarching(),
	    slr.getAmortStartDate(),
		slr.getAmortType(),
		slr.getAveragingMethod(),
		slr.getBackStubDate(),
		slr.getBackStubManualRate(),
		slr.getCompFreq(),
		slr.getCompoundingConv(),
		slr.getCurrency(),
		slr.getDayCount(),
		slr.getDiscountCurve(),
		slr.getEndDate(),
		slr.getEndDateRollFlag(),
		slr.getEndOfMonthIndicator(),
		slr.getFixedQuote(),
		slr.getFrontStubDate(),
		slr.getFrontStubManualRate(),
		slr.getGearFactor(),
		slr.getInitialQuoteCalendars(),
		slr.getInitialQuoteDate(),
		slr.getInitialQuoteLag(),
		slr.getLegNo(),
		slr.getLegType(),
		slr.getMarketIndex(),
		slr.getNotional(),
		slr.getNotionalExchange(),
		slr.getPayBusDay(),
		slr.getPayCalendars(),
		slr.getPayFreq(),
		slr.getPayMarching(),
		slr.getPaymentConvention(),
		slr.getPaymentConversionCurrency(),
		slr.getPaymentConversionIndex(),
		slr.getPaymentConversionLag(),
		slr.getPayLag(),
		slr.getPayRollDay(),
		slr.getPayRollWeek(),
		slr.getPosition(),
		7, // default 7
		slr.getQuoteCalendars(),
		slr.getQuoteLag(),
		slr.getRateCutOff(),
		slr.getResetAveraging(),
		slr.getResetBusDay(),
		slr.getResetConvention(),
		slr.getResetFreq(),
		slr.getResetMarching(),
		slr.getResetRollDay(),
		slr.getResetRollWeek(),
		slr.getResetType(),
		slr.getScheduleCustomFlag(),
		slr.getSpread(),
		slr.getStartDate(),
		slr.getStartDateRollFlag()
);

paySwapLeg->setFXResetFlag(false); // need to check product type actually
recvSwapLeg->setFXResetFlag(false);

swapTicket->setSwapPayLeg(paySwapLeg);
swapTicket->setSwapRecvLeg(recvSwapLeg);

return 1;
}



int Util::loadCapFloorTicket(CapFloorTicket * capFloorTicket, std::string xmlFileName)
{
	CMarkup xml;

	xml.Load(xmlFileName);

	xml.FindElem("TradeTicket");

	xml.IntoElem();


	  xml.FindElem("AlternateRef" );
	  capFloorTicket->setAlternateRef(xml.GetData());
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile << "AlternateRef is:"<< xml.GetData() << endl;

	  xml.FindElem("BookingType");
	  capFloorTicket->setBookingType(xml.GetData());
	//  if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "BookingType is:" << xml.GetData()<< endl;

	  //return 1;
	  xml.FindElem("CustomerAccount");
	  capFloorTicket->setCustomerAccount(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  	 	 // logFile << "Customer Account is:" << xml.GetData()<< endl;

	  xml.FindElem("EarlyTermDate");
	  Date earlyTermDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	  capFloorTicket->setEarlyTermDate(earlyTermDate);
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "EarlyTermDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

	  xml.FindElem("EarlyTermReason");
	  capFloorTicket->setEarlyTermReason(xml.GetData());
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "EarlyTermReason is:" << xml.GetData()<< endl;

	  xml.FindElem("ExternalSystem");
	  capFloorTicket->setExternalSystem(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "ExternalSystem is:" << xml.GetData()<< endl;

	  xml.FindElem("ExternalRef");
	  capFloorTicket->setExternalRef(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "ExternalRef is:" << xml.GetData()<< endl;

	  xml.FindElem("FirmAccount");
	  capFloorTicket->setFirmAccount(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "FirmAccount is:" << xml.GetData()<< endl;

	  xml.FindElem("FlowStatus");
	  capFloorTicket->setFlowStatus(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "FlowStatus is:" << xml.GetData()<< endl;

	  xml.FindElem("LastModifiedBy");
	  capFloorTicket->setLastModifiedBy(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "LastModifiedBy is:" << xml.GetData()<< endl;

	  xml.FindElem("LastVerifiedBy");
	  capFloorTicket->setLastVerifiedBy(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile << "LastVerifiedBy is:" << xml.GetData()<< endl;

	  xml.FindElem("LegalEntity");
	  capFloorTicket->setLegalEntity(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "LegalEntity is:" << xml.GetData()<< endl;

	  xml.FindElem("Location");
	  capFloorTicket->setLocation(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "Location is:" << xml.GetData()<< endl;

	  xml.FindElem("MatchingStatus");
	  capFloorTicket->setMatchingStatus(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "MatchingStatus is:" << xml.GetData()<< endl;

	  xml.FindElem("TerminationDate");
	  capFloorTicket->setTerminationDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	//if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "TerminationDate is:" << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y")<< endl;

	  xml.FindElem("ModifiedTimeStamp");
	  capFloorTicket->setModifiedTimeStamp(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "VerifiedTimeStamp is:" << xml.GetData()<< endl;

	  xml.FindElem("OperationsRef");
	  capFloorTicket->setOperationsRef(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "OperationsRef is:" << xml.GetData()<< endl;

	  xml.FindElem("OriginalTradeRef");
	  capFloorTicket->setOriginalTradeRef(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "OriginalTradeRef is:" << xml.GetData()<< endl;

	  xml.FindElem("ProductType");
	  capFloorTicket->setProductType(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "ProductType is:" << xml.GetData()<< endl;

	  xml.FindElem("SalesPerson");
	  capFloorTicket->setSalesPerson(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "SalesPerson is:" << xml.GetData()<< endl;

	  xml.FindElem("EffectiveDate");
	  Date effectiveDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	  capFloorTicket->setEffectiveDate(effectiveDate);
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "EffectiveDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

	  xml.FindElem("SubType");
	  capFloorTicket->setSubType(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "SubType is:" << xml.GetData()<< endl;

	  xml.FindElem("TradeDate");
	  Date tradeDate(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	  capFloorTicket->setTradeDate(tradeDate);
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "TradeDate is:" <<Date(MCD_2PCSZ(xml.GetData()), "d/m/Y")<< endl;

	  xml.FindElem("Trader");
	  capFloorTicket->setTrader(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "Trader is:" << xml.GetData()<< endl;

	  xml.FindElem("TradeRef");
	  capFloorTicket->setTradeRef(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 //  // logFile << "TradeRef is:" << xml.GetData()<< endl;

	  xml.FindElem("TradeStatus");
	  capFloorTicket->setTradeStatus(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "TradeStatus is:" << xml.GetData()<< endl;

	  xml.FindElem("TradeType");
	  capFloorTicket->setTradeType(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "TradeType is:" << xml.GetData()<< endl;

	  xml.FindElem("VerifiedTimeStamp");
	  capFloorTicket->setVerifiedTimeStamp(xml.GetData());
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	// logFile << "VerifiedTimeStamp is:" << xml.GetData()<< endl;

	  xml.FindElem("WashAccount");
	  capFloorTicket->setWashAccount(xml.GetData());
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  	 // logFile << "WashAccount is:  " << xml.GetData()<< endl;

	xml.FindElem("CapFloorTicket");
	xml.IntoElem();

	 xml.FindElem("AmortAmount");
	 capFloorTicket->setAmortAmount(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 	 // logFile << "AmortAmount is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

	 xml.FindElem("AmortFreq");
	 const char * amortFreqPay = MCD_2PCSZ(xml.GetData()) ;
	 Frequency amortFreq1 = Util::convFrequency( atoi(  amortFreqPay  ));
	 capFloorTicket->setAmortFreq(amortFreq1);
	 // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 	 // logFile <<"AmortFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

	  xml.FindElem("AmortType");
	  capFloorTicket->setAmortType(MCD_2PCSZ(xml.GetData()));
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  	 // logFile<<  "AmortType  is : " << MCD_2PCSZ(xml.GetData()) << endl;

	xml.FindElem("AmortRollDay");
	capFloorTicket->setAmortRollDay(atoi(MCD_2PCSZ(xml.GetData())));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
		 // logFile << "AmortRollDay is:"<<(atoi(MCD_2PCSZ(xml.GetData()))) << endl;

	xml.FindElem("AmortRollWeek");
	  const char * amortRollWeekPay = (MCD_2PCSZ(xml.GetData())) ;
	  //DayOfWeek  amortRollWeek1(DayOfWeek ((int) amortRollWeekPay  ));
	  DayOfWeek amortRollWeek1 = Util::convDayOfWeek( atoi(  amortRollWeekPay   ));
	  capFloorTicket->setAmortRollWeek(amortRollWeek1);
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "AmortRollWeek is:"<<MCD_2PCSZ(xml.GetData()) << endl;

	xml.FindElem("AmortBusDay");
	  const char * amortBusDayPay = MCD_2PCSZ(xml.GetData());
	   std::string amortBusDayP = amortBusDayPay;
	   const BusDayConv * amortBusDay1 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
	   capFloorTicket->setAmortBusDay( amortBusDay1);
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "AmortBusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;

	xml.FindElem("AmortCalendars");
	  const char * amortCalendarsPay = MCD_2PCSZ(xml.GetData()) ;
	  std::set < std::string > amortCalendars1;
	  amortCalendars1.insert(amortCalendarsPay);
	  capFloorTicket->setAmortCalendars( amortCalendars1);
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "AmortCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

	     xml.FindElem("AmortStartDate");
	     Date amortStartDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	     capFloorTicket->setAmortStartDate(amortStartDatePay);
	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "AmortStartDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

	  	  xml.FindElem("AmortMarching");
	  	  const DateMarcher * amortMarchingCf =  DateMarcher::find(MCD_2PCSZ(xml.GetData()));
	  	capFloorTicket->setAmortMarching( amortMarchingCf );
	  //	if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  	  // logFile << "AmortMarching :" << MCD_2PCSZ(xml.GetData());


	xml.FindElem("AmortEndDate");
	  Date amortEndDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	  capFloorTicket->setAmortEndDate(amortEndDatePay);
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "AmortEndDate  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

	  xml.FindElem("PricingMethod");
	  capFloorTicket->setPricingMethod(MCD_2PCSZ(xml.GetData()));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "ResetAveraging is : " << MCD_2PCSZ(xml.GetData()) << endl;

	     xml.FindElem("BackStubDate");
	     Date backStubDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	     capFloorTicket->setBackStubDate(backStubDatePay);
	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "Back Stub Date  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

	     xml.FindElem("BackStubManualRate");
	     capFloorTicket->setBackStubManualRate(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "BackStubManualRate is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

	     xml.FindElem("BuyFlag");
	     capFloorTicket->setBuyFlag(MCD_2PCSZ(xml.GetData()));
	   	 // logFile <<  "buyFlag  is : " << MCD_2PCSZ(xml.GetData()) << endl;

	   	 xml.FindElem("CapFloorType");
	   	capFloorTicket->setCapFloorType(MCD_2PCSZ(xml.GetData()));
	   //	if ( getenv("IRD_DEBUG") == std::string("Yes"))
	   		// logFile <<  "CapFloorType  is : " << MCD_2PCSZ(xml.GetData()) << endl;


	    xml.FindElem("Currency");
	   	     const Currency * currencyCf =  Currency::find(MCD_2PCSZ(xml.GetData()));
	   	     capFloorTicket->setCurrency(currencyCf);
	   	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	   	  	 // logFile <<  "Currency is : " << MCD_2PCSZ(xml.GetData()) << endl;

	     xml.FindElem("DayCount"); // change in xml to DayCount
	     DayCountConv * dayCountConv =  DayCountConv::find(MCD_2PCSZ(xml.GetData()));
	     capFloorTicket->setDayCount( dayCountConv );

	     // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	     	 // logFile << "Day Count is : " <<  MCD_2PCSZ(xml.GetData()) << endl;

	     xml.FindElem("DiscountCurve");
	     capFloorTicket->setDiscountCurve(MCD_2PCSZ(xml.GetData()));
	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "DiscountCurve is : " << MCD_2PCSZ(xml.GetData()) << endl;

	     xml.FindElem("EndDate");
	     Date endDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	     capFloorTicket->setEndDate(endDatePay);
	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "End Date  is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

	     xml.FindElem("EndDateRollFlag");
	     capFloorTicket->setEndDateRollFlag(MCD_2PCSZ(xml.GetData()));
	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "EndDateRollFlag is : " << MCD_2PCSZ(xml.GetData()) << endl;

	     xml.FindElem("FrontStubDate");
	     Date frontStubDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	     capFloorTicket->setFrontStubDate(frontStubDatePay);
	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "FrontStubDate is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

	     xml.FindElem("FrontStubManualRate");
	     capFloorTicket->setFrontStubManualRate(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "FrontStubManualRate is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

	     xml.FindElem("GearFactor");
	     capFloorTicket->setGearFactor(atof(MCD_2PCSZ(xml.GetData()))); //convert char * to double
	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "GearFactor is:"<<(atof(MCD_2PCSZ(xml.GetData()))) << endl;

	     xml.FindElem("InitialQuoteCalendars");
		 const char * initialQuoteCalendarsPay = MCD_2PCSZ(xml.GetData()) ;
		 std::set < std::string > initialQuoteCalendars1;
		 initialQuoteCalendars1.insert(initialQuoteCalendarsPay);
		 capFloorTicket->setInitialQuoteCalendars( initialQuoteCalendars1);

		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
		 	  // logFile << "InitialQuoteCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

		 xml.FindElem("InitialQuoteDate");
		 Date initialQuoteDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
		 capFloorTicket->setInitialQuoteDate(initialQuoteDatePay);
		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
		 	  // logFile <<  "InitialQuoteDate is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

		 xml.FindElem("InitialQuoteLag");
		 capFloorTicket->setInitialQuoteLag(atoi(MCD_2PCSZ(xml.GetData()))); // this is int man - convert char * to int

		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
		 	  // logFile << "InitialQuoteLag is:" <<atoi(MCD_2PCSZ(xml.GetData())) << endl;

		 xml.FindElem("LegNo");
		 capFloorTicket->setLegNo(atoi(MCD_2PCSZ(xml.GetData()))); // this is int man - convert char * to int

		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
		 	 // logFile << "LegNo is:" <<atoi(MCD_2PCSZ(xml.GetData())) << endl;

		 xml.FindElem("MarketIndex");
		 capFloorTicket->setMarketIndex(MCD_2PCSZ(xml.GetData()));

		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
		 	  // logFile <<  "MarketIndex is : " << MCD_2PCSZ(xml.GetData()) << endl;

		 xml.FindElem("Notional");
		 capFloorTicket->setNotional(atof(MCD_2PCSZ(xml.GetData())));
		  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
		 	 // logFile << "Notional for first leg is :" << atoi(MCD_2PCSZ(xml.GetData())) << endl;

	xml.FindElem("PayBusDay");
	  const char * payBusDayPay = MCD_2PCSZ(xml.GetData());
	   std::string payBusDayP = payBusDayPay;
	  const BusDayConv * payBusDay1 =  BusDayConv::find(MCD_2PCSZ(xml.GetData()));
	  capFloorTicket->setPayBusDay( payBusDay1 );
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "PayBusDay is:" <<MCD_2PCSZ(xml.GetData()) << endl;

	xml.FindElem("PayCalendars");
	  const char * payCalendarsPay = MCD_2PCSZ(xml.GetData()) ;
	  std::set < std::string > payCalendars;
	   payCalendars.insert(payCalendarsPay);
	   capFloorTicket->setPayCalendars( payCalendars);
	   capFloorTicket->getDayCount()->setCalendar(payCalendars); // needed for BUS360/BUS252
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "payCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

	xml.FindElem("PayFreq");
	  const char * payFreqPay = MCD_2PCSZ(xml.GetData()) ;
	  Frequency payFreq1 = Util::convFrequency( atoi(  payFreqPay  ));
	  capFloorTicket->setPayFreq(payFreq1);
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "PayFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

	xml.FindElem("PayMarching");
	  const char * payMarchingPay = MCD_2PCSZ(xml.GetData());
	    std::string payMarchingP = payMarchingPay;
	  const DateMarcher * payMarching1 =  DateMarcher::find(MCD_2PCSZ(xml.GetData()));
	  capFloorTicket->setPayMarching( payMarching1 );
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "PayMarching is:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output

	  xml.FindElem("PayLag");
	  capFloorTicket->setPayLag(atoi(MCD_2PCSZ(xml.GetData())));
	   // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  	  // logFile <<  "PayLag is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;


	  xml.FindElem("PayRollDay");
	  	capFloorTicket->setPayRollDay(atoi(MCD_2PCSZ(xml.GetData()))); // this is int man - convert char * to int
	  //	if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "PayRollDay is:" <<atoi(MCD_2PCSZ(xml.GetData())) << endl;

	  	  xml.FindElem("PayRollWeek");
	  	  const char * payRollWeekPay = (MCD_2PCSZ(xml.GetData())) ;
	  	  //DayOfWeek  payRollWeek1(DayOfWeek ((int) payRollWeekPay  ));
	  	  DayOfWeek payRollWeek1 = Util::convDayOfWeek( atoi(  payRollWeekPay   ));
	  	  capFloorTicket->setPayRollWeek(payRollWeek1);
	 // 	if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "PayRollWeek is:"<<MCD_2PCSZ(xml.GetData())<< endl;

	  xml.FindElem("QuoteCalendars");
	  const char * quoteCalendarsPay = MCD_2PCSZ(xml.GetData());
	  std::set < std::string >quoteCalendars1 ;
	  quoteCalendars1.insert(quoteCalendarsPay);
	  capFloorTicket->setQuoteCalendars( quoteCalendars1);
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "QuoteCalendars is:" <<MCD_2PCSZ(xml.GetData()) << endl;

	xml.FindElem("QuoteLag");
	capFloorTicket->setQuoteLag(atoi(MCD_2PCSZ(xml.GetData())));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  // logFile <<  "QuoteLag is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

	  xml.FindElem("ResetAveraging");
	  capFloorTicket->setResetAveraging(MCD_2PCSZ(xml.GetData()));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "ResetAveraging is : " << MCD_2PCSZ(xml.GetData()) << endl;

	xml.FindElem("ResetConvention");
	capFloorTicket->setResetConvention(MCD_2PCSZ(xml.GetData()));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "ResetConvention is : " << MCD_2PCSZ(xml.GetData()) << endl;

	xml.FindElem("ResetFreq");
	  const char * resetFreqPay = MCD_2PCSZ(xml.GetData()) ;
	  Frequency resetFreq1 = Util::convFrequency( atoi(  resetFreqPay  ));
	  capFloorTicket->setResetFreq(resetFreq1);
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile << "ResetFreq:"<<MCD_2PCSZ(xml.GetData()) << endl; // check the output


		xml.FindElem("ResetType");
		capFloorTicket->setResetType(MCD_2PCSZ(xml.GetData()));
		// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "ResetType is : " << MCD_2PCSZ(xml.GetData()) << endl;


	xml.FindElem("ScheduleCustomFlag");
	capFloorTicket->setScheduleCustomFlag(atoi(MCD_2PCSZ(xml.GetData())));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "ScheduleCustomFlag is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

	xml.FindElem("Spread");
	capFloorTicket->setSpread(atof(MCD_2PCSZ(xml.GetData())));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "Spread is : " << (atof(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

	xml.FindElem("CapStartDate");
	  Date startDatePay(Date(MCD_2PCSZ(xml.GetData()), "d/m/Y"));
	  capFloorTicket->setCapStartDate(startDatePay);
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	  	  // logFile <<  "Cap StartDate is : " << Date(MCD_2PCSZ(xml.GetData()), "d/m/Y") << endl;

	xml.FindElem("StartDateRollFlag");
	capFloorTicket->setStartDateRollFlag(MCD_2PCSZ(xml.GetData()));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "StartDateRollFlag is : " << MCD_2PCSZ(xml.GetData()) << endl;

	  xml.FindElem("Strike");
	  capFloorTicket->setStrike(atof(MCD_2PCSZ(xml.GetData())));
	  	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "Strike is : " << (atof(MCD_2PCSZ(xml.GetData()))) << endl;//convert char * to int

	  xml.FindElem("CfSubType");
	  capFloorTicket->setCFSubType(MCD_2PCSZ(xml.GetData()));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile <<  "CfSubType is : " << MCD_2PCSZ(xml.GetData()) << endl;


	  xml.FindElem("VolId");
	  capFloorTicket->setVolId(MCD_2PCSZ(xml.GetData()));
	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile <<  "VolId is : " << MCD_2PCSZ(xml.GetData()) << endl;

	  xml.FindElem("PaymentConvention");
	  	capFloorTicket->setPaymentConvention(MCD_2PCSZ(xml.GetData()));
	  	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "PaymentConvention is : " << MCD_2PCSZ(xml.GetData()) << endl;

	  	xml.FindElem("PaymentConversionCurrency");
	  	  const Currency * paymentConversionCurrency1 =  Currency::find(MCD_2PCSZ(xml.GetData()));
	  	  capFloorTicket->setPaymentConversionCurrency(paymentConversionCurrency1);
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "PaymentConversionCurrency is : " << MCD_2PCSZ(xml.GetData()) << endl;

	  	xml.FindElem("PaymentConversionIndex");
	  	capFloorTicket->setPaymentConversionIndex(MCD_2PCSZ(xml.GetData()));
	  // if ( getenv("IRD_DEBUG") == std::string("Yes"))
	//  // logFile <<  "PaymentConversionIndex is : " << MCD_2PCSZ(xml.GetData()) << endl;

	  	xml.FindElem("PaymentConversionLag");
	  	capFloorTicket->setPaymentConversionLag(atoi(MCD_2PCSZ(xml.GetData())));
	  	// if ( getenv("IRD_DEBUG") == std::string("Yes"))
	 // logFile <<  "PaymentConversionLag is : " << (atoi(MCD_2PCSZ(xml.GetData()))) << endl;



	  xml.OutOfElem();// out of trade ticket
	  xml.OutOfElem(); // out of CapFloor Ticket


	  return 1;

}

int Util::loadSwapTicketList(SwapTicketList & swapTicketList )
{
	ifstream xmlFiles("/home/vishist/xmls.lis");
	std::string xmlFileName;

	if ( xmlFiles.is_open() )
	{

		while ( xmlFiles.good() && ! xmlFiles.eof() )
		{

			getline(xmlFiles, xmlFileName);

			if ( xmlFileName == "" )
				break;

		SwapTicket * swapTicket = new SwapTicket();
			  logFile << " loading ... " << xmlFileName << endl;

			if ( Util::loadSwapTicket(swapTicket, xmlFileName ))
			{

				swapTicketList.push_back(swapTicket);
			}

		}

		xmlFiles.close();
	}


	return 1;
}

int Util::loadSwapOptionList(SwapOptionList & swapOptionList )
{
	ifstream xmlSWOFiles("/home/vishist/xmlsSWO.lis");
		std::string xmlSWOFileName;

		if ( xmlSWOFiles.is_open() )
		{

			while ( xmlSWOFiles.good() && ! xmlSWOFiles.eof() )
			{

				getline(xmlSWOFiles, xmlSWOFileName);

				if ( xmlSWOFileName == "" )
					break;

			SwapOption * swapOption = new SwapOption();
				  logFile << " loading ... " << xmlSWOFileName << endl;

				 SwapTicket * swapTicket = new SwapTicket();

				 if ( ! Util::loadSwapTicket(swapTicket, xmlSWOFileName ) )
				 	  logFile << " Swap Ticket can be created - problem with swapoption XML " << endl;

				if ( Util::loadSwapOption(swapOption, xmlSWOFileName ))
				{
					swapOption->setSwapTicket(swapTicket);
					swapOptionList.push_back(swapOption);
				}

			}

			xmlSWOFiles.close();
		}


		return 1;
}

int Util::loadFraTicketList(FraTicketList & fraTicketList )
{
	ifstream xmlFRAFiles("/home/vishist/xmlsFRA.lis");
	std::string xmlFRAFileName;

	if ( xmlFRAFiles.is_open() )
	{

		while ( xmlFRAFiles.good() && ! xmlFRAFiles.eof() )
		{

			getline(xmlFRAFiles, xmlFRAFileName);

			if ( xmlFRAFileName == "" )
				break;

		FraTicket * fraTicket = new FraTicket();
			 logFile << " loading ... " << xmlFRAFileName << endl;

			if ( Util::loadFraTicket(fraTicket, xmlFRAFileName ))
			{

				fraTicketList.push_back(fraTicket);
			}

		}

		xmlFRAFiles.close();
	}


	return 1;
}

int Util::loadCapFloorTicketList(CapFloorTicketList & capFloorTicketList )
{
        ifstream xmlCFFiles("/home/vishist/xmlsCF.lis");
        std::string xmlCFFileName;

        if ( xmlCFFiles.is_open() )
        {

                while ( xmlCFFiles.good() && ! xmlCFFiles.eof() )
                {

                        getline(xmlCFFiles, xmlCFFileName);

                        if ( xmlCFFileName == "" )
                                break;

                        CapFloorTicket * capFloorTicket = new CapFloorTicket();
                         logFile << " loading ... " << xmlCFFileName << endl;

                        if ( Util::loadCapFloorTicket(capFloorTicket, xmlCFFileName ))
                        {

                                capFloorTicketList.push_back(capFloorTicket);
                        }

                }

                xmlCFFiles.close();
        }


        return 1;
}

}
#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include "irdString.h"
#include "frequency.h"
#include "swapTicket.h"
#include "currency.h"
#include "moneyMkt.h"
#include "swapOption.h"
#include "fraTicket.h"
#include "capFloorTicket.h"



using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class Util {

public:

static int genSeqNo(String seqType);
static Frequency convFrequency(int i );
static DayOfWeek convDayOfWeek(int j );
static Period convPeriod(String period);
//static int loadSwapTicket(SwapTicket & swapTicket);

static Date getValuationDate() { return VALUATION_DATE; };
static Date getCurveDate(){ return CURVE_DATE; };

static void setValuationDate(Date valDate) {  VALUATION_DATE = valDate; };
static void setCurveDate(Date curveDate) { CURVE_DATE = curveDate; };

//static  Date VALUATION_DATE ;
//static Date CURVE_DATE ;

static int loadSwapTicket(String dealId);
static int loadSwapTicket(int noOfDeals);

static int loadSwapTicket(SwapTicket * swapTicket, std::string xmlFileName = 0 );
static int loadSwapTicketList(SwapTicketList & swapTicketList);


static int loadSwapOption(SwapOption * swapOption, std::string xmlFileName = 0 );
static int loadSwapOptionList(SwapOptionList & swapOptionList);

static int loadFraTicket(FraTicket * fraTicket, std::string xmlFileName = 0 );
static int loadFraTicketList(FraTicketList & fraTicketList);


static int loadCapFloorTicket(CapFloorTicket * capFloorTicket, std::string xmlFileName = 0 );
static int loadCapFloorTicketList(CapFloorTicketList & capFloorTicketList);

//static int loadPremiums(Premiums * premiums, std::string xmlFileName = 0);

static int loadMoneyMktList(MoneyMktList & moneyMktList);
static int loadCurrencyList(CurrencyList & currencyList);

private:

static Date CURVE_DATE ;
static Date VALUATION_DATE ;

};


}
#endif // UTIL_H

#ifndef SWAPOPTION_H_
#define SWAPOPTION_H_

#include<iostream>
#include<string>
#include "irdString.h"
#include "date.h"
#include "busDayConv.h"
#include "swapTicket.h"
#include "tradeTicket.h"
#include "swapLeg.h"


using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class SwapTicket; // SwapOption got SwapTicket in it
class SwapOption; // forward declare

typedef std::list < SwapOption * > SwapOptionList;


class SwapOption
{

public:


SwapOption();

SwapOption (
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
SwapTicket * 	swapTicket );

//SwapOption * getSwapOption();

//void setSwapOption(SwapOption * swapOption)

//SwapLegList getSwapLegList() {return _swapLegList;}

virtual ~SwapOption();

String getBuyFlag (){return _buyFlag;}
void setBuyFlag(String buyFlag) { _buyFlag =	buyFlag; }

String getExerciseFlag (){return _exerciseFlag;}
void setExerciseFlag(String exerciseFlag) { _exerciseFlag =	exerciseFlag; }
      
String getExerciseType (){return _exerciseType;}    
void setExerciseType(String exerciseType) { _exerciseType =	exerciseType; }

Date getExpiryDate(){return _expiryDate;}
void setExpiryDate(Date expiryDate){ _expiryDate = expiryDate;}

String getOptionStyle(){return _optionStyle;}
void setOptionStyle(String optionStyle){ _optionStyle = optionStyle;}

String getOptionType(){return _optionType;}
void setOptionType(String optionType){ _optionType = optionType;}

String getPosition(){return _position;}
void setPosition(String position){ _position = position; }

String getPricingMethod (){return _pricingMethod;}
void setPricingMethod (String pricingMethod ){ _pricingMethod = pricingMethod ;}

double getStrike(){return _strike;}
void setStrike(double strike){ _strike = strike;}

Date getSwapEndDate(){return _swapEndDate;}
void setSwapEndDate(Date swapEndDate){ _swapEndDate = swapEndDate;}

int getSwapLag(){return _swapLag;}
void setSwapLag(int swapLag){ _swapLag = swapLag;}

const BusDayConv * getSwapLagBusDay(){return _swapLagBusDay;}
void setSwapLagBusDay(const BusDayConv * swapLagBusDay){ _swapLagBusDay = swapLagBusDay;}

String getSwapRef(){return _swapRef;}
void setSwapRef(String swapRef){ _swapRef = swapRef;}

Date getSwapStartDate(){return _swapStartDate;}
void setSwapStartDate(Date swapStartDate){ _swapStartDate = swapStartDate;}

String getVolId (){return _volId;}
void setVolId (String volId){ _volId = volId ;}

SwapTicket * getSwapTicket() { return _swapTicket; }
void setSwapTicket(SwapTicket * swapTicket) { _swapTicket = swapTicket;}


bool genAllCashFlows();

//std::string serialize();

protected:

String		_buyFlag;
String		_exerciseFlag; // Yes or No
String 		_exerciseType; // CASH OR PHYSICAL
Date 		_expiryDate;
String 		_optionStyle; // european or american or bermudian
String 		_optionType; // option to enter or option to cancel
String 		_position; // PayFixed or RecFixed
String		_pricingMethod; // closed Form, Tree, Mc 3000:10000:40000 etc
double		_strike;
Date 		_swapEndDate;
int 		_swapLag;
const BusDayConv * _swapLagBusDay;
String 		_swapRef; // appear only if exercised and EXERCISE type is PHYSICAL
Date 		_swapStartDate;
String		_volId;
SwapTicket *  _swapTicket;


};

}

#endif // SWAPOPTION_H_

#ifndef SWAPTICKET_H
#define SWAPTICKET_H

#include "tradeTicket.h"
#include "swapLeg.h"
#include "fxReset.h"


#include <list>
#include <set>

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class SwapTicket; // forward declare

typedef std::list < SwapLeg * > SwapLegList;
typedef std::list < SwapTicket * > SwapTicketList;

class SwapTicket : public TradeTicket {

public:

SwapTicket();

virtual ~SwapTicket();

// SwapTicket(TradeTicket * tt,SwapLegList * swapLegList);

SwapTicket (
String   		alternateRef,
String     		bookingType,
String     		customerAccount,
Date       		earlyTermDate,
String     		earlyTermReason,
String     		externalSystem,
String     		externalRef,
String     		firmAccount,
String     		flowStatus,
String     		lastModifiedBy,
String     		lastVerifiedBy,
String      	legalEntity,
String      	location,
String      	matchingStatus,
Date        	terminationDate,
String     		modifiedTimeStamp,
String     		operationsRef,
String     		originalTradeRef,
String      	productType,
String      	salesPerson,
Date            effectiveDate,
String       	subType,
Date        	tradeDate,
String        	trader,
String      	tradeRef,
String  		tradeRemarks,
String      	tradeStatus,
String      	tradeType,
double    		tradeVersion,
String    		verifiedTimeStamp,
String      	washAccount
);

SwapLeg * getFirstFloatLeg();
SwapLeg * getFirstFixedLeg();

SwapLeg * getFirstPayLeg();
SwapLeg * getFirstReceiveLeg();

SwapLegList getSwapLegList() {return _swapLegList;}


void setSwapPayLeg(SwapLeg * swapLeg);
void setSwapRecvLeg(SwapLeg * swapLeg);

int getNoOfLegs() {return _noOfLegs;}
void setNoOfLegs(int noOfLegs) {_noOfLegs = noOfLegs;}

String getSwapStatus() {return _swapStatus;}
void setSwapStatus(String swapStatus) { _swapStatus = swapStatus;}

String getSwaptionRef() { return _swaptionRef;}
void setSwaptionRef(String swaptionRef) { _swaptionRef = swaptionRef;}

FXReset * getFXReset() { return _fxReset; };
void setFXReset(FXReset * fxReset) { _fxReset = fxReset; };

SwapLeg * getFXResetLeg();

bool genFXResetSchedule();

bool genAllCashFlows();

double calculateNetPV();
double calcAdjustmentPV();

double calculateTotalPV();

double calculateBERate(); // calculate break even rate for this deal - also called risk free rate for swaptions

std::string serialize();
//std::string deserialize();

friend class SwapLeg;

protected:

int 			_noOfLegs;  // no of legs
String			_swapStatus; // active or non activated swap
SwapLegList 	_swapLegList;
String 			_swaptionRef;
FXReset		*	_fxReset;

};


}
#endif //SWAPTICKET_H

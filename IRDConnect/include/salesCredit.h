#ifndef SALESCREDIT_H
#define SALESCREDIT_H

#include "irdString.h"
#include "date.h"
#include "currency.h"

using namespace IRDConnect;
using namespace std;

namespace IRDConnect
{

class SalesCredit
{

public:

SalesCredit();

~SalesCredit();

SalesCredit
(
		String				evType, // FLOW/OVERRIDE/ORDER/AXE/OTHER
		Date				evDate, // usually today
		double				amount,
		const Currency * 	ccy,
		String 				firmAccount, // optional  - if diff from trade book
		String				customerAccount, // optional - if diff from trade customer
		String				salesPerson,
		String				comment
);


String getEVType() { return _evType; };
void setEVType( String evType ) { _evType = evType; };

Date getEVDate() { return _evDate; };
void setEVDate( Date evDate ) { _evDate = evDate; };

double getAmount() { return _amount; };
void setAmount( double amount ) { _amount = amount; };

String getFirmAccount() { return _firmAccount; };
void setFirmAccount( String firmAccount ) { _firmAccount = firmAccount; };

String getCustomerAccount() { return _customerAccount; };
void setCustomerAccount( String customerAccount ) { _customerAccount = customerAccount; };

String getSalesPerson() { return _salesPerson; };
void setSalesPerson( String salesPerson ) { _salesPerson = salesPerson; };

String getComment() { return _comment; };
void setComment( String comment ) { _comment = comment; };

const Currency * getCurrency() { return _ccy; };
void setCurrency( const Currency * ccy ) { _ccy = ccy; };

private:


String				_evType; // FLOW/OVERRIDE/ORDER/AXE/OTHER
Date				_evDate; // usually today
double				_amount;
const Currency * 	_ccy;
String 				_firmAccount; // optional  - if diff from trade book
String				_customerAccount; // optional - if diff from trade customer
String				_salesPerson;
String				_comment;




};



}

#endif // end of SALESCREDIT_H

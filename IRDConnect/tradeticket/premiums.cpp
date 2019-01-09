#include  <iostream>
#include  "premiums.h"

using  namespace  IRDConnect;

Premiums::Premiums (
double  	amount,
const Currency *   	currency,
Date   		paymentDate,
String  	payReceive,
double    	premiumBP,
String    	premiumType
)

{
_amount			=	amount; // premium
_currency		=	currency;
_paymentDate	=	paymentDate;
_payReceive		=	payReceive;
_premiumBP		=	premiumBP;
_premiumType	=	premiumType; // Basis Point or Amount

}

Premiums::~Premiums()
{
	//do nothing
}


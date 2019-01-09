#ifndef BOND_H
#define BOND_H
#include <iostream>
#include "irdString.h"
#include "date.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class   Bond
{
public:

Bond (
String   bond,
String   currency,
String   issuer,
String   market,
Date     maturityDate,
double   yield );

~Bond();

String    getBond () {return _bond ;}
void setBond(String bond) { _bond = bond;}

String  getCurrency () {return _currency;}
void    setCurrency(String currency) {_currency = currency;}

String  getIssuer () {return _issuer;}
void setIssuer(String issuer) { _issuer = issuer;}

String getMarket() {return _market;}
void setMarket(String market) { _market = market;}

Date  getMaturityDate () {return _maturityDate;}
void  setMaturityDate(Date  maturityDate)  { _maturityDate = maturityDate ;}

double getYield () {return _yield;}
void setYield (double yield) { _yield = yield;}

protected:

 String     _bond;
 String     _currency;
 String     _issuer;
 String     _market;
 Date       _maturityDate;
 double     _yield;
 
 
 
};

}

#endif // BOND_H end


        
           

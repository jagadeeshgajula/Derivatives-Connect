/*
 * money.h
 *
 *  Created on: 26-Sep-2010
 *      Author: vishist
 */

#ifndef MONEY_H_
#define MONEY_H_


#include<iostream>
#include "date.h"
#include "roundingConv.h"
#include "currency.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class Money {
public:
	// an FX function must be registered via setFXFunction before the
	// convert() mbr function will work.

	Money( double amount = 0, const Currency *currency = 0 ) { _amount=amount;_currency=currency; };
	Money( const Money &money ) { _amount=money._amount;_currency=money._currency; };

	~Money() {};

	Money &operator=( const Money &money ) { _amount=money._amount;_currency=money._currency;return *this; };


	Money &operator+=( const Money& money );
	Money &operator-=( const Money& money );
	Money &operator*=(double qty);
	Money &operator/=(double qty);
	Money operator-() const;
	Money operator+( const Money& money ) const;
	Money operator-( const Money& money ) const;
	Money operator*( double qty ) const;

	double getAmount() const { 	return _amount; };
	const Currency *getCurrency() const { return _currency; };


	void setCurrency( const Currency * ccy ) { _currency = ccy; };


	double getRoundedAmount() const { return calcRoundedAmount(_amount); };


	void round() { _amount = calcRoundedAmount(_amount); };



	Money & setAmount( double amount ) { _amount=amount;return *this; };



	Money convert( const Currency * currency ) const;
	Money convert( const Currency * currency, Date valueDate ) const;

private:
	static double defaultFXFunction(const Currency *fromCcy,
		const Currency *toCcy);

	double calcRoundedAmount(double amt) const;


	double _amount;
	const Currency *_currency;
};


inline Money
operator*(double qty, const Money& money)
{

	return money * qty;
}

std::ostream & operator << (std::ostream& os, const Money& money);

}

#endif /* MONEY_H_ */

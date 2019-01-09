/*
 * IMMDates.cpp
 *
 *  Created on: 18-Sep-2010
 *      Author: vishist
 */

#include "immDates.h"
#include <assert.h>
#include "rollDayConv.h"

#include "currency.h"

namespace IRDConnect {

using namespace std;

Date
thirdIMMDay( Year year, Month month, const Currency * ccy )
{

	int immDayOfWk;
	int immDayOffset;


		immDayOfWk = DayOfWeek(WED);
		immDayOffset = 3;

	Date date( Day(1), month, year );
	const int occurrence = 3;
	const int daysInWeek = 7;
	const Weekday dow = date.weekday();
	const int correction = ( immDayOfWk == dow) ?
		daysInWeek : (immDayOffset + dow) % 7;
	// Calculate third wednsday first then get third monday
//	if (ccy != cadCcy)
		date = date + ( occurrence * daysInWeek - correction );
	//else
		//date = date + ( occurrence * daysInWeek - correction - 2);
	//assert( date.dayOfWeek() == immDayOfWk );

	return date;
}

Date nthWeekday( Year year, Month month, int dayOfWeek, int occurence )
{
  // Returns the n-th occurence of "day of week" in the month


  Date target( year, month, Day( 1 ) );

  if( dayOfWeek < DayOfWeek(SUN) || dayOfWeek > DayOfWeek(SAT) ||
      occurence < 1 || occurence > 5 ) {
    // What day ?
    return target;
  }

  // The 1st of the month is on a ...
  const Weekday dow = target.weekday();
  if(dow <= dayOfWeek) {
    target = target + (7*(occurence-1)+dayOfWeek-dow);
  }
  else {
    target = target + (7*occurence+dayOfWeek-dow);
  }

  return target;
}

//----------------------------------------------------------------------

static int
isIMMMonth( const Month month )
{
	switch( month ) {
	case March:
	case June:
	case September:
	case December:
		return 1;
	default:
		break;
	}
	return 0;
}

//----------------------------------------------------------------------

static Date
immDate(
const Year			year,
const Month			month,
const BusDayConv	* bdc,
const Calendar		* cal,
const Currency		* ccy )
{
	assert( isIMMMonth( month ) );
	const Date tw = thirdIMMDay( year, month, ccy );
	const Date imm = bdc ? bdc -> adjustToBusDay( tw, *cal ) : tw;
	return imm;
}

//----------------------------------------------------------------------

int
isIMMDate(
const Date			& date,
const BusDayConv	* bdc,
const Calendar		* cal,
const Currency		* ccy )
{

	const Month month = date.month();
	if ( !isIMMMonth( month ) )
		return 0;
	const Year year = date.year();
	return date == immDate( year, month, bdc, cal, ccy );
}

Date
nextIMMDate(
const Date			& date,
const BusDayConv	* bdc,
const Calendar		* cal,
const Currency 		* ccy )
{

	const Year year = date.year();
	const Month month = date.month();

	switch ( month ) {
	default:
		assert( 0 );

	case January:
    case February:
		return immDate( year, March, bdc,cal, ccy );

    case April:
    case May:
		return immDate( year, June, bdc, cal, ccy );

    case July:
    case August:
		return immDate( year, September, bdc, cal, ccy );

    case October:
    case November:
		return immDate( year, December, bdc, cal, ccy );

    case March:
    case June:
    case September:
    case December: {
		assert( isIMMMonth( month ) );
		const Date imm = immDate( year, month, bdc, cal, ccy );
		if ( date < imm )
			return imm;
		if ( month == December )
			return immDate( year + 1, March, bdc, cal, ccy );
		return immDate( year, (Month)(month + 3), bdc, cal, ccy );
	}

	}
}

Date
prevIMMDate(
const Date			& date,
const BusDayConv	* bdc,
const Calendar		* cal,
const Currency		* ccy )
{

	const Year year = date.year();
	const Month month = date.month();

	switch ( month ) {
	default:
		assert( 0 );

	case January:
    case February:
		return immDate( year - 1, December, bdc, cal, ccy );

    case April:
    case May:
		return immDate( year, March, bdc, cal, ccy );

    case July:
    case August:
		return immDate( year, June, bdc, cal, ccy );

    case October:
    case November:
		return immDate( year, September, bdc, cal, ccy );

    case March:
    case June:
    case September:
    case December: {
		assert( isIMMMonth( month ) );
		const Date imm = immDate( year, month, bdc, cal, ccy );
		if ( imm < date )
			return imm;
		if ( month == March)
			return immDate( year - 1, December, bdc, cal, ccy );
		return immDate( year, (Month)(month - 3), bdc, cal, ccy );
	}

	}
}
}

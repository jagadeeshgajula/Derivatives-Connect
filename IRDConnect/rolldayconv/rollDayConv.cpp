/*
 * RollDayConv.cpp
 *
 *  Created on: 16-Sep-2010
 *      Author: vishist
 */
#include "rollDayConv.h"

using namespace std;
using namespace IRDConnect;

RollDayConv::~RollDayConv()
{
	// nothing needs to be done
}

RollDayConv::RollDayConv(int rollDayOrWeek, BusOrCalConv busOrCalConv )
{
	_dayOfWeek = DayOfWeek(0);

	if ( _dayOfWeek == DayOfWeek(0) && rollDayOrWeek <= MAX_ROLLDAY )
	{
		_rollDayOrWeek = rollDayOrWeek;
	}
	else
	{
		_rollDayOrWeek = 0;
	}

	_busOrCalConv = busOrCalConv;
}

RollDayConv::RollDayConv()
{

	_dayOfWeek = DayOfWeek(0);
	_rollDayOrWeek = 0;
	_busOrCalConv = BusOrCalConv(0);

}

RollDayConv::RollDayConv( DayOfWeek dayOfWeek,  int rollDayOrWeek, BusOrCalConv busOrCalConv )
{

	_dayOfWeek = dayOfWeek;

	if ( _dayOfWeek == DayOfWeek(0) && rollDayOrWeek <= MAX_ROLLDAY )
	{
		_rollDayOrWeek = rollDayOrWeek;
	}
	else if ( _dayOfWeek != DayOfWeek(0) && rollDayOrWeek <= MAX_ROLLWEEK )
	{
		_rollDayOrWeek = rollDayOrWeek;
	}
	else
	{
		_rollDayOrWeek = 0;
	}
	_busOrCalConv = busOrCalConv;

}

bool RollDayConv::isBusDayConv()
{
	if ( getBusOrCalConv() == BusOrCalConv(BUS) )
		return true;
	else
		return false;
}



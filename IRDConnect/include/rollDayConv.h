/*
 * IRDRollDay.h
 *
 *  Created on: 16-Sep-2010
 *      Author: vishist
 */

#ifndef IRDROLLDAYCONV_H_
#define IRDROLLDAYCONV_H_
#include<iostream>



using namespace std;

namespace IRDConnect {


enum DayOfWeek {	NULL_DOW,
					SUN,
					MON,
					TUE,
					WED,
					THU,
					FRI,
					SAT

};


enum BusOrCalConv {
				CAL,
				BUS
};

static const int MAX_ROLLDAY = 31;
static const int MAX_ROLLWEEK = 4;


class RollDayConv {
public:


	RollDayConv();
	RollDayConv(DayOfWeek dayofWeek, int rollDayOrWeek, BusOrCalConv busOrCalConv ); // for DOFW
	RollDayConv(int rollDayOrWeek, BusOrCalConv busOrCalConv ); // for DOFM
	virtual ~RollDayConv();

	DayOfWeek getDayOfWeek() {return _dayOfWeek;}
	int getRollDayOrWeek(){return _rollDayOrWeek;}
	BusOrCalConv getBusOrCalConv() {return _busOrCalConv;}

	void setDayOfWeek(const DayOfWeek dayOfWeek) { _dayOfWeek = dayOfWeek;}
	void setRollDayOrWeek(int rollDayOrWeek ){ _rollDayOrWeek = rollDayOrWeek;}
	void setBusOrCalConv(const BusOrCalConv busOrCalConv) {_busOrCalConv = busOrCalConv;}

	bool isBusDayConv();

private:

	DayOfWeek	 	 _dayOfWeek;
	int	 			 _rollDayOrWeek;
	BusOrCalConv     _busOrCalConv;
};

}
#endif /* IRDROLLDAYCONV_H_ */

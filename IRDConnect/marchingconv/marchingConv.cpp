#include <assert.h>
#include <stdlib.h>
#include "marchingConv.h"
#include "immDates.h"

namespace IRDConnect {

typedef int RetCode ;

DateStreamWrapper::DateStreamWrapper( DateMarcher::GenSchedule & es ) :
	_es( es ),
	_minDate( 0 ),
	_maxDate( 0 )
{
}

DateStreamWrapper::~DateStreamWrapper()
{
	delete _minDate;
	delete _maxDate;
}

RetCode
DateStreamWrapper::addEvent( const Date & date )
{
	if ( !_es.addEvent( date ) )
		return false;

	if ( _minDate ) {
		if ( date < *_minDate )
			*_minDate = date;
	}
	else {

		_minDate = new Date( date );

	}

	if ( _maxDate ) {
		if ( date > *_maxDate )
			*_maxDate = date;
	}
	else {

		_maxDate = new Date( date );

	}

	_es.setESMinDate(new Date(*_minDate));
	_es.setESMaxDate(new Date(*_maxDate));


	return true;
}

const Date *
DateStreamWrapper::getMinDate() const
{
	return _minDate;
}

const Date *
DateStreamWrapper::getMaxDate() const
{
	return _maxDate;
}


DateMarcher::DateMarcher( const std::string  dateMarcher )
{
	name_ = dateMarcher;
}

DateMarcher::~DateMarcher()
{
}


GeneralForwardDateMarcher::GeneralForwardDateMarcher(const std::string  dateMarcher):DateMarcher("FRWARD")
{
	// do nothing
}

GeneralForwardDateMarcher::~GeneralForwardDateMarcher()
{
}


RetCode
GeneralForwardDateMarcher::firstAndLastEventsToGenSchedule(
const Date				& start,
const Date				& end,
int						  noOfPeriods,
const Frequency		freq,
const Calendar			& calendar,
const BusDayConv		* bdc,
GenSchedule				& genSchedule,
int					 	  evenFinalPeriod,
RollDayConv *  rollDayConv  ) const
{

	if ( !noOfPeriods )
		return false;

	DateStreamWrapper esw( genSchedule );

	DateCtl * ctl = createDateCtl( start, freq, calendar, bdc, rollDayConv );
	if ( !ctl )
		return false;

	for (int n = noOfPeriods; n >= 0; ctl->next(), n-- )
		if ( start <= *ctl && (n == noOfPeriods || n == 0))
			esw.addEvent( *ctl );

	delete ctl;

	return true;
}

RetCode
GeneralForwardDateMarcher::genSchedule(
const Date			& start,
const Date			& end,
const Frequency	freq,
const Calendar		& calendar,
const BusDayConv	* bdc,
GenSchedule			& genSchedule,
int					  evenFinalPeriod,
RollDayConv *  rollDayConv  ) const
{

	if ( !(start < end) )
		return false;

	DateStreamWrapper esw( genSchedule );

	DateCtl * ctl = createDateCtl( start, freq, calendar, bdc, rollDayConv);
	if ( !ctl )
		return false;

	RetCode rc = true;
	for ( ; *ctl < end && rc == true; ctl -> next() )
		if ( start <= *ctl )
			rc = esw.addEvent( *ctl );

	if (rc != true)
		return rc;

	if ( evenFinalPeriod ) {


		const Date * last = esw.getMaxDate();
		if ( !last ) {
			delete ctl;
			return false;
		}

		const unsigned int lastToEnd = end - *last;
		const unsigned int endToDate = *ctl - *last;

		if ( endToDate != lastToEnd )
			genSchedule.addEvent( end ); // there is a back stub just checking endToEnd equal to 0 is also ok.
		else if ( endToDate == lastToEnd )
			{
				genSchedule.addEvent( end );
				genSchedule.setESMaxDate(new Date(end)); // there is no back stub
			}

	}
	else {
		//genSchedule.setESMaxDate(new Date(end));
		genSchedule.addEvent( end );

	}

	delete ctl;

	return true;
}

GeneralForwardDateMarcher::DateCtl::DateCtl( const Date & date ) :
	Date( date )
{
}

GeneralForwardDateMarcher::DateCtl::~DateCtl()
{
}


ForwardDateMarcher::ForwardDateMarcher() :
	GeneralForwardDateMarcher( "FRWARD" )
{
}

ForwardDateMarcher::~ForwardDateMarcher()
{
}

GeneralForwardDateMarcher::DateCtl *
ForwardDateMarcher::createDateCtl(
const Date		& start,
const Frequency	freq,
const Calendar		& calendar,
const BusDayConv	* bdc,
RollDayConv  * rollDayConv ) const
{
	return new DateCtl( start, freq, calendar, bdc);
}

ForwardDateMarcher::DateCtl::DateCtl(
const Date		& date,
const Frequency	freq,
const Calendar		& cal,
const BusDayConv	* bdc ) :
	GeneralForwardDateMarcher::DateCtl( date ),
	_date( date ),
	_startDate( date ),
	_period(Period(freq)),
	_periodAddedToStartDate(Period()),
	_cal( cal ),
	_bdc( bdc )
{
}

ForwardDateMarcher::DateCtl::~DateCtl()
{
}

void
ForwardDateMarcher::DateCtl::next()
{

	_periodAddedToStartDate +=  _period;

	_date = _startDate + _periodAddedToStartDate;
	Date _dateTmp(_date.dayOfMonth(), _date.month(),_date.year());

	//Date bdcDate = _bdc -> adjustToBusDay( _dateTmp, _cal );



	Date::operator = ( _bdc ? _bdc -> adjustToBusDay( _dateTmp, _cal ) : _date );


}


EuroDollarDateMarcher::EuroDollarDateMarcher() :
	GeneralForwardDateMarcher(  "ED" )
{
}

EuroDollarDateMarcher::~EuroDollarDateMarcher()
{
}

GeneralForwardDateMarcher::DateCtl *
EuroDollarDateMarcher::createDateCtl(
const Date		& start,
const Frequency		freq,
const Calendar		& calendar,
const BusDayConv	* bdc,
RollDayConv *  rollDayConv ) const
{
	return new DateCtl( start, freq, calendar );
}

EuroDollarDateMarcher::DateCtl::DateCtl(
const Date			& date,
const Frequency	freq,
const Calendar		& cal ) :
	GeneralForwardDateMarcher::DateCtl( date ),
	_period(Period(freq)),
	_cal( cal ),
	_lastBusDay( *this == findLastBusDay() )
{
}

EuroDollarDateMarcher::DateCtl::~DateCtl()
{
}

void
EuroDollarDateMarcher::DateCtl::next()
{
	*this += _period;

	if ( _lastBusDay ) {

		Date::operator = ( findLastBusDay() );

	}
	else {

		if ( !_cal.isBusDay( *this ) ) {

			const BusDayConv * bdc = BusDayConv::find("MOD");
			assert( bdc );

			Date::operator = ( bdc -> adjustToBusDay( *this, _cal ) );

		}

		if ( !_lastBusDay )
			if ( *this == findLastBusDay() )
				_lastBusDay = 1;

	}

	assert( _cal.isBusDay( *this ) );

}

Date
EuroDollarDateMarcher::DateCtl::findLastBusDay() const
{
	const Date firstdom( Day( 1 ), month(),year() );
	const Date lastdom(  firstdom.endOfMonth(firstdom).dayOfMonth(), month(), year() );
	if ( _cal.isBusDay( lastdom ) )
		return lastdom;
	return _cal.prevBusDay( lastdom );
}


IMMDateMarcher::IMMDateMarcher() :
	GeneralForwardDateMarcher(  "IMM"  )
{
}

IMMDateMarcher::~IMMDateMarcher()
{
}

GeneralForwardDateMarcher::DateCtl *
IMMDateMarcher::createDateCtl(
const Date		& start,
const Frequency		freq,
const Calendar		& calendar,
const BusDayConv	* bdc,
RollDayConv * rollDayConv ) const
{
	return new DateCtl( start, freq, calendar, bdc );
}

IMMDateMarcher::DateCtl::DateCtl(
const Date		& date,
const Frequency	 freq,
const Calendar		& cal,
const BusDayConv	* bdc ) :
	GeneralForwardDateMarcher::DateCtl( date ),
	_period( Period(freq) ),
	_cal( cal ),
	_bdc( bdc )
{
}

IMMDateMarcher::DateCtl::~DateCtl()
{
}

void
IMMDateMarcher::DateCtl::next()
{
	*this += _period;

	if ( isIMMDate( *this,false ) )
		return;

	const Date prev = prevIMMDate( *this, _bdc, &_cal );
	const Date next = nextIMMDate( *this, _bdc, &_cal );

	assert( prev < *this );
	assert( *this < next );

	Date::operator = ( (*this - prev) < (next - *this) ? prev : next );
}


DOWDateMarcher::DOWDateMarcher() :
	GeneralForwardDateMarcher( "DOFW" )
{
}

DOWDateMarcher::~DOWDateMarcher()
{
}

GeneralForwardDateMarcher::DateCtl *
DOWDateMarcher::createDateCtl(
				const Date			& date,
			 	const Frequency	freq,
				const Calendar		& calendar,
				const BusDayConv	* bdc,
				RollDayConv * rollDayConv) const
{

	return new DateCtl( date, freq, calendar, bdc, rollDayConv );
}


DOWDateMarcher::DateCtl::DateCtl(
 		const Date         & date,
        const Frequency    freq,
        const Calendar     & cal,
        const BusDayConv   * bdc,
        RollDayConv * rollDayConv
		) :
		GeneralForwardDateMarcher::DateCtl( date ),
		_date ( date ),
		_sdate( date ),
		_period(Period(freq)),
		_currentPeriod(Period()),
		_cal( cal ),
		_bdc( bdc ),
		_rollDayConv(rollDayConv)
{
}

DOWDateMarcher::DateCtl::~DateCtl()
{
}

void
DOWDateMarcher::DateCtl::next()
{
	_date += _period;

	if (_rollDayConv -> getRollDayOrWeek() == 0) {

		Date lastDate(_date.endOfMonth( _date).dayOfMonth(),  _date.month(), _date.year() );
		int dayOfWeekOfLastOfMonth = (int)((unsigned int)lastDate.weekday());
		int theOffset = dayOfWeekOfLastOfMonth - _rollDayConv->getDayOfWeek();
		int theDay = _date.endOfMonth(_date).dayOfMonth();
		if (theOffset)
			theDay -= theOffset;
		else
			theDay -= (7 + theOffset);
		Date theDate(theDay, _date.month(), _date.year() );
		if ( _bdc && !_cal.isBusDay( theDate ) )
			theDate = _bdc->adjustToBusDay(theDate, _cal);

		Date::operator = (theDate);

		return;
	}


	Date tempDate(1,  _date.month(), _date.year() );

	int	 dayOfWeekTheMonthStartedOn = (int)((unsigned int)tempDate.weekday());

	int offsetToFirst = _rollDayConv->getDayOfWeek() - dayOfWeekTheMonthStartedOn;


	if (offsetToFirst < 0)
		offsetToFirst += 7;

	int dayOfMonth = (offsetToFirst + 1) + ((_rollDayConv->getRollDayOrWeek() - 1) * 7);

	if (_date.endOfMonth(_date).dayOfMonth() < dayOfMonth) {
		// This would have taken us beyond this month
		dayOfMonth -= 7;
		assert (_date.endOfMonth(_date).dayOfMonth() >= dayOfMonth);
	}

	Date newDate( dayOfMonth, _date.month(),  _date.year());

	Date newDateTmp(newDate.dayOfMonth(), newDate.month(),newDate.year());


	if ( _bdc && !_cal.isBusDay( newDateTmp ) )
		newDateTmp = _bdc->adjustToBusDay(newDateTmp, _cal);


	Date::operator = (newDateTmp);

	return;
}


DOMDateMarcher::DOMDateMarcher() :
    GeneralForwardDateMarcher(  "DOFM"  )
{
}

DOMDateMarcher::~DOMDateMarcher()
{
}


GeneralForwardDateMarcher::DateCtl *
DOMDateMarcher::createDateCtl(
                const Date          & date,
                const Frequency     freq,
                const Calendar      & calendar,
                const BusDayConv   * bdc,
                RollDayConv * rollDayConv ) const
{
    return new DateCtl( date, freq, calendar, bdc, rollDayConv);
}

DOMDateMarcher::DateCtl::DateCtl(
        const Date         & date,
        const Frequency    freq,
        const Calendar     & cal,
        const BusDayConv   * bdc,
        RollDayConv *  rollDayConv
        ) :
        GeneralForwardDateMarcher::DateCtl( date ),
        _date ( date ),
        _sdate( date ),
        _period( Period(freq)),
        _currentPeriod( Period() ),
        _cal(cal ),
        _bdc( bdc ),
		_rollDayConv(rollDayConv)
{
}

DOMDateMarcher::DateCtl::~DateCtl()
{
}

void
DOMDateMarcher::DateCtl::next()
{

	_date += _period;

	if ( !_rollDayConv->isBusDayConv() ) {
		int dayOfMonth = _rollDayConv->getRollDayOrWeek();
		if (_date.endOfMonth(_date).dayOfMonth() < _rollDayConv->getRollDayOrWeek())
			dayOfMonth = _date.endOfMonth(_date).dayOfMonth();

		Date newDate(dayOfMonth, _date.month(), _date.year());

		if ( _bdc && !_cal.isBusDay( newDate ) )
			newDate = _bdc->adjustToBusDay(newDate, _cal);

		Date::operator = (newDate);
	}
	else {
		Date newDate = Date(  1,_date.month(),_date.year() );
		bool firstOfMonthAlreadyABusDay = _cal.isBusDay( newDate );
		if ( _rollDayConv->getRollDayOrWeek() == 1) {
			if( ! firstOfMonthAlreadyABusDay )
				newDate = _cal.addBusDay( newDate, 1 );
		}
		else {
			if( ! firstOfMonthAlreadyABusDay )
				newDate = _cal.addBusDay( newDate, _rollDayConv->getRollDayOrWeek() );
			else
				newDate = _cal.addBusDay( newDate, _rollDayConv->getRollDayOrWeek() - 1 );

			if ( newDate.month() != _date.month() ) {
                newDate = Date( _date.endOfMonth(_date).dayOfMonth(), _date.month(), _date.year() );
                if ( !_cal.isBusDay( newDate ) )
                    newDate = _cal.prevBusDay( newDate );
			}
		}

		Date::operator = (newDate);
	}

}


BackwardDateMarcher::BackwardDateMarcher() :
	DateMarcher(  "BCKWRD" )
{
}

BackwardDateMarcher::~BackwardDateMarcher()
{
}

RetCode
BackwardDateMarcher::genSchedule(
const Date			& start,
const Date			& end,
const Frequency		freq,
const Calendar		& calendar,
const BusDayConv	* bdc,
GenSchedule			& genSchedule,
int					evenFinalPeriod,
RollDayConv  * rollDayConv ) const
{

	if ( !(start < end) )
		return false;


	DateStreamWrapper esw( genSchedule );
	BackDate date( end, freq, calendar, bdc );
	for (; start < date; date.next() )
		if ( date <= end )
			esw.addEvent( date );

	if ( evenFinalPeriod ) {


		const Date * last = esw.getMinDate();
		if ( !last )
			return false;

		const unsigned int dateToStart = start - date;
		//const unsigned int startToLast = *last - start;


		if ( dateToStart != 0 )
					genSchedule.addEvent( start ); // there is a front stub
		else
			{
					genSchedule.addEvent( start );
					genSchedule.setESMinDate(new Date(start)); // there is no front stub
			}

		//if ( dateToStart < startToLast ) commented for now
			//genSchedule.addEvent( date );

	}
	else {

		genSchedule.addEvent( start );

	}


	return true;
}

BackwardDateMarcher::BackDate::BackDate(
const Date		& date,
const Frequency		freq,
const Calendar		& cal,
const BusDayConv	* bdc ) :
	Date( date ),
	_date( date ),
	_startDate( date ),
	_period( Period(freq)),
	_periodAddedToStartDate( Period()),
	_cal( cal ),
	_bdc( bdc )
{
}

BackwardDateMarcher::BackDate::~BackDate()
{
}

void
BackwardDateMarcher::BackDate::next()
{

	_periodAddedToStartDate +=  _period;

	_date = _startDate - _periodAddedToStartDate;

	Date::operator = ( _bdc ? _bdc -> adjustToBusDay( _date, _cal ) : _date );
}


DateMarcher::GenSchedule::GenSchedule()
{
}

int DateMarcher::GenSchedule::addEvent(const Date & date)
{
	unsigned int size_d = _dates.size();

	_dates.push_back(date);

	return (_dates.size() == size_d + 1);
}


DateMarcher::GenSchedule::GenSchedule( const GenSchedule & )
{
}

DateMarcher::GenSchedule::~GenSchedule()
{
}

DateMarcher::GenSchedule &
DateMarcher::GenSchedule::operator = ( const GenSchedule & )
{
	return *this;
}


const DateMarcher *
DateMarcher::find( const std::string & name )
{

	 MarchMap::const_iterator it = getMarchMap().find( name ) ;
	    if ( it != getMarchMap().end() )
	        return it->second ;
		return 0;

}

std::map<std::string, const DateMarcher *> & DateMarcher::getMarchMap ()
{

	static MarchMap marMap ;
	static bool inited = false ;
	 if ( !inited ) {
		 marMap.insert ( MarchMap::value_type("_forward", new ForwardDateMarcher )) ;
		         marMap.insert ( MarchMap::value_type("_backward", new BackwardDateMarcher )) ;
		         marMap.insert ( MarchMap::value_type("_imm", new IMMDateMarcher )) ;
		         marMap.insert ( MarchMap::value_type("_eurodollar" , new EuroDollarDateMarcher )) ;
		         marMap.insert ( MarchMap::value_type("_dayofweek", new DOWDateMarcher  )) ;
		         marMap.insert ( MarchMap::value_type("_dayofmonth", new DOMDateMarcher )) ;

		         inited = true;
	 }
	 	 return marMap;
}
}


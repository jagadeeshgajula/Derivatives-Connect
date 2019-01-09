/*
 * swap.cpp
 *
 *  Created on: 30-Nov-2010
 *      Author: vishist
 */


#ifndef SWAP_H
#   include "swap.h"
#endif
#ifndef MONEYMKT_H
#   include "moneymkt.h"
#endif
#include "period.h"
#include "currency.h"
#include "marchingConv.h"
#include "calendarUtil.h"

//----------------------------------------------------------------------

Swap::Swap( const std::string           & id,
		    const Currency              * ccy,
            const Date                  & today,
            const Period                & period,
            const std::string           & marchingConv,
            const DayCountConv          * dcc,
            const BusDayConv            * bdc,
            const Calendar              * calendar,
            const double                & rate,
            const boost::shared_ptr<Moneymkt> & underlier,
            unsigned int                startDateOffset

            )
		:		id_( id ) ,
		 		ccy_ ( ccy ) ,
                effectiveDate_   ( today ) ,
                terminationDate_ ( today ),
                period_          ( period ),
                marchingConv_    ( marchingConv),
                dcc_             ( dcc ),
                bdc_             ( bdc ),
                calendar_        ( calendar ),
                swapRate_        ( rate ) ,
                underlier_       ( underlier),
                startDateOffset_ ( startDateOffset )

{}

Swap::Swap( const Swap & swap ) :
		id_( swap.id_ ) ,
		ccy_ ( swap.ccy_ ) ,
		effectiveDate_   ( swap.effectiveDate_ ) ,
		terminationDate_ ( swap.terminationDate_ ),
		period_          ( swap.period_ ),
		marchingConv_    ( swap.marchingConv_),
		dcc_             ( swap.dcc_ ),
		bdc_             ( swap.bdc_ ),
		calendar_        ( swap.calendar_),
		swapRate_        ( swap.swapRate_),
		underlier_       ( swap.underlier_),
		startDateOffset_ ( swap.startDateOffset_ ){}

Swap &
Swap::operator = ( const Swap & swap )
{
    if ( this != &swap )
    {
    	id_ =  swap.id_ ;
    	ccy_ = swap.ccy_ ;
    	effectiveDate_   = swap.effectiveDate_;
        terminationDate_ = swap.terminationDate_;
        period_          = swap.period_;
        marchingConv_    = swap.marchingConv_ ;
        dcc_             = swap.dcc_;
        bdc_             = swap.bdc_ ;
        calendar_        = swap.calendar_ ;
        swapRate_        = swap.swapRate_ ;
        underlier_       = swap.underlier_ ;
        startDateOffset_ = swap.startDateOffset_;

    }
    return *this;
}

Swap::~Swap()
{
}

//----------------------------------------------------------------------

const Date  &
Swap::getEffectiveDate() const {
    return effectiveDate_ ;
}

const Date  &
Swap::getTerminationDate() const {
    return terminationDate_ ;
}

unsigned int
Swap::getStartDateOffset() const {
    return startDateOffset_ ;
}

Period
Swap::getInstrTenor() const {
	return underlier_->getMaturityDateOffset()  ;
}

const Period &
Swap::getTerm() const
{
    return period_ ;
	//return _swapImp->getTerm();
}

Period
Swap::getValueDayLag() const
{

   /* const Calendar * cal = 0;
    SwapLeg * leg        = _swapImp->findTheFixedLeg();
    if ( leg )
        cal = &leg->getSettlementCalendar(); */
    return Period( getStartDateOffset(), Days);
}

//------------------------------------------------------------------
// Realtime Spreadsheet Support ...

double
Swap::getYTM( Date startDate ) const
{
 /*   const double errorRv = -1;

    SwapLeg * fixedLeg = _swapImp->findTheFixedLeg();
    if ( !fixedLeg )
        return errorRv;

    if ( !_swapImp->generateStream( startDate ) )
        return errorRv;

    return fixedLeg -> breakEven(); */
	return 0 ;
}

std::list<Date> Swap::generateSchedule ( const Date & startDate  ) {

	//const BusDayConv * bdc = BusDayConv::find  ( "FOL") ;
	effectiveDate_ = bdc_->adjustToBusDay(effectiveDate_,*calendar_) ;

	effectiveDate_ = calendar_->addBusDay(effectiveDate_,startDateOffset_) ;
    terminationDate_ = effectiveDate_ + period_ ;
	if ( bdc_ )
		terminationDate_ = bdc_->adjustToBusDay(terminationDate_,*calendar_) ;

	const DateMarcher * marcher  = DateMarcher::find ( getMarchingConv()) ;
	DateMarcher::GenSchedule es ;

//	const BusDayConv * bdc = BusDayConv::find  ( "MOD") ;
//	const Calendar * cal = CalendarUtil::getCalendar ( "BOM") ;

	marcher->genSchedule ( effectiveDate_,terminationDate_
						                     ,underlier_->getMaturityDateOffset().frequency(),*calendar_,bdc_, es);
	//marcher->genSchedule ( effectiveDate_,terminationDate_
		//			                     ,Annual,*calendar_,bdc_, es);
	return es.getEventList () ;
}

Date Swap::getInstrEndDate ( const Date & startDate )  {
	return underlier_->getMaturityDate ( underlier_->getQuoteDate( startDate)) ;
}

const DayCountConv	* Swap::getInstrDayCountConv() const {
	return underlier_->getDayCountConv() ;
}

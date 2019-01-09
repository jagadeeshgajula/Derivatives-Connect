/*
 * BusDayConvention.cpp
 *
 *  Created on: 24-Aug-2010
 *      Author: vishist
 */
#include "busDayConv.h"
#include "calendar.h"

namespace IRDConnect {

using namespace std ;
//----------------------------------------------------------------------

BusDayConv::BusDayConv( const std::string name ) : name_ (name )
{
}

BusDayConv::~BusDayConv()
{
}

Date
BusDayConv::adjustToBusDay( const Date &d, const Calendar &calendar ) const
{
	return calendar.isBusDay( d ) ? d : adjust( d, calendar );
}

Date
BusDayConv::adjustToBusDay( const Date &d,
					const Calendar &calendar,
					const Calendar &secondCalendar ) const
{
    return calendar.isBusDay( d, secondCalendar ) ? d :
				adjust( d, calendar, secondCalendar );
}


//----------------------------------------------------------------------

class None : public BusDayConv {
public:
	None();
	virtual ~None();
private:
	virtual Date adjust( const Date &d, const Calendar &calendar ) const;
	virtual Date adjust( const Date &d, const Calendar &calendar,
					const Calendar &secondCalendar ) const;
};

None::None() :
	BusDayConv( "None" )
{
}

None::~None()
{
}

Date
None::adjust( const Date &d, const Calendar & ) const
{
	return d;
}

Date
None::adjust( const Date &d, const Calendar &, const Calendar & ) const
{
    return d;
}

//----------------------------------------------------------------------

class Following : public BusDayConv {
public:
	Following();
	virtual ~Following();
private:
	virtual Date adjust( const Date &d, const Calendar &calendar ) const;
	virtual Date adjust( const Date &d, const Calendar &calendar,
					const Calendar &secondCalendar ) const;
};

Following::Following() :
	BusDayConv(  "FOL" )
{
}

Following::~Following()
{
}

Date
Following::adjust( const Date &d, const Calendar &calendar ) const
{
	return calendar.nextBusDay( d );
}

Date
Following::adjust( const Date &d, const Calendar &calendar,
					const Calendar & secondCalendar ) const
{
    return calendar.nextBusDay( d, secondCalendar );
}

//----------------------------------------------------------------------

class ModifiedFollowing : public BusDayConv {
public:
	ModifiedFollowing();
	virtual ~ModifiedFollowing();
private:
	virtual Date adjust( const Date &d, const Calendar &calendar ) const;
	virtual Date adjust( const Date &d, const Calendar &calendar,
				const Calendar &secondCalendar ) const;
};

ModifiedFollowing::ModifiedFollowing() :
	BusDayConv( "MOD" )
{
	//Remakrs: Originally, the UIName is "Modified Following". It
	// screw up the UI screen. According to the suggestion to
	// the Human factor specialist, agreed upon with the analytical
	// guy and GUI PF, we changed to Modified.
}

ModifiedFollowing::~ModifiedFollowing()
{
}

Date
ModifiedFollowing::adjust( const Date &d, const Calendar &calendar ) const
{
	Date adjDate = calendar.nextBusDay( d );

	if( adjDate.month() != d.month() )
		return calendar.prevBusDay( d );

	return adjDate;
}

Date
ModifiedFollowing::adjust( const Date &d, const Calendar &calendar,
					const Calendar &secondCalendar ) const
{
    Date adjDate = calendar.nextBusDay( d, secondCalendar);

    if( adjDate.month() != d.month() )
        return calendar.prevBusDay( d, secondCalendar );

    return adjDate;
}

//----------------------------------------------------------------------

class Preceding : public BusDayConv {
public:
	Preceding();
	virtual ~Preceding();
private:
	virtual Date adjust( const Date &d, const Calendar &calendar ) const;
	virtual Date adjust( const Date &d, const Calendar &calendar,
					const Calendar &secondCalendar ) const;
};

Preceding::Preceding() :
	BusDayConv( "PRE" )
{
}

Preceding::~Preceding()
{
}

Date
Preceding::adjust( const Date &d, const Calendar &calendar ) const
{
	return calendar.prevBusDay( d );
}

Date
Preceding::adjust( const Date &d, const Calendar &calendar,
					const Calendar &secondCalendar ) const
{
    return calendar.prevBusDay( d, secondCalendar);
}

//----------------------------------------------------------------------
const BusDayConv *
BusDayConv::find( const std::string name )
{
    BdcMap::const_iterator it = getBdcMap().find( name ) ;
    if ( it != getBdcMap().end() )
        return it->second ;
	return 0;
}

std::map<std::string, const BusDayConv *> & BusDayConv::getBdcMap ( )

{
     static BdcMap bdcMap ;
     static bool inited = false ;
     if ( !inited ) {
         bdcMap.insert ( BdcMap::value_type("NONE",new None )) ;
         bdcMap.insert ( BdcMap::value_type("FOL",new Following )) ;
         bdcMap.insert ( BdcMap::value_type("MOD",new ModifiedFollowing )) ;
         bdcMap.insert ( BdcMap::value_type("PRE",new Preceding )) ;
         inited = true ;
     }
     return bdcMap ;
}

}

// End-Of-File

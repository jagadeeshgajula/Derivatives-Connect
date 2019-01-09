/*
 * dayCountConv.h
 *
 *  Created on: 26-Aug-2010
 *      Author: vishist
 */

#ifndef DayCountConv_H_
#define DayCountConv_H_


#include "calendar.h"
#include "timeUnit.h"
#include "date.h"
#include<iostream>
#include <map>
#include <set>

using namespace std;
//using namespace IRDConnect;

namespace IRDConnect {

class DayCountConv {
public:
	DayCountConv();
	virtual ~DayCountConv();


	  virtual double getFraction ( const Date       firstDate,
	                                 const Date       secondDate,
	                                 const bool          finalPeriod   = false,
	                                 const bool          stubPeriod    = false,
	                                 const int           periodPerYear = 0 ) const = 0 ;


	   virtual double getPeriodFraction ( const Date       & actualStart,
	                                       const Date       & actualEnd,
	                                       const Date       & psuedoStart,
	                                       const Date       & psuedoEnd,
	                                       const int             numPeriodPerYear,
	                                       const bool            finalPeriod = false ) const = 0;

	    virtual int getDay ( const Date  & startDate,
	                          const Date  & endDate ) const
	    {
	        return endDate.dayOfMonth() - startDate.dayOfMonth();
	    }


	    virtual double getDayInYear( Year ) const = 0;
	    static DayCountConv * find ( const std::string & ) ;

	    //virtual void setCalendar ( const std::set<std::string> calendar );
	    virtual  const std::set<std::string > getCalendar () {return _calendar;};
	    virtual void setCalendar(std::string _calTmp);
	    virtual void setCalendar( std::set < std::string > _calTmp);

	   // {_calendar/*.insert*/(cal);}

	    DayCountConv ( const DayCountConv & );
	    std::string getStr() { return name_; };

	protected:

	    DayCountConv (const std::string &);
	    std::string name_ ;
	    std::set <std::string> _calendar; // this is a string list



	private:


	    void operator = ( const DayCountConv & );

	    typedef std::map<std::string, DayCountConv *> DccMap ;
	   	    	 static DccMap & getDccMap ( ) ;
};

class ActAct : public DayCountConv {

public:

    ActAct();


    virtual ~ActAct();

    virtual double getFraction(
        const Date  firstDate,
        const Date   secondDate,
        const bool finalPeriod = false,
        const bool stubPeriod = false,
        const int periodsPerYear = 0 ) const;

    virtual double getPeriodFraction(
        const Date  & actualStart,
        const Date  & actualEnd,
        const Date  & psuedoStart,
        const Date  & psuedoEnd,
        const int numPeriodPerYear,
        const bool finalPeriod = false ) const;

    virtual double getDayInYear( Year ) const;

protected:

    ActAct( const std::string & dayCountConv);

    // calculate secondDate - firstDate
    virtual double getDiffInDay(
        const Date  & startDate,
        const Date  & endDate ) const;
    virtual int includeFeb29(const Date  & start,
                             const Date  & end) const;
};


class ActActISMA251 : public ActAct {

public:

    ActActISMA251();

    virtual ~ActActISMA251();

    virtual double getFraction(
        const Date firstDate,
        const Date secondDate,
        const bool finalPeriod = false,
        const bool subtPeriod = false,
        const int numPeriodPerYear = 0) const;

    virtual double getPeriodFraction(
        const Date & actualStart,
        const Date & actualEnd,
        const Date & psuedoStart,
        const Date & psuedoEnd,
        const int numPeriodPerYear,
        const bool finalPeriod = false ) const;
};



class Act365F : public DayCountConv {

public:

    Act365F();

    virtual ~Act365F();

    virtual double getFraction(
        const Date firstDate,
        const Date secondDate,
        const bool finalPeriod = false,
        const bool stubPeriod = false,
        const int periodsPerYear = 0 ) const;

    virtual double getPeriodFraction(
        const Date & actualStart,
        const Date & actualEnd,
        const Date & psuedoStart,
        const Date & psuedoEnd,
        const int numPeriodPerYear,
        const bool finalPeriod = false ) const;

    virtual double getDayInYear( Year ) const;

private:

};


class Act360 : public DayCountConv {

public:

    Act360();

    virtual ~Act360();

    virtual double getFraction(
        const Date firstDate,
        const Date secondDate,
        const bool finalPeriod = false,
        const bool stubPeriod = false,
        const int periodsPerYear = 0 ) const;

    virtual double getPeriodFraction(
        const Date & actualStart,
        const Date & actualEnd,
        const Date & psuedoStart,
        const Date & psuedoEnd,
        const int numPeriodPerYear,
        const bool finalPeriod = false ) const;

    virtual double getDayInYear( Year) const;

private:

};


class Bus360 : public DayCountConv
{
public:
        Bus360();
        virtual ~Bus360();

        virtual int getDay ( const Date & startDate, const Date & endDate ) const ;

        virtual double getFraction ( const Date firstDate,
                                     const Date secondDate,
                                     const bool     finalPeriod    = false,
                                     const bool     stubPeriod     = false,
                                     const int      periodsPerYear = 0 ) const
        {
            return getDay ( firstDate, secondDate ) / 360.0 ;
        }

        virtual double getPeriodFraction ( const Date & actualStart,
                                           const Date & actualEnd,
                                           const Date & psuedoStart,
                                           const Date & psuedoEnd,
                                           const int        numPeriodPerYear,
                                           const bool       finalPeriod = false ) const
        {
            return getFraction(actualStart, actualEnd) * numPeriodPerYear;
        }

        virtual double getDayInYear ( Year ) const ;

};

class Bus252 : public DayCountConv
{
public:
        Bus252();
        virtual ~Bus252();

        virtual int getDay ( const Date & startDate,
                              const Date & endDate ) const ;

        virtual double getFraction ( const Date firstDate,
                                     const Date secondDate,
                                     const bool     finalPeriod    = false,
                                     const bool     stubPeriod     = false,
                                     const int      periodsPerYear = 0 ) const
        {
            return getDay ( firstDate, secondDate ) / 252.0 ;
        }

        virtual double getPeriodFraction ( const Date & actualStart,
                                           const Date & actualEnd,
                                           const Date & psuedoStart,
                                           const Date & psuedoEnd,
                                           const int        numPeriodPerYear,
                                           const bool       finalPeriod = false ) const
        {
            return getFraction ( actualStart, actualEnd ) * numPeriodPerYear ;
        }

        virtual double getDayInYear ( Year ) const ;


};

class Dcc30360Based : public DayCountConv {
public:

    Dcc30360Based(const std::string & name);
    virtual ~Dcc30360Based();

    virtual double getFraction(
        const Date      firstDate,
        const Date      secondDate,
        const bool finalPeriod = false,
        const bool stubPeriod = false,
        const int periodsPerYear = 0 ) const;

    virtual double getPeriodFraction(
        const Date      & actualStart,
        const Date      & actualEnd,
        const Date      & psuedoStart,
        const Date      & psuedoEnd,
        const int           numPeriodPerYear,
        const bool          finalPeriod = false ) const;

    double getDayInYear( Year ) const;

protected :

    virtual double getDayCountForGivenDates(
        const Date      & startDate,
        const Date      & endDate,
        const bool          finalPeriod = false ) const = 0;



    static int isLastDayOfFebruary( const Date & d );



    static Day min( Day firstDate, Day secondDate );

private:


    Dcc30360Based( const Dcc30360Based & );
    void operator = ( const Dcc30360Based & );
};


class Dcc30S360 : public Dcc30360Based {
public:

    Dcc30S360();
    ~Dcc30S360();

protected:

    double getDayCountForGivenDates(
        const Date  & startDate,
        const Date  & endDate,
        const bool      finalPeriod ) const;

private:


    Dcc30S360( const Dcc30S360 & );
    void operator = ( const Dcc30S360 & );
};


class Dcc30I360 : public Dcc30360Based {
public:

    Dcc30I360();
    ~Dcc30I360();

protected:

    double getDayCountForGivenDates(
        const Date  & startDate,
        const Date  & endDate,
        const bool      finalPeriod ) const;

private:

    Dcc30I360( const Dcc30I360 & );
    void operator = ( const Dcc30I360 & );
};


class Dcc30B360 : public Dcc30360Based {
public:

    Dcc30B360();
    ~Dcc30B360();

protected:

    double getDayCountForGivenDates(
        const Date  & startDate,
        const Date  & endDate,
        const bool      finalPeriod ) const;

private:



    Dcc30B360( const Dcc30B360 & );
    void operator = ( const Dcc30B360 & );
};


class Dcc30E360 : public Dcc30360Based {
public:

    Dcc30E360();
    ~Dcc30E360();

protected:

    double getDayCountForGivenDates(
        const Date  & startDate,
        const Date  & endDate,
        const bool      finalPeriod ) const;

private:



    Dcc30E360( const Dcc30E360 & );
    void operator = ( const Dcc30E360 & );
};

class Dcc30E360last : public Dcc30360Based {
public:

    Dcc30E360last();
    ~Dcc30E360last();

protected:

    double getDayCountForGivenDates(
        const Date  & startDate,
        const Date  & endDate,
        const bool      finalPeriod ) const;

private:



    Dcc30E360last( const Dcc30E360last & );
    void operator = ( const Dcc30E360last & );
};

class Act36525 : public DayCountConv {

public:

    Act36525();

    virtual ~Act36525();

    virtual double getFraction(
        const Date firstDate,
        const Date secondDate,
        const bool finalPeriod = false,
        const bool stubPeriod = false,
        const int periodsPerYear = 0 ) const;


    virtual double getPeriodFraction(
        const Date & actualStart,
        const Date & actualEnd,
        const Date & psuedoStart,
        const Date & psuedoEnd,
        const int numPeriodPerYear,
        const bool finalPeriod = false ) const;

    virtual double getDayInYear( Year ) const;

private:

};

class EqualPayment : public DayCountConv {
public:

    EqualPayment();
    virtual ~EqualPayment();

    virtual double getFraction(
        const Date      firstDate,
        const Date      secondDate,
        const bool          finalPeriod,
        const bool          stubPeriod = false,
        const int periodPerYear = 0 ) const;

    virtual double getPeriodFraction(
        const Date      & actualStart,
        const Date      & actualEnd,
        const Date      & psuedoStart,
        const Date      & psuedoEnd,
        const int           numPeriodPerYear,
        const bool          finalPeriod ) const;

    virtual double getDayInYear( Year year ) const;

private:


    EqualPayment( const EqualPayment & );
    void operator = ( const EqualPayment & );
};

class FullPayment : public DayCountConv {
public:

    FullPayment();
    virtual ~FullPayment();

    virtual double getFraction(
        const Date      firstDate,
        const Date      secondDate,
        const bool          finalPeriod,
        const bool          stubPeriod = false,
        const int           periodsPerYear = 0) const;

    virtual double getPeriodFraction(
        const Date & actualStart,
        const Date & actualEnd,
        const Date & psuedoStart,
        const Date & psuedoEnd,
        const int numPeriodPerYear,
        const bool finalPeriod = false ) const;

    virtual double getDayInYear( Year year ) const;

private:


    FullPayment( const FullPayment & );
    void operator = ( const FullPayment & );
};

}

#endif /* DayCountConv_H_ */

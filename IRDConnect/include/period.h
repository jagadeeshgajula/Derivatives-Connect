/*
 * period.h
 *
 *  Created on: 28-Aug-2010
 *      Author: vishist
 */

#ifndef IRDPERIOD_H_
#define IRDPERIOD_H_

#include "frequency.h"
#include "timeUnit.h"
#include "types.h"
#include <ostream>
#include "irdString.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


    //! Time period described by a number of a given time unit
    /*! \ingroup datetime */
    class Period {
      public:
        Period(): length_(0), units_(Days) {}
        Period(Integer n, TimeUnit units)
        : length_(n), units_(units) {}
        explicit Period(Frequency f);
        //explicit Period(Tenor t);
        Integer length() const { return length_; }
        TimeUnit units() const { return units_; }
        Frequency frequency() const;
        Period(String period);
        //Tenor tenor() const;
        Period& operator+=(const Period&);
        Period& operator-=(const Period&);
        Period& operator=(const Period&);
        Period& operator/=(Integer);
        void normalize();
      protected:
        Integer length_;
        TimeUnit units_;
    };
    /*! \relates Period */
    template <typename T> Period operator*(T n, TimeUnit units);
    /*! \relates Period */
    template <typename T> Period operator*(TimeUnit units, T n);

    /*! \relates Period */
    Period operator-(const Period&);

    /*! \relates Period */
    Period operator*(Integer n, const Period&);
    /*! \relates Period */
    Period operator*(const Period&, Integer n);

    /*! \relates Period */
    bool operator<(const Period&, const Period&);
    /*! \relates Period */
    bool operator==(const Period&, const Period&);
    /*! \relates Period */
    bool operator!=(const Period&, const Period&);
    /*! \relates Period */
    bool operator>(const Period&, const Period&);
    /*! \relates Period */
    bool operator<=(const Period&, const Period&);
    /*! \relates Period */
    bool operator>=(const Period&, const Period&);



    /*! \relates Period */
    std::ostream& operator<<(std::ostream&, const Period&);


    namespace IRDdetail {

        struct long_period_holder {
            long_period_holder(const Period& p) : p(p) {}
            Period p;
        };
        std::ostream& operator<<(std::ostream&, const long_period_holder&);

        struct short_period_holder {
            short_period_holder(Period p) : p(p) {}
            Period p;
        };
        std::ostream& operator<<(std::ostream&, const short_period_holder&);

    }

    namespace IRDio {

        //! output periods in long format (e.g. "2 weeks")
        /*! \ingroup manips */
        IRDdetail::long_period_holder long_period(const Period&);

        //! output periods in short format (e.g. "2w")
        /*! \ingroup manips */
        IRDdetail::short_period_holder short_period(const Period&);

    }

    // inline definitions

    template <typename T>
    inline Period operator*(T n, TimeUnit units) {
        return Period(Integer(n),units);
    }

    template <typename T>
    inline Period operator*(TimeUnit units, T n) {
        return Period(Integer(n),units);
    }

    inline Period operator-(const Period& p) {
        return Period(-p.length(),p.units());
    }

    inline Period operator*(Integer n, const Period& p) {
        return Period(n*p.length(),p.units());
    }

    inline Period operator*(const Period& p, Integer n) {
        return Period(n*p.length(),p.units());
    }

    inline bool operator==(const Period& p1, const Period& p2) {
        return !(p1 < p2 || p2 < p1);
    }

    inline bool operator!=(const Period& p1, const Period& p2) {
        return !(p1 == p2);
    }

    inline bool operator>(const Period& p1, const Period& p2) {
        return p2 < p1;
    }

    inline bool operator<=(const Period& p1, const Period& p2) {
        return !(p1 > p2);
    }

    inline bool operator>=(const Period& p1, const Period& p2) {
        return !(p1 < p2);
    }



}

#endif /* IRDPERIOD_H_ */

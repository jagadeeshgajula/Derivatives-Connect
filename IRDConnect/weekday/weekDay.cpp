/*
 * WeekDay.cpp
 *
 *  Created on: 06-Sep-2010
 *      Author: vishist
 */
#include "weekDay.h"
#include "types.h"
#include "errors.h"

namespace IRDConnect {

    // weekday formatting

    std::ostream& operator<<(std::ostream& out, const Weekday& w) {
        return out << IRDio::long_weekday(w);
    }

    namespace IRDdetail {

        std::ostream& operator<<(std::ostream& out,
                                 const long_weekday_holder& holder) {
            switch (holder.d) {
              case Sunday:
                return out << "Sunday";
              case Monday:
                return out << "Monday";
              case Tuesday:
                return out << "Tuesday";
              case Wednesday:
                return out << "Wednesday";
              case Thursday:
                return out << "Thursday";
              case Friday:
                return out << "Friday";
              case Saturday:
                return out << "Saturday";
              default:
                QL_FAIL("unknown weekday");
            }
        }

        std::ostream& operator<<(std::ostream& out,
                                 const short_weekday_holder& holder) {
            switch (holder.d) {
              case Sunday:
                return out << "Sun";
              case Monday:
                return out << "Mon";
              case Tuesday:
                return out << "Tue";
              case Wednesday:
                return out << "Wed";
              case Thursday:
                return out << "Thu";
              case Friday:
                return out << "Fri";
              case Saturday:
                return out << "Sat";
              default:
                QL_FAIL("unknown weekday");
            }
        }

        std::ostream& operator<<(std::ostream& out,
                                 const shortest_weekday_holder& holder) {
            switch (holder.d) {
              case Sunday:
                return out << "Su";
              case Monday:
                return out << "Mo";
              case Tuesday:
                return out << "Tu";
              case Wednesday:
                return out << "We";
              case Thursday:
                return out << "Th";
              case Friday:
                return out << "Fr";
              case Saturday:
                return out << "Sa";
              default:
                QL_FAIL("unknown weekday");
            }
        }

    }

    namespace IRDio {

        IRDdetail::long_weekday_holder long_weekday(Weekday d) {
            return IRDdetail::long_weekday_holder(d);
        }

        IRDdetail::short_weekday_holder short_weekday(Weekday d) {
            return IRDdetail::short_weekday_holder(d);
        }

        IRDdetail::shortest_weekday_holder shortest_weekday(Weekday d) {
            return IRDdetail::shortest_weekday_holder(d);
        }

    }

}
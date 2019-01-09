/*
 * dataFormat.h
 *
 *  Created on: 06-Sep-2010
 *      Author: vishist
 */

#ifndef DATAFORMAT_H_
#define DATAFORMAT_H_
#include "null.h"
#include "types.h"
#include <ostream>


namespace IRDConnect {

using namespace std;

    namespace IRDdetail {

        template <typename T> struct null_checker {
            null_checker(T value) : value(value) {}
            T value;
        };
        template <typename T>
        std::ostream& operator<<(std::ostream&, const null_checker<T>&);

        struct ordinal_holder {
            ordinal_holder(Size n) : n(n) {}
            Size n;
        };
        std::ostream& operator<<(std::ostream&, const ordinal_holder&);

        template <typename T> struct power_of_two_holder {
            power_of_two_holder(T n) : n(n) {}
            T n;
        };
        template <typename T>
        std::ostream& operator<<(std::ostream&,
                                 const power_of_two_holder<T>&);

        struct percent_holder {
            percent_holder(Real value) : value(value) {}
            Real value;
        };
        std::ostream& operator<<(std::ostream&, const percent_holder&);

        template <typename InputIterator> struct sequence_holder {
            sequence_holder(InputIterator begin, InputIterator end)
            : begin(begin), end(end) {}
            InputIterator begin, end;
        };
        template <typename I>
        std::ostream& operator<<(std::ostream&, const sequence_holder<I>&);

    }


    namespace IRDio {

        /*! \defgroup manips Output manipulators

            Helper functions for creating formatted output.

            @{
        */

        //! check for nulls before output
        template <typename T>
        IRDdetail::null_checker<T> checknull(T);

        //! outputs naturals as 1st, 2nd, 3rd...
        IRDdetail::ordinal_holder ordinal(Size);

        //! output integers as powers of two
        template <typename T>
        IRDdetail::power_of_two_holder<T> power_of_two(T);

        //! output reals as percentages
        IRDdetail::percent_holder percent(Real);

        //! output rates and spreads as percentages
        IRDdetail::percent_holder rate(Rate);

        //! output volatilities as percentages
        IRDdetail::percent_holder volatility(Volatility);

        //! output STL-compliant containers as space-separated sequences
        template <class Container>
        IRDdetail::sequence_holder<typename Container::const_iterator>
        sequence(const Container& c);

        /*! @}  */


        // inline definitions

        template <typename T>
        inline IRDdetail::null_checker<T> checknull(T x) {
            return IRDdetail::null_checker<T>(x);
        }

        inline IRDdetail::ordinal_holder ordinal(Size n) {
            return IRDdetail::ordinal_holder(n);
        }

        template <typename T>
        inline IRDdetail::power_of_two_holder<T> power_of_two(T n) {
            return IRDdetail::power_of_two_holder<T>(n);
        }

        inline IRDdetail::percent_holder percent(Real x) {
            return IRDdetail::percent_holder(x);
        }

        inline IRDdetail::percent_holder rate(Rate r) {
            return IRDdetail::percent_holder(r);
        }

        inline IRDdetail::percent_holder volatility(Volatility v) {
            return IRDdetail::percent_holder(v);
        }

        template <class Container>
        inline IRDdetail::sequence_holder<typename Container::const_iterator>
        sequence(const Container& c) {
            return IRDdetail::sequence_holder<typename Container::const_iterator>(
                                                           c.begin(), c.end());
        }

    }

    namespace IRDdetail {

        template <typename T>
        inline std::ostream& operator<<(std::ostream& out,
                                        const null_checker<T>& checker) {
            if (checker.value == Null<T>())
                return out << "null";
            else
                return out << checker.value;
        }

        template <typename T>
        inline std::ostream& operator<<(std::ostream& out,
                                        const power_of_two_holder<T>& holder) {
            if (holder.n == Null<T>())
                return out << "null";

            T n = holder.n;
            Integer power = 0;
            if (n != 0) {
                while (!(n & 1UL)) {
                    power++;
                    n >>= 1;
                }
            }
            return out << n << "*2^" << power;
        }

        template <typename I>
        inline std::ostream& operator<<(std::ostream& out,
                                        const sequence_holder<I>& holder) {
            out << "( ";
            for (I i = holder.begin; i != holder.end; ++i)
                out << *i << " ";
            out << ")";
            return out;
        }

    }

}


#endif /* DATAFORMAT_H_ */

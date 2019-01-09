#ifndef BUSDAYCONV_H
#define BUSDAYCONV_H

#include "date.h"
#include <map>

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class Calendar ;
class BusDayConv {
public:

Date adjustToBusDay( const Date & d,
                                          const Calendar & calendar ) const;
Date adjustToBusDay( const Date & d,
                    const Calendar &calendar,
                    const Calendar &secondCalendar ) const;
static const BusDayConv * find( const std::string name )  ;

BusDayConv ( const BusDayConv & );
BusDayConv &operator=( const BusDayConv & );

virtual Date adjust ( const Date     & d,
                              const Calendar & calendar ) const = 0 ;

virtual Date adjust ( const Date     & d,
                              const Calendar & calendar,
                              const Calendar & secondCalendar ) const = 0 ;

std::string getStr() const {return name_;};

protected:

BusDayConv ( std::string name) ;
    virtual ~BusDayConv () ;


private:


    std::string name_ ;
    typedef std::map<std::string, const BusDayConv *> BdcMap ;
    static BdcMap & getBdcMap ( ) ;

};

}
#endif


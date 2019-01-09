#ifndef CURVEDEF_H_
#define CURVEDEF_H_
#include <string>
#include <vector>
#include "boost/shared_ptr.hpp"
#include "date.h"


#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/xml_parser.hpp"

namespace IRDConnect { 
class Moneymkt;
class MMFuture;
class Swap ;


  class CurveDef {
  public : 
    CurveDef( const Date & date, const std::string & cashFileName,const std::string & futFileName , const std::string & swapFileName ) ;
    CurveDef ( const std::string & filename );
    const std::vector <boost::shared_ptr<Moneymkt> >  & getCashTenors () { return cashTenors_; } ;
    const std::vector <boost::shared_ptr<MMFuture> >  & getFutureTenors() { return futureTenors_; } ;
    const std::vector <boost::shared_ptr<Swap> > & getSwapTenors() {return swapTenors_; } ;
    ~CurveDef() { cout << "destructor" << endl; } ;
  private :
    void loadCashTenors ( const std::string & cashFileName );
    void loadFutureTenors ( const std::string & futFileName );
    void loadSwapTenors ( const std::string & swapFileName );
    void load (const std::string & fileName ) ;
    void loadCash ( boost::property_tree::ptree & pt );    
    void loadFut ( boost::property_tree::ptree & pt );    
    void loadSwap ( boost::property_tree::ptree & pt );    
    Date curveDate_ ;
    std::vector <boost::shared_ptr<Moneymkt> >  cashTenors_ ;
    std::vector <boost::shared_ptr<MMFuture> >  futureTenors_ ;
    std::vector <boost::shared_ptr<Swap> > swapTenors_ ;
     
  };
}
#endif

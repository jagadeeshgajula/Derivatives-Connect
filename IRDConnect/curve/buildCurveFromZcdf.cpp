/*
 * buildCurveFromZcdf.cpp
 *
 *  Created on: 30-Oct-2010
 *      Author: vishist
 */

#include "buildCurveFromZcdf.h"
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include "date.h"
#include <fstream>
#include "curve.h"



namespace IRDConnect {


Date dateFromString ( std::string dateStr )
{
	boost::char_separator<char> sep("-");
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	tokenizer tok(dateStr,sep);
	tokenizer::iterator beg=tok.begin();
	Day day = boost::lexical_cast<int> (*beg) ;
	beg++ ;
	int month = boost::lexical_cast<int> (*beg) ;
	beg++ ;
	Year year = boost::lexical_cast<int> (*beg) ;

	return Date ( day,(Month) (month ) , year );

}
boost::shared_ptr <Curve> BuildCurveFromZcdf::build ()
{
	std::vector<IRDConnect::Date> dates ;
	std::vector<double> zcdfs;

		std::ifstream fin ( "/home/vishist/test.in");
		std::string buf;
		boost::char_separator<char> sep(",");
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		while ( getline(fin,buf))
		{
			 tokenizer tok(buf,sep);
			 int k =0;
	     	 for(tokenizer::iterator beg=tok.begin(); beg!=tok.end();++beg,++k){
		         if ( k== 1 )
		         {
		        	 dates.push_back (dateFromString(*beg)) ;
		         }
		         if ( k==2 )
		         {
		        	 zcdfs.push_back ( boost::lexical_cast<double>(*beg));
		         }
	     		 std::string str ( *beg ) ;
	     		 cout << str << "\n";
		     }
			 cout << "IN" << buf << endl ;
		}
		return boost::shared_ptr<Curve>(new Curve ( dates.front(),dates , zcdfs )) ;
}
}

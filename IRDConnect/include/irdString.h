#ifndef STRING_H_
#define STRING_H_

#include <stddef.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>

using namespace std;
//using namespace IRDConnect;

namespace IRDConnect {

static ofstream logFile("/home/vishist/IRD.log", ios::out | ios::app);

class String  {

public:

    String( const char * = 0 );
    String( const String  & );

    String( const std::string & );

    String( const char * str, const int len );

    ~String();

    String  insertCharInStr
        (
        const String  & str,
        char cExisting,
        char cIns = '\\'
        );

    operator const char *() const;

    String& operator=( const char * );
    String& operator=( const String  & );
    //String& operator=( const std::string  & );

  
    String& operator+=( const char );
    String& operator+=( const char * );
    String& operator+=( const String  & );

    String  operator + ( const String  & );
    String  operator + ( const char *);
  friend  String  operator + (const char *, const String  & );

    int operator==( const char * ) const;
    int operator!=( const char * ) const;
    int operator==( const String  & ) const;
    int operator!=( const String  & ) const;
    int operator!() const;


    static int strcmp(const char *, const char *);

    
    char & operator[] ( const unsigned index ) const;

    void trimRight(); 

    void trimLeft(); 

    static std::string doubleToString(double d);
    static std::string doubleToFourDecString(double p, int prec);
   
    int isEmpty() const
    {
      return _str ? *_str == '\0' : 1;

    }
    static int compare( String ** s1, String   **s2) {
        return(strcasecmp(*(*s1), *(*s2)));
    }
    
    void toLower () ;
    void toUpper () ;

    char* getStr() const;

private:

    char *_str;

};


int operator==( const char *spStr, const String  &str );
int operator!=( const char *spStr, const String  &str );


std::ostream &operator <<( std::ostream &, const String  & );

}

#endif


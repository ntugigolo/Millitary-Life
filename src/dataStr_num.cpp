// File    : dataStr_num.cpp
// Author  : XQWang
// Update  : 5.14.2016
// Synopsis: Functions for class Number

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "dataStr.h"

using namespace std;

const double& Number::getDouble() const { return _value; }
const int Number::getInt()        const { return static_cast<int>(_value); }
const int Number::getFloor()      const { return floor(_value); }
const int Number::getCeiling()    const { return ceil(_value); }
void Number::toCeiling() { _value = ceil(_value); }
void Number::toFloor()   { _value = floor(_value); }
Number Number::operator +  ( const Number& rhs ) const { return _value + rhs._value; }
Number Number::operator -  ( const Number& rhs ) const { return _value - rhs._value; }
Number Number::operator *  ( const Number& rhs ) const { return _value * rhs._value; }
Number Number::operator /  ( const Number& rhs ) const { return _value / rhs._value; }
Number Number::operator =  ( const Number& rhs ) { _value = rhs._value; return *this; }
Number Number::operator =  ( const int& rhs )    { _value = static_cast<double>(rhs); return *this; }
Number Number::operator =  ( const double& rhs ) { _value = rhs; return *this; }
Number& Number::operator ++ () { _value++; return *this; }
Number& Number::operator -- () { _value--; return *this; }
Number& Number::operator += ( const Number& rhs ) { *this = *this + rhs; return *this; }
Number& Number::operator -= ( const Number& rhs ) { *this = *this - rhs; return *this; }
Number Number::operator ++ (int) { Number temp = *this; ++(*this); return temp; }
Number Number::operator -- (int) { Number temp = *this; --(*this); return temp; }
bool   Number::operator == ( const Number& rhs ) const { return _value == rhs._value; }
bool   Number::operator == ( const double& rhs ) const { return _value == rhs; }
bool   Number::operator != ( const Number& rhs ) const { return _value != rhs._value; }
bool   Number::operator != ( const double& rhs ) const { return _value != rhs; }
bool   Number::operator >  ( const Number& rhs ) const { return _value >  rhs._value; }
bool   Number::operator <  ( const Number& rhs ) const { return _value <  rhs._value; }
bool   Number::operator >= ( const Number& rhs ) const { return _value >= rhs._value; }
bool   Number::operator <= ( const Number& rhs ) const { return _value <= rhs._value; }
ostream& operator << ( ostream& out, const Number& rhs ){ out << setprecision(8) << rhs.getDouble();  return out; }

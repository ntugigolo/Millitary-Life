// File    : dataStr_gridvec.cpp
// Author  : XQWang
// Update  : 1.14.2016
// Synopsis: Functions for class Grid, Vec2D

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "dataStr.h"

using namespace std;

char buff[50];

// class Grid
Grid::Grid(){
	_x = _y = 0.0;
}
bool Grid::setLL( const Number* arr ){
	_Nd = arr[0]; _Nm = arr[1]; _Ns = arr[2];
	_Ed = arr[3]; _Em = arr[4]; _Es = arr[5];
	return LL2XY();
}
bool Grid::setXY( const Number& x, const Number& y ) { _x = x; _y = y; return XY2LL(); }
const Number& Grid::getX() const { return _x; }
const Number& Grid::getY() const { return _y; }
const Number& Grid::getNd() const { return _Nd; }
const Number& Grid::getNm() const { return _Nm; }
const Number& Grid::getNs() const { return _Ns; }
const Number& Grid::getEd() const { return _Ed; }
const Number& Grid::getEm() const { return _Em; }
const Number& Grid::getEs() const { return _Es; }
pair< Number, Number > Grid::getLtLn() const{
	Number Lt = ( getNd() + getNm()/60 + getNs()/3600 ).getDouble();
	Number Ln = ( getEd() + getEm()/60 + getEs()/3600 ).getDouble();
	return make_pair( Lt, Ln );
}
Grid  Grid::operator +  ( const Vec2D& rhs ) const{
	Grid lhs; lhs.setXY( _x + rhs.getX(), _y + rhs.getY() ); return lhs;
}
Vec2D Grid::operator -  ( const Grid& rhs ) const{
	Vec2D lhs; lhs.setXY( _x - rhs.getX(), _y - rhs.getY() ); return lhs;
}
Grid  Grid::operator =  ( const Grid& rhs ) { setXY( rhs.getX(), rhs.getY() ); return *this; }
bool  Grid::operator == ( const Grid& rhs ) const { return _x == rhs.getX() && _y == rhs.getY(); }
bool  Grid::operator != ( const Grid& rhs ) const { return !(rhs == *this); }
ostream& operator << ( ostream& out, const Grid& rhs ){
	if( out == cout )
		sprintf( buff, "( %2d %2d\' %.2f\", %3d %2d\' %.2f\" )", rhs.getNd().getInt(), rhs.getNm().getInt(), rhs.getNs().getDouble(), rhs.getEd().getInt(), rhs.getEm().getInt(), rhs.getEs().getDouble() );
	else
		sprintf( buff, "%2d,%2d,%.2f,%3d,%2d,%.2f", rhs.getNd().getInt(), rhs.getNm().getInt(), rhs.getNs().getDouble(), rhs.getEd().getInt(), rhs.getEm().getInt(), rhs.getEs().getDouble() );

	out << buff; return out;
}
bool Grid::XY2LL(){
	Number temp = _y;
	_Nd = ( temp/D2M ).getInt(); temp = temp - _Nd * D2M;
	_Nm = ( temp/M2M ).getInt(); temp = temp - _Nm * M2M;
	_Ns =   temp/S2M;
	temp = _x / cos( _Nd.getDouble()*DEGREE );
	_Ed = ( temp/D2M ).getInt(); temp = temp - _Ed * D2M;
	_Em = ( temp/M2M ).getInt(); temp = temp - _Em * M2M;
	_Es = ( temp/S2M );
	return true;
}
bool Grid::LL2XY(){
	_y =   _Nd*D2M + _Nm*M2M + _Ns*S2M;
	_x = ( _Ed*D2M + _Em*M2M + _Es*S2M ) * cos( _Nd.getDouble()*DEGREE ); // + _Nm.getDouble()*DEGREE/MINUTE
	return true;
}

// class Vec2D
bool Vec2D::setXY( const Number& x, const Number& y ) { _x = x; _y = y; return true; }
bool Vec2D::setCurrXY( const Number& x, const Number& y ) { cur_x = x; cur_y = y;return true; }

bool Vec2D::setVD( const Number& v, const Number& a ) {
	// v for value; a for angle (right is 0, up is 90)
	_x = v * cos(a.getDouble()*DEGREE);
	_y = v * sin(a.getDouble()*DEGREE);
	return true;
}
const Number& Vec2D::getX() const { return _x; }
const Number& Vec2D::getY() const { return _y; }
Vec2D Vec2D::rotate( const Number& angle ) const {
	Vec2D newVec; newVec.setVD( getValue(), getAngle() + angle ); return newVec;
}
Vec2D Vec2D::setCurrSpeed(const Number& x, const Number& y) {
    Vec2D result;
    result.setXY(x,y); return result;
    //result.setCurrXY(x,y); return result;
}

Number Vec2D::getValue() const { return sqrt( pow( _x.getDouble(), 2 ) + pow( _y.getDouble(), 2) ); }
Number Vec2D::getAngle() const {
    if (_x == 0) return 0;
	if( _x > 0 ) return atan( (_y/_x).getDouble() ) / DEGREE;
	else         return atan( (_y/_x).getDouble() ) / DEGREE +180;
}
Vec2D Vec2D::operator + ( const Number& rhs ) const{
	Vec2D lhs; lhs = *this; lhs = lhs * rhs / getValue(); return lhs + *this;
}
Vec2D Vec2D::operator + ( const Vec2D& rhs ) const{
	Vec2D lhs; lhs.setXY( _x + rhs.getX(), _y + rhs.getY() ); return lhs;
}
Vec2D Vec2D::operator - ( const Vec2D& rhs ) const{
	Vec2D lhs; lhs.setXY( _x - rhs.getX(), _y - rhs.getY() ); return lhs;
}
Vec2D Vec2D::operator * ( const Number& rhs ) const{
	Vec2D lhs; lhs.setXY( _x * rhs, _y * rhs ); return lhs;
}
Vec2D Vec2D::operator / ( const Number& rhs ) const{
	Vec2D lhs; lhs.setXY( _x / rhs, _y / rhs ); return lhs;
}
Vec2D Vec2D::operator = ( const Vec2D& rhs ){
	setXY( rhs.getX(), rhs.getY() ); return *this;
}
bool Vec2D::operator == ( const Vec2D& rhs ) const{
	return _x == rhs.getX() && _y == rhs.getY();
}
bool Vec2D::operator >  ( const Vec2D& rhs ) const{
	return getValue() > rhs.getValue();
}
bool Vec2D::operator <  ( const Vec2D& rhs ) const{
	return getValue() < rhs.getValue();
}
bool Vec2D::operator >= ( const Vec2D& rhs ) const{
	return getValue() >= rhs.getValue();
}
bool Vec2D::operator <= ( const Vec2D& rhs ) const{
	return getValue() <= rhs.getValue();
}
ostream& operator << ( ostream& out, const Vec2D& rhs ){
	sprintf( buff, "( %.2f, %.2f )", rhs.getX().getDouble(), rhs.getY().getDouble() );
	out << buff; return out;
}

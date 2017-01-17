// File    : dataStr.h
// Author  : XQWang
// Update  : 5.15.2016
// Synopsis: Header file for data structure : Number, Grid, Vec2D

#ifndef DATASTR_H
#define DATASTR_H

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <math.h>
#include <iomanip>
#include <fstream>

#define HOUR   3600     // Hour
#define MINUTE 60       // Minute
#define SECOND 1        // Second
#define NM     1852     // Nautical miles
#define KM     1000     // Kilometers
#define M      1        // Meters
#define KNOTS  NM/HOUR 	// Knots to m/s
#define PI     3.14159  // pi
#define DEGREE (PI/180) // Degree to Radian
#define D2M    111120   // Latitude degree to meters
#define M2M    1852     // Latitude minute to meters
#define S2M    30.87    // Latitude second to meters

using namespace std;

class Number;
class Grid;
class Vec2D;
class LayerTree;

class Number
{
	public:
		Number( double v = 0 ) :_value(v) {}
		~Number(){}
		// access functions and utility functions
		const double& getDouble() const;
		const int getInt() const;
		const int getCeiling() const
		const int getFloor() const;
		void toCeiling();
		void toFloor();
		// operator overloading
		Number operator + ( const Number& ) const;
		Number operator - ( const Number& ) const;
		Number operator * ( const Number& ) const;
		Number operator / ( const Number& ) const;
		Number operator = ( const Number& );
		Number operator = ( const int& );
		Number operator = ( const double& );
		Number& operator ++ ();
		Number& operator -- ();
		Number& operator += (const Number&);
		Number& operator -= (const Number&);
		Number operator ++ (int);
		Number operator -- (int);
		bool   operator == ( const Number& ) const;
		bool   operator == ( const double& ) const;
		bool   operator != ( const Number& ) const;
		bool   operator != ( const double& ) const;
		bool   operator >  ( const Number& ) const;
		bool   operator <  ( const Number& ) const;
		bool   operator >= ( const Number& ) const;
		bool   operator <= ( const Number& ) const;
		friend ostream& operator << ( ostream&, const Number& );
	private:
		double _value;
};

class Grid
{
	public:
		Grid();
		~Grid(){}
		// access/set functions and utility functions
		bool setLL( const Number* );  // _Nd, _Nm, _Ns, _Ed, _Em, _Es
		bool setXY( const Number&, const Number& );	// _x, _y
		const Number& getX() const;   // _x
		const Number& getY() const;   // _y
		const Number& getNd() const;  // _Nd;
		const Number& getNm() const;  // _Nm;
		const Number& getNs() const;  // _Ns;
		const Number& getEd() const;  // _Ed;
		const Number& getEm() const;  // _Em;
		const Number& getEs() const;  // _Es;
		pair< Number, Number > getLtLn() const;
		// operator overloading
		Grid  operator +  ( const Vec2D& ) const; // previous point + movement(speed*time) = new point
		Vec2D operator -  ( const Grid& ) const;  // movement = new point - previous point
		Grid  operator =  ( const Grid& );        // assignment
		bool  operator == ( const Grid& ) const;  // comparison
		bool  operator != ( const Grid& ) const;  // comparison
		friend ostream& operator << ( ostream&, const Grid& ); // print
		// static function
		static Number getDistance( const Grid& A, const Grid& B){
			Number xDistance = A.getX() - B.getX();
			Number yDistance = A.getY() - B.getY();
			return sqrt( pow( xDistance.getDouble(), 2 ) + pow( yDistance.getDouble(), 2 ) );
		}	// get distance between two points
		static Grid getMidPoint( const Grid& A, const Grid& B){
			Grid mid;
			mid.setXY( (A.getX() + B.getX())/2, (A.getY() + B.getY())/2  );
			return mid;
		} 	// get the middle point of two points
	private:
		Number _Nd, _Nm, _Ns; // latitude (north) degree, minute, second
		Number _Ed, _Em, _Es; // lontitude (east) degree, minute, second
		Number _x, _y;        // 2 dimentional grid
		bool XY2LL();         // convert X Y axis to latitude and lontitude
		bool LL2XY();         // convert latitude and lontitude to X Y axis
};

class Vec2D
{
	public:
		Vec2D(){cur_x = 0.0;cur_y = 0.0;_x = 0.0;_y = 0.0;}
		//Vec2D(){_x = 0.0;_y = 0.0;}
		~Vec2D(){}
		// access functions and utility functions
		bool setXY( const Number&, const Number& );	// _x, _y
		bool setVD( const Number&, const Number& );	// value, direction
		bool setCurrXY( const Number&, const Number& );
		const Number& getX() const;	// _x
		const Number& getY() const;	// _y
		Vec2D rotate( const Number& ) const;	// rotate by "degree"
		Vec2D setCurrSpeed ( const Number&, const Number& );
		Number getValue() const;	// get value of velocity in "m/s"
		Number getAngle() const;	// get angle of direction in "degree"
		// operator overlaoding
		Vec2D operator + ( const Vec2D& ) const;	// add by vector
		Vec2D operator + ( const Number& ) const;	// add by a vector with value descinated, same direction
		Vec2D operator - ( const Vec2D& ) const;
		Vec2D operator * ( const Number& ) const;
		Vec2D operator / ( const Number& ) const;
		Vec2D operator = ( const Vec2D& );
		bool operator == ( const Vec2D& ) const;	// compare value and direction
		bool operator >  ( const Vec2D& ) const;	// compare value only
		bool operator <  ( const Vec2D& ) const;
		bool operator >= ( const Vec2D& ) const;
		bool operator <= ( const Vec2D& ) const;
		friend ostream& operator << ( ostream&, const Vec2D& );	// print as ( x, y )
	private:
	    Number cur_x,cur_y;
		Number _x, _y;
};

#endif // DATASTR_H

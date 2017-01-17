// File    : coeffHandler.cpp
// Author  : XQWang
// Update  : 6.3.2016
// Synopsis: Functions for class CoeffHandler

#include <iostream>
#include <cstdlib>
#include "coeffHandler.h"

using namespace std;

CoeffHandler::CoeffHandler()
{
	setLeewayWeight( 1 );
	setBuoyWeight( 1 );
	setLeewaySlope( 0.011 );
	setLeewayInter( 0.068 );
	setLeewayAngle( 30 );
	setSimTimeUnit( 5*SECOND );
	setDisTimeUnit( 5*MINUTE );
	setLeewayUpperBound( 2 );
	setLeewayLowerBound( -2 );
	setBuoyLowerBound( -2 );
	setBuoyUpperBound( 2 );
	setLeewayStep( 0.2 );
	setBuoyStep( 0.2 );
}
bool CoeffHandler::setLeewayWeight( const Number& value ) { _leewayWeight = value; return true; }
bool CoeffHandler::setBuoyWeight( const Number& value )  { _buoyWeight = value;  return true; }
bool CoeffHandler::setLeewaySlope( const Number& value ) { _leewaySlope = value; return true; }
bool CoeffHandler::setLeewayInter( const Number& value ) { _leewayInter = value * KNOTS; return true; }
bool CoeffHandler::setLeewayAngle( const Number& value ) { _leewayAngle = value; return true; }
bool CoeffHandler::setSimTimeUnit( const Number& value ) { _simTimeUnit = value; return true; }
bool CoeffHandler::setDisTimeUnit( const Number& value ) { _disTimeUnit = value; return true; }
bool CoeffHandler::setSimTotalTime( const Number& value ) { _simTotalTime = value; return true; }
bool CoeffHandler::setLeewayLowerBound( const Number& value ){ _leewayLowerBound = value; return true; }
bool CoeffHandler::setLeewayUpperBound( const Number& value ){ _leewayUpperBound = value; return true; }
bool CoeffHandler::setBuoyLowerBound( const Number& value ){ _buoyLowerBound = value; return true; }
bool CoeffHandler::setBuoyUpperBound( const Number& value ){ _buoyUpperBound = value; return true; }
bool CoeffHandler::setLeewayStep( const Number& value ){ _leewayStep = value; return true; }
bool CoeffHandler::setBuoyStep( const Number& value ){ _buoyStep = value; return true; }
const Number& CoeffHandler::getLeewayWeight() const { return _leewayWeight; }
const Number& CoeffHandler::getBuoyWeight()  const { return _buoyWeight; }
const Number& CoeffHandler::getLeewaySlope() const { return _leewaySlope; }
const Number& CoeffHandler::getLeewayInter() const { return _leewayInter; }
const Number& CoeffHandler::getLeewayAngle() const { return _leewayAngle; }
const Number& CoeffHandler::getSimTimeUnit() const { return _simTimeUnit; }
const Number& CoeffHandler::getDisTimeUnit() const { return _disTimeUnit; }
const Number& CoeffHandler::getSimTotalTime() const { return _simTotalTime; }
const Number& CoeffHandler::getLeewayLowerBound() const { return _leewayLowerBound; }
const Number& CoeffHandler::getLeewayUpperBound() const { return _leewayUpperBound; }
const Number& CoeffHandler::getBuoyLowerBound() const { return _buoyLowerBound; }
const Number& CoeffHandler::getBuoyUpperBound() const { return _buoyUpperBound; }
const Number& CoeffHandler::getLeewayStep() const { return _leewayStep; }
const Number& CoeffHandler::getBuoyStep() const { return _buoyStep; }

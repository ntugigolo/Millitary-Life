// File    : pathGenerator_ana.cpp
// Author  : XQWang
// Update  : 5.18.2016
// Synopsis: Member function analyze() for class PathGenerator

#include <iomanip>
#include "pathGenerator.h"


Number sqrtRoot( const Number& A, const Number& B )
{
	Number sum = ( A * A + B * B ) / 2;
	return sqrt( sum.getDouble() );
}

bool PathGenerator::analyze( ostream& write )
{
	if( !_currSet ){
		write << "Buoy Information Not Set!!\n"; return false;
	}
	if( !_windSet ){
		write << "Wind Information Not Set!!\n"; return false;
	}
	if( _start == Grid() ){
		write << "Initial Starting Point Not Set!!\n"; return false;
	}
	if( _piw == 0 ){
		write << "PIW Path Not Set!!\n"; return false;
	}

	write << "Coefficients Settings:\n";
	write << "Leeway Slope:    " << _coeff->getLeewaySlope() << endl;
	write << "Leeway Inter:    " << _coeff->getLeewayInter() << endl;
	write << "Leeway Angle:    " << _coeff->getLeewayAngle() << endl;
	write << endl;

	Number* distance = 0;
	distance = calDistance( _coeff->getLeewayWeight(), _coeff->getBuoyWeight() );
	printDistance( write, distance );

	Number LwLow   = _coeff->getLeewayLowerBound();
	Number LwUp    = _coeff->getLeewayUpperBound();
	Number BuoyLow = _coeff->getBuoyLowerBound();
	Number BuoyUp  = _coeff->getBuoyUpperBound();
	Number LWstep  = _coeff->getLeewayStep();
	Number Bstep   = _coeff->getBuoyStep();
	write << "LW   weight from " << LwLow << " to " << LwUp << " Step: " << LWstep << endl;
	write << "Buoy weight from " << BuoyLow << " to " << BuoyUp << " Step: " << Bstep<< endl;

	Number minDiffMid = distance[2];
	Number minDiffSqr = distance[4];
	Number minDiffEnd = distance[5];
	Number minDiffMid_LW  = _coeff->getLeewayWeight();
	Number minDiffSqr_LW  = _coeff->getLeewayWeight();
	Number minDiffEnd_LW  = _coeff->getLeewayWeight();
	Number minDiffMid_B   = _coeff->getBuoyWeight();
	Number minDiffSqr_B   = _coeff->getBuoyWeight();
	Number minDiffEnd_B   = _coeff->getBuoyWeight();

	delete distance; distance = 0;

	write << "\nComputing Minimum Distance...\n\n";

	for( Number LWindex = LwLow; LWindex <LwUp; LWindex += LWstep ){
		for( Number Bindex = BuoyLow; Bindex < BuoyUp; Bindex += Bstep ){
			distance = calDistance( LWindex, Bindex );
			if( distance[2] < minDiffMid ){
				minDiffMid = distance[2];
				minDiffMid_LW = LWindex;
				minDiffMid_B  = Bindex;
			}
			if( distance[4] < minDiffSqr ){
				minDiffSqr = distance[4];
				minDiffSqr_LW = LWindex;
				minDiffSqr_B  = Bindex;
			}
			if( distance[5] < minDiffEnd ){
				minDiffEnd = distance[5];
				minDiffEnd_LW = LWindex;
				minDiffEnd_B  = Bindex;
			}
			delete distance; distance = 0;
		}
	}

	write << "Minimum Distance of Middle Points: " << endl;
	distance = calDistance( minDiffMid_LW, minDiffMid_B );
	printDistance( write, distance );
	delete distance; distance = 0;

	write << "Minimum Avarage Distance (Square Root): " << endl;
	distance = calDistance( minDiffSqr_LW, minDiffSqr_B );
	printDistance( write, distance );
	delete distance; distance = 0;

	write << "Minimum Distance between End Points (Middle): " << endl;
	distance = calDistance( minDiffEnd_LW, minDiffEnd_B );
	printDistance( write, distance );
	delete distance; distance = 0;

	return true;
}

Number* PathGenerator::calDistance( const Number& lWeight, const Number& bWeight )
{
	Number* distance = new Number[6];
	/*
		[0]->positive angle
		[1]->negative angle
		[2]->zero angle
		[3]->mean of positive and negative
		[4]->square root of positive and negative
		[5]->distance between end points
	*/
	_coeff->setLeewayWeight( lWeight );
	_coeff->setBuoyWeight( bWeight );
	_sar = genPath( _start );
	distance[0] = comparePath( _sar,   _piw );
	distance[1] = comparePath( _sar+1, _piw );
	distance[2] = comparePath( _sar+2, _piw );
	distance[3] = ( distance[0] + distance[1] ) / 2;
	distance[4] = sqrtRoot( distance[0], distance[1] );
	distance[5] = distOfEnd( _sar+2, _piw );
	delete _sar; _sar = 0;
	return distance;
}
bool PathGenerator::printDistance( ostream& write, Number* distance) const
{
	if( distance == 0 ){
		write << "Distance Not Calculated...\n"; return false;
	}
	write << "Leeway Weight:   " << _coeff->getLeewayWeight() << endl;
	write << "Buoy   Weight:   " << _coeff->getBuoyWeight() << endl;
	write << "Positive Angle:  " << distance[0] << endl;
	write << "Negative Angle:  " << distance[1] << endl;
	write << "Middle Points :  " << distance[2] << endl;
	write << "Square Root   :  " << distance[4] << endl;
	write << "End Points    :  " << distance[5] << endl;
	write << endl;
	return true;
}

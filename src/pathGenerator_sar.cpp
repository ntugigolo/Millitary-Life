// File    : pathGenerator_sar.cpp
// Author  : XQWang
// Update  : 6.13.2016
// Synopsis: Member function calSAR() for class PathGenerator

#include "pathGenerator.h"

bool PathGenerator::calSAR()
{
	if( !_currSet ){
		cout << "Buoy Information Not Set!!\n"; return false;
	}
	if( !_windSet ){
		cout << "Wind Information Not Set!!\n"; return false;
	}
	if( _start == Grid() ){
		cout << "Initial Starting Point Not Set!!\n"; return false;
	}
	//cout << "Start From : " << _start << "\n\n";
	_sar = genPath( _start );
	if( _sar == 0 ){
		cout << "Somthing Wrong In Simulating The Paths...\n"; return false;
	}

	if( _outCsv == "" )
		genCsv( cout );
	else{
		ofstream write( _outCsv.c_str() );
		genCsv( write );
	}
	if( _outGpx == "" )
		genGpx( cout );
	else{
		ofstream write( _outGpx.c_str() );
		genGpx( write );
	}

	if( _sar ){
		delete _sar;
		_sar = 0;
	}
	return true;
}

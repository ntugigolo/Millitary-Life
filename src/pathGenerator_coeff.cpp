// File    : pathGenerator_coeff.cpp
// Author  : XQWang
// Update  : 5.16.2016
// Synopsis: Member function setCoeff() for class PathGenerator

#include "pathGenerator.h"

bool PathGenerator::setCoeff( string fileName )
{
	/*
		Parse the file and call functions by _coeff to set coefficients.
	*/
	ifstream read( fileName.c_str() );
	if( !read.is_open() ){
		cout << "File " << fileName << " not opened!!\n"; return false;
	}
	Number content;
	string buff;
	read >> buff;
	while( !read.eof() )
	{
		if      ( buff == ".leewayWeight" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setLeewayWeight( content );
		}
		else if ( buff == ".buoyWeight" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setBuoyWeight( content );
		}
		else if ( buff == ".leewaySlope" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setLeewaySlope( content );
		}
		else if ( buff == ".leewayInter" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setLeewayInter( content );
		}
		else if ( buff == ".leewayAngle" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setLeewayAngle( content );
		}
		else if ( buff == ".simTimeUnit" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setSimTimeUnit( content );
		}
		else if ( buff == ".simTotalTime" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setSimTotalTime( content );
		}
		else if ( buff == ".disTimeUnit" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setDisTimeUnit( content );
		}
		else if ( buff == ".leewayLowerBound" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setLeewayLowerBound( content );
		}
		else if ( buff == ".leewayUpperBound" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setLeewayUpperBound( content );
		}
		else if ( buff == ".buoyLowerBound" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setBuoyLowerBound( content );
		}
		else if ( buff == ".buoyUpperBound" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setBuoyUpperBound( content );
		}
		else if ( buff == ".leewayStep" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setLeewayStep( content );
		}
		else if ( buff == ".buoyStep" ){
			read >> buff; content = atof( buff.c_str() );
			_coeff->setBuoyStep( content );
		}
		else if ( buff == ".scopeSize" ){
			read >> buff; content = atof( buff.c_str() );
			_curr->setScopeSize( content );
		}
		else if ( buff == ".gridSize" ){
			read >> buff; content = atof( buff.c_str() );
			_curr->setGridSize( content );
		}
		else if ( buff == ".avgRange" ){
			read >> buff; content = atof( buff.c_str() );
			_curr->setAvgRange( content );
		}
		else if ( buff == ".avgNumber" ){
			read >> buff; content = atof( buff.c_str() );
			_curr->setAvgNumber( content );
		}
		else if( buff == ".fillNumber" ){
			read >> buff; content = atof( buff.c_str() );
			_curr->setFillNumber( content );
		}

		read >> buff;
	}
	return true;
}

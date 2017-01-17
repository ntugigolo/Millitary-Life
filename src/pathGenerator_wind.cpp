// File    : pathGenerator_wind.cpp
// Author  : XQWang
// Update  : 6.13.2016
// Synopsis: Member function setWind() for class PathGenerator

#include "pathGenerator.h"

bool PathGenerator::setWind( string fileName )
{
	/*
		Parse the file in buoyFormat.csv and convert the wind information into vector< Grid, Vec2D >.
		buoyFormat.cvs:
		[6] wind direction
		[7] wind speed
		[9] -[11] Lt
		[12]-[14] Ln
		[15],[16] Current Speed
		The first element of the pair is the position. The second element of the pair is the wind speed.
	*/
	ifstream read( fileName.c_str() );
	if( !read.is_open() ){
		cout << "File " << fileName << " Not Opened!!\n"; return false;
	}

	vector< pair<Grid,Vec2D> >* organized = new vector< pair<Grid,Vec2D> >;
	string* strArr = new string [18];
	string buff;
	Number speed;
	Number angle;
	Number* location = new Number[6];
	Vec2D wind;
	Grid  position;

	read >> buff;
	while( !read.eof() ){
		parseCSV( buff, strArr );
		if( buff[0] == ',' ){
			read >> buff;
			continue;
		}
		angle = atof( strArr[7].c_str() );
		speed = atof( strArr[8].c_str() ); angle = angle * -1 + 90 + 180;
		wind.setVD( speed, angle );
		for(int i=0; i<6; i++)
			location[i] = atof( strArr[10+i].c_str() );
		position.setLL( location );
		organized->push_back( make_pair( position, wind ) );
		read >> buff;
	}
	_wind->setWind( organized );
	delete   organized;
	delete[] strArr;
	delete[] location;
	_windSet = true;
	return true;
}

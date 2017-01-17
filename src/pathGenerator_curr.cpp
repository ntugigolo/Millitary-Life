// File    : pathGenerator_curr.cpp
// Author  : XQWang
// Update  : 5.16.2016
// Synopsis: Member function setCurrent() for class PathGenerator

#include "pathGenerator.h"

Number convertTime( string );
Number convertSpeed ( string);
bool fillPoint( const Grid&, const Grid&, const Vec2D&, vector< pair<Grid, Vec2D> >* );

bool PathGenerator::setCurrent( string fileName )
{
	/*
		Parse the file and convert the information into vector< pair<Grid, Vec2D> >*.
		buoyFormat.cvs:
		[8] record time
		[9] -[11] Lt
		[12]-[14] Ln
		[15],[16] Current Speed
		The input vector will be deleted after using.
	*/
	ifstream read( fileName.c_str() );
	if( !read.is_open() ){
		cout << "File " << fileName << " Not Opened!!\n"; return false;
	}
	string  buff;
	Number  time,x_speed,y_speed;
	Number* location = new Number[6];
	string* strArr   = new string [18];
	Grid    position;
	vector< Number > vecTime,vecX_speed,vecY_speed;
	vector< Grid > vecPoint;

	read >> buff;
	while( !read.eof() ){
		parseCSV( buff, strArr);
		if( buff[0] == ',' ){
			read >> buff;
			continue;
		}
		time = convertTime( strArr[9] );
		x_speed = convertSpeed( strArr[16] );
		y_speed = convertSpeed( strArr[17] );
		//x_speed = strArr[8]

		for( int i=0; i<6; i++)
			location[i] = atof( strArr[i+10].c_str() );
		position.setLL( location );
		vecTime.push_back( time );
		vecX_speed.push_back( x_speed);
		vecY_speed.push_back( y_speed);
		vecPoint.push_back( position );
		read >> buff;
	}
	if( vecTime.size() != vecPoint.size() || vecTime.empty() ){
		cout << "Something Wrong...\n"; return false;
	}

	vector< pair<Grid, Vec2D> >* organized = new vector< pair<Grid, Vec2D> >;

	Vec2D currSpeed;
	for( size_t i=0; i<vecTime.size(); i++ ){
            currSpeed = currSpeed.setCurrSpeed(vecX_speed[i],vecY_speed[i]);
		//if( vecTime[i] < vecTime[i+1] ){
		//currSpeed.setCurrXY(vecX_speed[i],vecY_speed[i]);
			//currSpeed = ( vecPoint[i+1] - vecPoint[i] ) / ( vecTime[i+1] - vecTime[i] );
			organized->push_back( make_pair( vecPoint[i], currSpeed ) );
			//	Below are optional to put additional points into the map.
			if (i < vecTime.size()-1) fillPoint( vecPoint[i], vecPoint[i+1], currSpeed, organized );
			// Above are optional to put additional points into the map.
		//}
	/*	else if( vecTime[i] > vecTime[i+1] ){
			organized->push_back( make_pair( vecPoint[i], currSpeed ) );
		}*/
	}
	//organized->push_back( make_pair( vecPoint[ vecPoint.size()-1 ], currSpeed ) );
	_curr->setCurrent( organized );
	delete   organized;
	delete[] location;
	delete[] strArr;
	_currSet = true;

	return true;
}

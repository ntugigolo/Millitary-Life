// File    : pathGenerator.cpp
// Author  : BYHuang
// Update  : 6.13.2015
// Synopsis: Member functions for class PathGenerator

#include <iomanip>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include "pathGenerator.h"
string _absroute = "";
PathGenerator::PathGenerator()
{
	_curr  = new CurrentMap;
	_wind  = new WindMap;
	_coeff = new CoeffHandler;
	_piw   = 0;
	_sar   = 0;
	_outCsv = _outGpx = "";
	_start.setXY( 0, 0 );
	_currSet = false;
	_windSet = false;
}
PathGenerator::~PathGenerator()
{
	if( _curr ) delete _curr;
	if( _wind ) delete _wind;
	if( _coeff) delete _coeff;
	if( _piw  ) delete _piw;
	if( _sar  ) delete _sar;
}
bool PathGenerator::setOutCsv( string fileName ){
	_outCsv = fileName; return true;
}
bool PathGenerator::setOutGpx( string fileName ){
	_outGpx = fileName; return true;
}
bool PathGenerator::setInitialPoint( string fileName )
{
	ifstream read( fileName.c_str() );
	if( !read.is_open() ){
		cout << "File " << fileName << " Not Opened!!\n"; return false;
	}
	string buff; read >> buff;
	string* strArr = new string[6];
	Number* location = new Number[6];
	parseCSV( buff, strArr );
	for( int i=0; i<6; i++ )
		location[i] = atof( strArr[i].c_str() );
	_start.setLL( location );
	delete[] strArr;
	delete[] location;
	return true;
}
PATH* PathGenerator::genPath( const Grid& start ) const
{
	/*
		Generate three paths, with positive and negative leeway angle, respectively, from
		start point. Update the location every simTimeUnit. Save the location every
		disTimeUnit. Simulate simTotalTime seconds.
		PATH* : [0]->positive angle
		        [1]->negative angle
	*/
	PATH* routes = new vector< pair< Number, Grid > >[2];
	routes[0].push_back( make_pair(0, start) );
	routes[1].push_back( make_pair(0, start) );
	Vec2D* speed    = new Vec2D[2];
	Grid*  location = new Grid[2];
	location[0] =  start;
	location[1] =  start;

	Number simTotalTime = _coeff->getSimTotalTime();
	Number simTimeUnit  = _coeff->getSimTimeUnit();
	Number disTimeUnit  = _coeff->getDisTimeUnit();
	for( Number time = 0; time < simTotalTime; ){
		time += simTimeUnit;
		for(int i=0; i<2; i++){
                //cout<<"FirstLocation:"<<location[i]<<endl;
			getTotalSpeed( location[i], speed );
			//cout<<"End"<<endl;
			location[i] = location[i] + speed[i] * simTimeUnit;
			if( (time/disTimeUnit).getCeiling() - (time/disTimeUnit).getFloor() == 0  )
				routes[i].push_back( make_pair(time, location[i]) );
		}
	}
	delete[] location; location = 0;
	delete[] speed;    speed = 0;
	return routes;
}
bool PathGenerator::getTotalSpeed( const Grid& point, Vec2D* totalSpeed ) const
{
	/*
		Speed = LW + TWC
		Here we use buoy current to represent TWC, which may differs from the theory.
		To put wind current and other factors in, you can add it in a similar way.
	*/
	Vec2D  buoy   = _curr->getSpeed( point );
	Vec2D* leeway = new Vec2D[2];
	getLeewaySpeed( point, leeway );// [0]:rotate positive angle
												// [1]:rotate negative angle
	totalSpeed[0] = buoy      * _coeff->getBuoyWeight()		// buoy with weight
	              + leeway[0] * _coeff->getLeewayWeight();	// leeway positive with weight
	totalSpeed[1] = buoy      * _coeff->getBuoyWeight()		// buoy with weight
	              + leeway[1] * _coeff->getLeewayWeight();	// leeway negative with weight
	delete[] leeway; leeway = 0;
	return true;
}

bool PathGenerator::getLeewaySpeed( const Grid& position, Vec2D* leewayPosNeg ) const
{
	/*
		Implemented according to the theory.
		LW = windSpeed *  slope + y-inter                 if( windSpeed > 6 knots)
		LW = windSpeed * (slope + y-inter/6)              if( windSpeed < 6 knots)
	*/
	string tune_wind = _absroute + "/Tune_Wind.txt";
    ifstream read( tune_wind.c_str() );
    if( !read.is_open() ){
	cout << "File " << tune_wind << " not opened!!\n"; return false;
    }
    Number content;
    string buff;
    read >> buff;
    content = atof( buff.c_str() );

    Number threshold = content * KNOTS;

	Vec2D windSpeed = _wind->getSpeed( position );
	Vec2D leewaySpeed;
	if( windSpeed.getValue() >= threshold )
		leewaySpeed = windSpeed * _coeff->getLeewaySlope() + _coeff->getLeewayInter();
	else
		leewaySpeed = windSpeed * ( _coeff->getLeewaySlope() + _coeff->getLeewayInter()/content );
	leewayPosNeg[0] = leewaySpeed.rotate( _coeff->getLeewayAngle() );			// rotate +angle
	leewayPosNeg[1] = leewaySpeed.rotate( _coeff->getLeewayAngle() * -1 );	// rotate -angle
	return true;
}
Number PathGenerator::convertSpeed( string speed ) const
{
    return atof(speed.c_str());
}
Number PathGenerator::convertTime( string raw ) const
{
	/* Functionality
		Input raw data should be like "ab:cd", output number will be ab*60+cd.
	*/
	string minute;
	string second;
	size_t index = 2;
	for(size_t i=0; i<raw.size(); i++)
		if( raw[i] == ':' ) index = i;
	minute = raw.substr( 0, index );
	second = raw.substr( index +1 );
	return atoi(minute.c_str()) * 3600 + atoi(second.c_str()) * 60;
}
bool PathGenerator::fillPoint( const Grid& head, const Grid& end, const Vec2D& speed, vector< pair<Grid, Vec2D> >* organized ) const
{
	/* Functionality
		Add additional points between the two point with the specified current speed.
	*/
	int numToAdd = 10;

	Grid intermediate;
	Number x;
	Number y;

	for( int i=0; i<numToAdd; i++ ){
		x = head.getX() + (end.getX()-head.getX())*i/numToAdd;
		y = head.getY() + (end.getY()-head.getY())*i/numToAdd;
		intermediate.setXY( x, y );
		//cout<<"IniSetPos:"<<head<<endl;
		//cout<<"IniSetPos:"<<head.getX()<<endl;
		//cout<<"IniSetPos:"<<head.getY()<<endl;
		organized->push_back( make_pair( intermediate, speed ) );
	}
	return true;
}
bool PathGenerator::genCsv( ostream& write ) const
{
	//write << "Path with Leeway Angle:  " << _coeff->getLeewayAngle() << " Degree:\n";
	printPath( write, _sar );
	//write << "Path with Leeway Angle: -" << _coeff->getLeewayAngle() << " Degree:\n";
	printPath( write, _sar+1 );
//	write << "Path with middle points:\n";
//	printPath( write, _sar+2 );
	return true;
}
void PathGenerator::printPath( ostream& write, PATH* route ) const
{
	for( size_t i=0; i<route->size(); i++ ){
		if( write == cout ){
			write << "Time(m):" << setw(3) << (*route)[i].first/MINUTE << "  ";
			write << "Location: " << (*route)[i].second << endl;
		}
		else // print in csv format
			write << (*route)[i].first/MINUTE << "," << (*route)[i].second << endl;
	}
	write << endl;
}
bool PathGenerator::genGpx( ostream& write ) const
{
	write << "<?xml version=\"1.0\"?>" << endl;
   write << "<gpx version=\"1.1\" creator=\"BYHuang\" >" << endl;

   for( int i=0; i<2; i++ )
   	plotPathGpx( write, _sar+i );

   write << "</gpx>";
	return true;
}
string pathType  = "101";
string pathColor = "Red";
//string pathName  = "SAR";
bool PathGenerator::plotPathGpx( ostream& write, PATH* route ) const
{
	Number Lt;
	Number Ln;
	vector< pair<Number, Number> > path;
	for( size_t i=0; i<route->size(); i++){
		Lt = (*route)[i].second.getLtLn().first;
		Ln = (*route)[i].second.getLtLn().second;
		path.push_back( make_pair( Lt, Ln ) );
	}
	string pathName = _outGpx.substr( 7, _outGpx.size()-11 );
//	string pathName = _outGpx.substr( _outGpx.size()-4 );
	write << "\t<rte>" << endl;
	write << "\t\t<name>" << pathName << "</name>" << endl;
	write << "\t\t<extensions>" << endl;
	write << "\t\t\t<opencpn:style width=\"5\" style=\"" << pathType <<"\"/>" << endl;
	write << "\t\t\t<gpxx:RouteExtension>" << endl;
	write << "\t\t\t\t<gpxx:DisplayColor>" << pathColor << "</gpxx:DisplayColor>" << endl;
	write << "\t\t\t</gpxx:RouteExtension>" << endl;
	write << "\t\t</extensions>" << endl;
	for( size_t i=0; i<path.size(); i++ ){
		write << "\t\t<rtept lat=\"" << setprecision(10) << path[i].first;
		write << "\" lon=\"" << setprecision(10) << path[i].second << "\">" << endl;
		if( i == path.size()-1 ){
			write << "\t\t\t<name>" << pathName << "</name>" << endl;
		}
		write << "\t\t\t<sym>circle</sym>" << endl;
		write << "\t\t</rtept>" << endl;
	}
	write << "\t</rte>" << endl;

	return true;
}
bool PathGenerator::setCompare( string fileName )
{
	if( _piw ) return false;
	_piw = readPath( fileName );
	if( _piw == 0 || _piw->empty() ){
		cout << "PIW path wrong!!\n"; return false;
	}
	_start = (*_piw)[0].second;
	return true;
}
PATH* PathGenerator::readPath( string fileName ) const
{
	ifstream read( fileName.c_str() );
	if( !read.is_open() ){
		cout << "File " << fileName << " Not Open!!\n"; return 0;
	}
	string buff;
	Number  time;
	Number* location = new Number[6];
	Grid    point;
	read >> buff;
	Number  initalTime = convertTime( buff );
	PATH*   route = new PATH;
	while( !read.eof() )
	{
		time = convertTime( buff ) - initalTime;
		for( int i=0; i<6; i++ ){
			read >> buff; location[i] = atof( buff.c_str() );
		}
		point.setLL( location );
		route->push_back( make_pair( time, point ) );
		read >> buff;
	}
	return route;
}
Number timeDiffer( const pair< Number, Grid >& a, const pair< Number, Grid >& b )
{
	Number difference = a.first - b.first;
	if( difference >= 0 ) return difference;
	else                  return difference * -1;
}
Number PathGenerator::comparePath( PATH* predict, PATH* model ) const
{
	Number difference  = 0;
	Number nearestTime = 0;
	Number differTime  = 0;
	Number count       = 0;
	size_t index = 0;
	for( size_t i=1; i<model->size(); i++ ){
		nearestTime = timeDiffer( (*predict)[0], (*model)[i] );
		for( size_t j=index; j<predict->size(); j++ ){
			differTime = timeDiffer( (*predict)[j], (*model)[i] );
			if( differTime < nearestTime ){
				nearestTime = differTime;
				index = j;
			}
		}
//		difference += Grid::getDistance( (*predict)[index].second, (*model)[i].second ) / (*model)[i].first;
//		count = count + 1;
		difference += Grid::getDistance( (*predict)[index].second, (*model)[i].second );
		count += (*model)[i].first;
	}
	difference = difference / count;
	return difference * HOUR;
}
Number PathGenerator::distOfEnd( PATH* predict, PATH* model ) const
{
	Number nearestTime = timeDiffer( (*model)[ model->size()-1 ], (*predict)[0] );
	Number differTime;
	size_t index = 0;
	for( size_t i=0; i<predict->size(); i++ ){
		differTime = timeDiffer( (*predict)[i], (*model)[ model->size()-1 ] );
		if( differTime < nearestTime ){
			nearestTime = differTime;
			index = i;
		}
	}
	return Grid::getDistance( (*predict)[index].second, (*model)[ model->size()-1 ].second );
}
bool PathGenerator::parseCSV( string csv, string* container ) const
{
	if( container == 0 ) return false;
	size_t prev_cmID = -1;
	size_t post_cmID = 0;
	size_t strID = 0;
	for( size_t i=0; i<csv.size(); i++ ){
		if( csv[i] == ',' || i == csv.size()-1 ){
			if( csv[i] == ',' ) post_cmID = i;
			else                post_cmID = i+1;
            container[strID] = csv.substr( prev_cmID+1, post_cmID - prev_cmID - 1 );
			strID++;
			prev_cmID = post_cmID;
		}
	}
	return true;
}

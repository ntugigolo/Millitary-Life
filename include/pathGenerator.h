// File    : pathGenerator.h
// Author  : XQWang
// Update  : 6.13.2016
// Synopsis: Header file for class PathGenerator.

#ifndef PATHGENERATOR_H
#define PATHGENERATOR_H

#include <string>
#include <fstream>
#include <utility>
#include <vector>

#include "dataStr.h"
#include "coeffHandler.h"
#include "windMap.h"
#include "currentMap.h"

#define PATH vector< pair< Number, Grid > >

extern string _absroute;
class PathGenerator
{
	public:
		PathGenerator();
		~PathGenerator();
		bool setCoeff( string fileName );
		/* Functionality:
			Parse the raw data in the file, and set them in CoeffHandler, CurrentMap and WindMap.
			Define in file "pathGenerator_coeff.cpp".
		*/
		bool setCurrent( string fileName );
		/* Functionality:
			Parse the raw data into two vectors ( Grid & Vec2D ) and pass it to CurrentMap.
			Define in file "pathGenerator_curr.cpp".
		*/
		bool setWind( string fileName );
		/* Functionality:
			Parse the raw data into two vector ( Grid & Vec2D) and pass it to WindMap.
			Define in file "pathGenerator_wind.cpp"
		*/
		bool setInitialPoint( string fileName );
		/* Functionality:
			Parse the latitude and longitude in the file and set them as the initial point.
			Define in file "pathGenerator.cpp"
		*/
		bool setOutCsv( string fileName );
		/* Functionality:
			Set output SAR.csv file name for calSAR.
			Define in file "pathGenerator.cpp"
		*/
		bool setOutGpx( string fileName );
		/* Functionality:
			Set output SAR.gpx file name for calSAR.
			Define in file "pathGenerator.cpp"
		*/
		bool calSAR();
		/* Functionality:
			Calculate SAR(the two paths) and print it on the file (or on the screen).
			Define in file "pathGenerator_sar.cpp"
		*/

		// Functions below are optional for research use. No need for webpage engine.
		bool analyze( ostream& write );
		/* Functionality: (This is optional for research use)
			Automatically calculate the avarage distance under difference coefficient settings.
			Define in file "pathGenerator_ana.cpp"
		*/
		bool setCompare( string fileName );
		/* Functionality: (This it optional for research use)
			Read the PIW file and compare with the predicted paths.
			Define in file "pathGenerator.cpp"
		*/
		//static string        _absroute;
	private:
		CoeffHandler* _coeff;
		CurrentMap*   _curr;
		WindMap*      _wind;
		Grid          _start;
		PATH*         _piw;
		PATH*         _sar;
		bool          _currSet;
		bool          _windSet;
		string        _outCsv;
		string        _outGpx;

		PATH* genPath( const Grid& startingPoint ) const;
		/* Functionality:
			Generate paths from starting point and save the three predicted paths.
			PATH* : [0]->positive leeway angle
			        [1]->negative leeway angle
			        [2]->middle points
			Note: the paths are newed in the function, remember to delete[] after using.
			Define in file "pathGenerator.cpp"
		*/
		bool getTotalSpeed( const Grid& location, Vec2D* totalSpeed ) const;
		/* Functionality:
			Calculate total speed including buoy and leeway, optional for other factors.
			Vec2D* : [0]->total speed with positive LW
			         [1]->total speed with negative LW
			Note: the speed will NOT be newed inside the function, handle it outside.
			Define in file "pathGenerator.cpp"
		*/
		bool getLeewaySpeed( const Grid& location, Vec2D* leewaySpeed ) const;
		/* Functionality:
			Calculate leeway speed.
			Vec2D* : [0]->leeway speed with positive LW angle (right is 0; up is 90)
			         [1]->leeway speed with negative LW angle (right is 0; up is 90)
			Note: the speed will NOT be newed inside the function, handle it outside.
			Define in file "pathGenerator.cpp"
		*/
		bool parseCSV( string cvs, string* container ) const;
		/* Functionality:
			An utility function. Parse the string in csv string into container.
			Define in file "pathGenerator.cpp"
		*/
		void printPath( ostream& write = cout, PATH* route = 0 ) const;
		/* Functionality:
			Print out the path on the screen or to the file descinated.
			Define in file "pathGenerator.cpp"
		*/
		bool genCsv( ostream& ) const;
		/* Functionality:
			Create the excel csv file.
			Define in file "pathGenerator.cpp".
		*/
		bool genGpx( ostream& ) const;
		/* Functionality:
			Create the openCPN gpx file.
			Define in file "pathGenerator.cpp".
		*/
		bool plotPathGpx( ostream& write = cout, PATH* route = 0 ) const;
		/* Functionality:
			Create the rte block for openCPN gpx file.
			Define in file "pathGenerator.cpp".
		*/
		bool fillPoint( const Grid&, const Grid&, const Vec2D&, vector< pair<Grid, Vec2D> >* ) const;
		/* Functionality:
			An optional utility function, add more data points in the buoy current map between raw data.
			Define in file "pathGenerator.cpp"
		*/
		Number convertTime( string ) const;
		/* Functionality:
			An utility function, ac:cd -> ab*3600 + cd * 60
			Define in file "pathGenerator.cpp"
		*/
        Number convertSpeed( string ) const;

		// Functions below are optional for research use. No need for webpage engine.
		PATH* readPath( string fileName ) const;
		/* Functionality: (This it optional for research use)
			Read the file and return the path. ( Used to compare real path and predicted paths )
			Define in file "pathGenerator.cpp"
		*/
		Number comparePath( PATH*, PATH* ) const;
		/* Functionality: (This it optional for research use)
			Compare two paths and calculate the avarage distance per hour.
			PATH* predict, PATH* model
			Define in file "pathGenerator.cpp"
		*/
		Number distOfEnd( PATH*, PATH* ) const;
		/* Functionality: (This it optional for research use)
			Calculate the distance between the end points of the model path and the
			corresponding point of the predict path.
			PATH* predict, PATH* model
			Define in file "pathGenerator.cpp"
		*/
		Number* calDistance( const Number& lWeight, const Number& bWeight );
		/* Functionality: (This it optional for research use)
			Calculate distance between various path with piw based on the given leeway weight
			and buoy weight.
			Number* : [0]->positive angle
			          [1]->negative angle
			          [2]->middle point
			          [3]->mean of positive and negative
			          [4]->square root of positive and negative
			          [5]->distance between end points of middle path and piw
			Define in file "pathGenerator.cpp"
		*/
		bool printDistance( ostream& write = cout, Number* distance = 0 ) const;
		/* Functionality: (This it optional for research use)
			Print out the distance on the screen or to the file descinated.
			Notes:
			Also print the coefficients at the time this function is called.
			Define in file "pathGenerator.cpp"
		*/
};

#endif // PATHGENERATOR_H

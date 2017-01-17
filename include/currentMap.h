// File    : currentMap.h
// Author  : XQWang
// Update  : 5.15.2016
// Synopsis: Header file for class CurrentMap, which maintains the buoy information.

#ifndef CURRENTMAP_H
#define CURRENTMAP_H

#include <vector>
#include "dataStr.h"

#define DATA pair< Grid, Vec2D >

using namespace std;

class CurrentMap
{
	public:
		CurrentMap();
		~CurrentMap();
		Vec2D getSpeed( const Grid& ) const;
		/* Functionality:
			Find the current speed on that point ( or nearest ) and return.
		*/
		bool setCurrent( vector< pair<Grid, Vec2D> >* );
		/* Functionality:
			Set current map from a vector, which contains "some" data points.
			The first element of a DATA is the position.
			The second element of a DATA is the speed of that point.
		*/
		bool setScopeSize( const Number& );
		bool setGridSize( const Number& );
		bool setAvgRange( const Number& );
		bool setAvgNumber( const Number& );
		bool setFillNumber( const Number& );
		Number getScopeSize() const;
		Number getGridSize() const;
		Number getAvgRange() const;
		Number getAvgNumber() const;
		Number getFillNumber() const;
	private:
		Number _scopeSize;	// Default 10 km
		Number _gridSize;		// Default 25 m
		Number _avgRange;		// Default 50 m
		Number _avgNumber;	// Default 5
		Number _fillNumber;	// Default 5
		vector< DATA > _map;	// Data container
};

#endif // CURRENTMAP_H

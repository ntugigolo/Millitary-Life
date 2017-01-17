// File    : windMap.cpp
// Author  : XQWang
// Update  : 2.3.2015
// Synopsis: Member functions for class WindMap

#include "windMap.h"

bool WindMap::setWind( vector< pair<Grid, Vec2D> >* wind )
{
	if( wind == 0 || wind->empty() ){
		cout << "Fail Setting Wind\n"; return false;
	}
	for( size_t i=0; i<wind->size(); i++ )
		_map.push_back( (*wind)[i] );

	return true;
}
Vec2D WindMap::getSpeed( const Grid& position ) const
{
	if( _map.empty() ){
		cout << "Wind Information Not Set!!\n"; return Vec2D();
	}
	// Find the nearest data point and return its wind speed.
	Vec2D speed = _map[0].second;
	Number shortestDistance = Grid::getDistance( position, _map[0].first );
	for( size_t i=0; i<_map.size(); i++ ){
		if( Grid::getDistance( position, _map[i].first ) < shortestDistance ){
			shortestDistance = Grid::getDistance( position, _map[i].first );
			speed = _map[i].second;
		}
	}
	return speed;
}

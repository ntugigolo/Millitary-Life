// File    : windMap.h
// Author  : XQWang
// Update  : 6.3.2016
// Synopsis: Header file for class WindMap. Cosidering the data format we now have, the
//				 program only deal with information from one place and non-realistic timing.

#ifndef WINDMAP_H
#define WINDMAP_H

#include <vector>
#include "dataStr.h"

using namespace std;

class WindMap
{
	public:
		WindMap(){}
		~WindMap(){}

		Vec2D getSpeed( const Grid& ) const;
		/* Functionality:
			Find the wind speed on that point (or nearest) and return.
		*/
		bool setWind( vector< pair< Grid, Vec2D > >* );
		/* Functionality:
			Set wind map from vector, which contains location and speed information.
			The input vector will NOT be deleted.
		*/
	private:
		vector< pair< Grid, Vec2D > > _map;
};

#endif // WINDMAP_H

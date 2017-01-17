// File    : currentMap.cpp
// Author  : XQWang
// Update  : 6.13.2016
// Synopsis: Member functions for class CurrentMap
#include <fstream>
#include "currentMap.h"
#include "pathGenerator.h"
#define KEY pair< Number, Vec2D >
//extern string _absroute;
CurrentMap::CurrentMap()
{
	setScopeSize( 10 );
	setGridSize( 25 );
	setAvgRange( 50 );
	setAvgNumber( 5 );
	setFillNumber( 5 );
}
CurrentMap::~CurrentMap(){}
bool CurrentMap::setCurrent( vector<DATA>* newData )
{
	assert( newData->size() != 0 );
	for(size_t i=0; i<newData->size(); i++)
		_map.push_back( (*newData)[i] );

	return true;
}
Vec2D CurrentMap::getSpeed( const Grid& position ) const
{
	Vec2D currSpeed; currSpeed.setXY(0,0);
	Number shortestDistance = 10*KM;
	/*
		Take the weighted avarage from nearby points.
		Weight : The inverse of distance
		Nearby : Defined by avgRange
		Average: Include "avgNumber" points
	*/
	int avgRange  = getAvgRange().getInt();
	int avgNumber = getAvgNumber().getInt();
	vector< KEY > top;
	KEY dummy = make_pair( shortestDistance, currSpeed );
	for( int i=0; i<avgNumber; i++ )
		top.push_back( dummy );
	Number tempDist = 0;
	int insertIndex = 0;
	int count = 0;
    int cc = 0;
	int never_small = 1;
	for( size_t i=0; i<_map.size(); i++){
            cc += 1;
		tempDist = Grid::getDistance( position, _map[i].first );
		insertIndex = avgNumber;
		for( int j=avgNumber-1; j>=0; j-- )
			if( tempDist < top[j].first ) insertIndex = j;
		if( insertIndex == avgNumber );
		else if( insertIndex < avgNumber ){
			for( int j=avgNumber-1; j>insertIndex; j--)
				top[j] = top[j-1];
			top[insertIndex] = make_pair( tempDist, _map[i].second );
		}
		assert( insertIndex <= avgNumber );
            if (tempDist < shortestDistance) {
            never_small = 0;
        }
	}

	/*for (int i = 0;i <avgNumber;i++){
    cout<<"Number:"<<i<<endl;
    cout<<"Sephiria:"<<top[i].first<<endl;
    cout<<"Sephiria_Total:"<<top[i].second<<endl;}*/

	if (never_small){
        string out_error = _absroute + "/Error_Msg_SAR.txt";
        ofstream outfile; outfile.open(out_error.c_str());
        outfile << "Out of range !"; outfile.close(); exit(1);
	}
	else{
        string out_error = _absroute + "/Error_Msg_SAR.txt";
        ofstream outfile; outfile.open(out_error.c_str());
        outfile << ""; outfile.close();
	}
	assert( (int)(top.size()) == (int)avgNumber );
	Number weight = 0;
	if( top[0].first == 0 ){
		for( int i=0; i<avgNumber; i++ ){
			if( top[i] != dummy && top[i].first == 0 ){
				currSpeed = currSpeed + top[i].second;
				weight    = weight + 1;
			}
		}
	}
	else{
		while( weight == 0 ){
			for( int i=0; i<avgNumber; i++ ){
				if( top[i] != dummy && top[i].first < avgRange ){ //dummy 初始距離,若一開始就超過shortestDistance,則進不了if
					currSpeed = currSpeed + top[i].second/top[i].first;
					/*cout<<"Sephiria:"<<top[i].second<<endl;
					cout<<"Sephiria_Total:"<<currSpeed<<endl;*/
					weight    = weight + 1/top[i].first.getDouble();
				}
			}
			avgRange = avgRange + getAvgRange().getInt();
		}
	}
	assert( weight != 0 );
	/*cout<<"_weight:"<<weight<<endl;
	cout<<"_Speed:"<<currSpeed<<endl;*/
	currSpeed = currSpeed / weight;
    //cout<<"YAYA_Total_YAYAYAYAYA:"<<currSpeed<<endl;

	return currSpeed;
}
bool CurrentMap::setScopeSize( const Number&  value ) { _scopeSize = value * KM;  return true; }
bool CurrentMap::setGridSize(  const Number&  value ) { _gridSize  = value * M;   return true; }
bool CurrentMap::setAvgRange(  const Number&  value ) { _avgRange  = value * M;   return true; }
bool CurrentMap::setAvgNumber( const Number&  value ) { _avgNumber = value;       return true; }
bool CurrentMap::setFillNumber( const Number& value ) { _fillNumber = value;      return true; }
Number CurrentMap::getScopeSize() const { return _scopeSize; }
Number CurrentMap::getGridSize()  const { return _gridSize; }
Number CurrentMap::getAvgRange()  const { return _avgRange; }
Number CurrentMap::getAvgNumber() const { return _avgNumber; }
Number CurrentMap::getFillNumber() const{ return _fillNumber; }

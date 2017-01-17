// File    : coeffHandler.h
// Author  : XQWang
// Update  : 5.15.2016
// Synopsis: Header files for class CoeffHandler, which handles coefficients XD

#ifndef COEFFHANDLER_H
#define COEFFHANDLER_H

#include <dataStr.h>

using namespace std;

class CoeffHandler
{
   public:
		CoeffHandler();
      ~CoeffHandler(){}
      // setting functions
      bool setLeewayWeight( const Number& );
      bool setBuoyWeight( const Number& );
      bool setLeewaySlope( const Number& );
      bool setLeewayInter( const Number& );
      bool setLeewayAngle( const Number& );
      bool setSimTimeUnit( const Number& );
      bool setDisTimeUnit( const Number& );
      bool setSimTotalTime( const Number& );
      bool setLeewayLowerBound( const Number& );
      bool setLeewayUpperBound( const Number& );
      bool setBuoyLowerBound( const Number& );
      bool setBuoyUpperBound( const Number& );
      bool setLeewayStep( const Number& );
      bool setBuoyStep( const Number& );
      // access functions
      const Number& getLeewayWeight() const;
      const Number& getBuoyWeight() const;
      const Number& getLeewaySlope() const;
      const Number& getLeewayInter() const;
      const Number& getLeewayAngle() const;  // degree
      const Number& getSimTimeUnit() const;  // second
      const Number& getDisTimeUnit() const;  // second
      const Number& getSimTotalTime() const; // second
      const Number& getLeewayLowerBound() const;
      const Number& getLeewayUpperBound() const;
      const Number& getBuoyLowerBound() const;
      const Number& getBuoyUpperBound() const;
      const Number& getLeewayStep() const;
      const Number& getBuoyStep() const;
   private:
   	// Weighting for Leeway Diviation, Buoy Current, and other TWC weightings
   	Number _leewayWeight;
   	Number _buoyWeight;
   	// Coefficents for Leeway
   	Number _leewaySlope;
   	Number _leewayInter;
   	Number _leewayAngle;
      // Coefficents for simulation
      Number _simTimeUnit;    // time to update new speed and new position
      Number _disTimeUnit;    // time to display locations of the route
      Number _simTotalTime;   // total time to simulate
      // Coefficients for analysis
      Number _leewayLowerBound;  // lower bound for LWcoeff to search for minimum distance
      Number _leewayUpperBound;  // upper bound for LWcoeff to search for minimum distance
      Number _buoyLowerBound;    // lower bound for Bcoeff to search for minimum distance
      Number _buoyUpperBound;    // upper bound for Bcoeff to search for minimum distance
      Number _leewayStep;        // step to add LWcoeff
      Number _buoyStep;          // step to add Bcoeff

};

#endif // COEFFHANDLER_H

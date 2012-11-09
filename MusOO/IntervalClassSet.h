#ifndef IntervalClassSet_h
#define IntervalClassSet_h

//============================================================================
/**
 Abstract base class representing an interval class set.
 
 @author	Johan Pauwels
 @date		20121109
 */
//============================================================================
#include <set>
#include <string>
#include "Interval.h"


class IntervalClassSet
{
public:
    
	friend class LerdahlDistance; //to access m_IntervalList in LerdahlDistance::basicSpace()
	/** Default constructor. */
	IntervalClassSet();
    //IntervalClassSet(IntervalClassSet inIntervalClassSet) = default
	virtual ~IntervalClassSet();
    
	// operator= default implementation
	virtual bool operator==(const IntervalClassSet& inIntervalClassSet) const;
	virtual bool operator!=(const IntervalClassSet& inIntervalClassSet) const;
	virtual bool operator<(const IntervalClassSet& inIntervalClassSet) const;
    
	bool isMajor() const;
	bool isMinor() const;
    
    /**
        Checks if this set contains all the notes of a given IntervalClassSet

        @param		inIntervalClassSet		the set contained by this set
        @return		true if this set contains all interval classes of <inIntervalClassSet>
    */
	const bool contains(const IntervalClassSet inIntervalClassSet) const;
	
	const bool contains(const Interval& inInterval) const;
    
	const size_t cardinality() const;
    
	/**
         Returns the interval of a given diatonic number
         @param	inDiatonicNumber	the diatonic numnber the interval should have
         @return an Interval of the given diatonic number or Interval::none() if there's no such interval in the current Set
     */
	const Interval& getDiatonicInterval(const size_t inDiatonicNumber) const;
    
    virtual const bool hasSpelling() const;
    virtual IntervalClassSet& ignoreSpelling();
    
	virtual IntervalClassSet& addInterval(const Interval& inInterval);
	virtual IntervalClassSet& deleteInterval(const Interval& inInterval);
	virtual IntervalClassSet& replaceInterval(const Interval& inIntervalToReplace, const Interval& inReplacementInterval);
    
protected:
	
	// only used for construction of static IntervalClassSets
	IntervalClassSet(const Interval* inIntervalList, const int inNumOfIntervals);
    
	virtual const std::string str() const;
    
	std::set<Interval> m_IntervalList;
    
private:
    
};

#endif	// #ifndef IntervalClassSet_h

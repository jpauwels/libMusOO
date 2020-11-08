#ifndef Set_h
#define Set_h

//============================================================================
/**
 Abstract base class representing a set.
 
 @author	Johan Pauwels
 @date		20121109
 */
//============================================================================
#include <set>
#include <string>

namespace MusOO
{
template<typename Interval, typename BaseT>
class Set
{
public:
    
    template <typename OtherInterval, typename OtherT> friend class Set; // to access m_set from other Set types
    
	/** Default constructor. */
	Set();
    template <typename OtherT>
    Set(const Set<Interval, OtherT>& inSet);
	virtual ~Set() = 0;
    
	// operator= default implementation
	virtual bool operator==(const Set<Interval, BaseT>& inSet) const;
	virtual bool operator!=(const Set<Interval, BaseT>& inSet) const;
	virtual bool operator<(const Set<Interval, BaseT>& inSet) const;
    
    /**
        Checks if this set contains all the notes of a given Set

        @param		inSet		the set contained by this set
        @return		true if this set contains all interval classes of <inSet>
    */
	const bool contains(const BaseT& inSet) const;
	
	const bool contains(const Interval& inInterval) const;
    
	const size_t cardinality() const;
    
	/**
         Returns the interval of a given diatonic number
         @param	inDiatonicNumber	the diatonic numnber the interval should have
         @return an Interval of the given diatonic number or Interval::none() if there's no such interval in the current Set
     */
	const Interval& getDiatonicInterval(const size_t inDiatonicNumber) const;
    
    virtual const bool hasSpelling() const;
    virtual BaseT withoutSpelling() const;
    virtual BaseT& ignoreSpelling();

	virtual BaseT& add(const Interval& inInterval);
	virtual BaseT& remove(const Interval& inInterval);
	virtual BaseT& replace(const Interval& inIntervalToReplace, const Interval& inReplacementInterval);
    
    typedef typename std::set<Interval>::iterator iterator;
    typedef typename std::set<Interval>::const_iterator const_iterator;
    
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    
protected:
	
	// only used for construction of static Sets
	Set(const Interval* inIntervalList, const int inNumOfIntervals);
    
	virtual const std::string str() const;
    
	std::set<Interval> m_set;
    
private:
    
};
}

#include "MusOO/Set.hpp"
#endif	// #ifndef Set_h

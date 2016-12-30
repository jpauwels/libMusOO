#ifndef Set_hpp
#define Set_hpp

//============================================================================
/**
 Implementation file for Set.h
 
 @author	Johan Pauwels
 @date		20121109
 */
//============================================================================

// Includes
#include "MusOO/Set.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iterator>

using std::ostringstream;
using std::set;
using std::invalid_argument;
using std::includes;
using namespace MusOO;

/*******************************/
/* Constructors and destructor */
/*******************************/
template<typename Interval>
Set<Interval>::Set()
{
}

template<typename Interval>
Set<Interval>::Set(const Interval* inIntervalList, const int inNumOfIntervals)
: m_set(inIntervalList, inIntervalList+inNumOfIntervals)
{
}

template<typename Interval>
Set<Interval>::~Set()
{
}

/*************/
/* Operators */
/*************/
template<typename Interval>
bool Set<Interval>::operator==(const Set<Interval>& inSet) const
{
	return m_set == inSet.m_set;
}

template<typename Interval>
bool Set<Interval>::operator!=(const Set<Interval>& inSet) const
{
	return m_set != inSet.m_set;
}

template<typename Interval>
bool Set<Interval>::operator<(const Set<Interval>& inSet) const
{
	return m_set < inSet.m_set;
}

/*************/
/* Observers */
/*************/
template<typename Interval>
const size_t Set<Interval>::cardinality() const
{
	return m_set.size();
}

template<typename Interval>
const Interval& Set<Interval>::getDiatonicInterval(const size_t inDiatonicNumber) const
{
	for (typename set<Interval>::const_iterator it = m_set.begin(); it != m_set.end(); ++it)
	{
		if (it->diatonicNumber() == inDiatonicNumber)
		{
			return *it;
		}
	}
	return Interval::none();
}

template<typename Interval>
const std::string Set<Interval>::str() const
{
	ostringstream theSetStream;
	theSetStream << "{";
	if (!m_set.empty())
	{
		theSetStream << m_set.begin()->circleStepsCW();
        for (typename set<Interval>::const_iterator i = ++m_set.begin(); i != m_set.end(); ++i)
        {
            theSetStream << ",";
            theSetStream << i->circleStepsCW();
        }
	}
	theSetStream << "}";
	return theSetStream.str();
}

template<typename Interval>
const bool Set<Interval>::hasSpelling() const
{
    for (typename set<Interval>::const_iterator it = m_set.begin(); it != m_set.end(); ++it)
    {
        if (!it->hasSpelling())
        {
            return false;
        }
    }
    return true;
    //all_of(m_set(), m_set(), hasSpelling())
}

template<typename Interval>
const bool Set<Interval>::contains(const Set<Interval>& inSet) const
{
	return includes(m_set.begin(), m_set.end(), inSet.m_set.begin(), inSet.m_set.end());
}

template<typename Interval>
const bool Set<Interval>::contains(const Interval& inInterval) const
{
	return m_set.count(inInterval) > 0;
}

/*************/
/* Modifiers */
/*************/
template<typename Interval>
Set<Interval>& Set<Interval>::ignoreSpelling()
{
    if (hasSpelling())
    {
        set<Interval> theSet;
        std::transform(m_set.begin(), m_set.end(), std::inserter(theSet, theSet.begin()), std::mem_fun_ref(&Interval::withoutSpelling));
        m_set = theSet;
    }
	return *this;
}

template<typename Interval>
Set<Interval>& Set<Interval>::add(const Interval& inInterval)
{
    if (hasSpelling() && !inInterval.hasSpelling())
    {
        throw invalid_argument("The interval class to be added should have a spelling");
    }
	m_set.insert(inInterval);
	return *this;
}

template<typename Interval>
Set<Interval>& Set<Interval>::remove(const Interval& inInterval)
{
    if (hasSpelling() && !inInterval.hasSpelling())
    {
        throw invalid_argument("The interval class to be deleted should have a spelling");
    }
	size_t theNumOfDeletes = m_set.erase(inInterval);
	if (theNumOfDeletes != 1)
	{
		throw invalid_argument("Interval to be deleted does not exist");
	}
	return *this;
}

template<typename Interval>
Set<Interval>& Set<Interval>::replace(const Interval& inIntervalToReplace, const Interval& inReplacementInterval)
{
    if (hasSpelling() && (!inIntervalToReplace.hasSpelling() || !inReplacementInterval.hasSpelling()))
    {
        throw invalid_argument("Both the interval to replace and the replacement interval should have a spelling");
    }
	size_t theNumOfDeletes = m_set.erase(inIntervalToReplace);
	if (theNumOfDeletes != 1)
	{
		throw invalid_argument("Interval to be replaced does not exist in chord");
	}
	m_set.insert(inReplacementInterval);
	return *this;
}

#endif	// #ifndef Set_hpp

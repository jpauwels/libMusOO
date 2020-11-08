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

using namespace MusOO;

/*******************************/
/* Constructors and destructor */
/*******************************/
template<typename Interval, typename BaseT>
Set<Interval, BaseT>::Set()
{
}

template<typename Interval, typename BaseT>
template <typename OtherT>
Set<Interval, BaseT>::Set(const Set<Interval, OtherT>& inSet)
: m_set(inSet.m_set)
{
}

template<typename Interval, typename BaseT>
Set<Interval, BaseT>::Set(const Interval* inIntervalList, const int inNumOfIntervals)
: m_set(inIntervalList, inIntervalList+inNumOfIntervals)
{
}

template<typename Interval, typename BaseT>
Set<Interval, BaseT>::~Set()
{
}

/*************/
/* Operators */
/*************/
template<typename Interval, typename BaseT>
bool Set<Interval, BaseT>::operator==(const Set<Interval, BaseT>& inSet) const
{
	return m_set == inSet.m_set;
}

template<typename Interval, typename BaseT>
bool Set<Interval, BaseT>::operator!=(const Set<Interval, BaseT>& inSet) const
{
	return m_set != inSet.m_set;
}

template<typename Interval, typename BaseT>
bool Set<Interval, BaseT>::operator<(const Set<Interval, BaseT>& inSet) const
{
	return m_set < inSet.m_set;
}

/*************/
/* Observers */
/*************/
template<typename Interval, typename BaseT>
const size_t Set<Interval, BaseT>::cardinality() const
{
	return m_set.size();
}

template<typename Interval, typename BaseT>
const Interval& Set<Interval, BaseT>::getDiatonicInterval(const size_t inDiatonicNumber) const
{
	for (typename Set<Interval, BaseT>::const_iterator it = m_set.begin(); it != m_set.end(); ++it)
	{
		if (it->diatonicNumber() == inDiatonicNumber)
		{
			return *it;
		}
	}
	return Interval::none();
}

template<typename Interval, typename BaseT>
const std::string Set<Interval, BaseT>::str() const
{
	std::ostringstream theSetStream;
	theSetStream << "{";
	if (!m_set.empty())
	{
		theSetStream << m_set.begin()->circleStepsCW();
        for (typename Set<Interval, BaseT>::const_iterator i = ++m_set.begin(); i != m_set.end(); ++i)
        {
            theSetStream << ",";
            theSetStream << i->circleStepsCW();
        }
	}
	theSetStream << "}";
	return theSetStream.str();
}

template<typename Interval, typename BaseT>
const bool Set<Interval, BaseT>::hasSpelling() const
{
    for (typename Set<Interval, BaseT>::const_iterator it = m_set.begin(); it != m_set.end(); ++it)
    {
        if (!it->hasSpelling())
        {
            return false;
        }
    }
    return true;
    //all_of(m_set(), m_set(), hasSpelling())
}

template<typename Interval, typename BaseT>
BaseT Set<Interval, BaseT>::withoutSpelling() const
{
    return BaseT(static_cast<const BaseT&>(*this)).ignoreSpelling();
}

template<typename Interval, typename BaseT>
const bool Set<Interval, BaseT>::contains(const BaseT& inSet) const
{
	return std::includes(m_set.begin(), m_set.end(), inSet.m_set.begin(), inSet.m_set.end());
}

template<typename Interval, typename BaseT>
const bool Set<Interval, BaseT>::contains(const Interval& inInterval) const
{
	return m_set.count(inInterval) > 0;
}

/*************/
/* Modifiers */
/*************/
template<typename Interval, typename BaseT>
BaseT& Set<Interval, BaseT>::ignoreSpelling()
{
    if (hasSpelling())
    {
        std::set<Interval> theSet;
        std::transform(m_set.begin(), m_set.end(), std::inserter(theSet, theSet.begin()), std::mem_fn(&Interval::withoutSpelling));
        m_set = theSet;
    }
	return static_cast<BaseT&>(*this);
}

template<typename Interval, typename BaseT>
BaseT& Set<Interval, BaseT>::add(const Interval& inInterval)
{
    if (m_set.size() > 0 && hasSpelling() && !inInterval.hasSpelling())
    {
        throw std::invalid_argument("The interval class to be added should have a spelling");
    }
	m_set.insert(inInterval);
	return static_cast<BaseT&>(*this);
}

template<typename Interval, typename BaseT>
BaseT& Set<Interval, BaseT>::remove(const Interval& inInterval)
{
    if (hasSpelling() && !inInterval.hasSpelling())
    {
        throw std::invalid_argument("The interval class to be deleted should have a spelling");
    }
	size_t theNumOfDeletes = m_set.erase(inInterval);
	if (theNumOfDeletes != 1)
	{
		throw std::invalid_argument("Interval to be deleted does not exist");
	}
	return static_cast<BaseT&>(*this);
}

template<typename Interval, typename BaseT>
BaseT& Set<Interval, BaseT>::replace(const Interval& inIntervalToReplace, const Interval& inReplacementInterval)
{
    if (hasSpelling() && (!inIntervalToReplace.hasSpelling() || !inReplacementInterval.hasSpelling()))
    {
        throw std::invalid_argument("Both the interval to replace and the replacement interval should have a spelling");
    }
	size_t theNumOfDeletes = m_set.erase(inIntervalToReplace);
	if (theNumOfDeletes != 1)
	{
		throw std::invalid_argument("Interval to be replaced does not exist in chord");
	}
	m_set.insert(inReplacementInterval);
	return static_cast<BaseT&>(*this);
}

template<typename Interval, typename BaseT>
typename Set<Interval, BaseT>::iterator Set<Interval, BaseT>::begin()
{
    return m_set.begin();
}

template<typename Interval, typename BaseT>
typename Set<Interval, BaseT>::const_iterator Set<Interval, BaseT>::begin() const
{
    return m_set.begin();
}

template<typename Interval, typename BaseT>
typename Set<Interval, BaseT>::iterator Set<Interval, BaseT>::end()
{
    return m_set.end();
}

template<typename Interval, typename BaseT>
typename Set<Interval, BaseT>::const_iterator Set<Interval, BaseT>::end() const
{
    return m_set.end();
}

#endif	// #ifndef Set_hpp

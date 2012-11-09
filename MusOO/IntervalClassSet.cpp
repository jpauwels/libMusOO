//============================================================================
/**
 Implementation file for IntervalClassSet.h
 
 @author	Johan Pauwels
 @date		20121109
 */
//============================================================================

// Includes
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "IntervalClassSet.h"

using std::ostringstream;
using std::set;
using std::invalid_argument;
using std::includes;

/*******************************/
/* Constructors and destructor */
/*******************************/
IntervalClassSet::IntervalClassSet()
{
}

IntervalClassSet::IntervalClassSet(const Interval* inIntervalList, const int inNumOfIntervals)
: m_IntervalList(inIntervalList, inIntervalList+inNumOfIntervals)
{
}

IntervalClassSet::~IntervalClassSet()
{
}

/*************/
/* Operators */
/*************/
bool IntervalClassSet::operator==(const IntervalClassSet& inIntervalClassSet) const
{
	return m_IntervalList == inIntervalClassSet.m_IntervalList;
}

bool IntervalClassSet::operator!=(const IntervalClassSet& inIntervalClassSet) const
{
	return m_IntervalList != inIntervalClassSet.m_IntervalList;
}

bool IntervalClassSet::operator<(const IntervalClassSet& inIntervalClassSet) const
{
	return m_IntervalList < inIntervalClassSet.m_IntervalList;
}

/*************/
/* Observers */
/*************/
bool IntervalClassSet::isMajor() const
{
	return m_IntervalList.count(Interval::majorThird()) > 0;
}

bool IntervalClassSet::isMinor() const
{
	return m_IntervalList.count(Interval::minorThird()) > 0;
}

const size_t IntervalClassSet::cardinality() const
{
	return m_IntervalList.size();
}

const Interval& IntervalClassSet::getDiatonicInterval(const size_t inDiatonicNumber) const
{
	for (set<Interval>::const_iterator it = m_IntervalList.begin(); it != m_IntervalList.end(); ++it)
	{
		if (it->diatonicNumber() == inDiatonicNumber)
		{
			return *it;
		}
	}
	return Interval::none();
}

const std::string IntervalClassSet::str() const
{
	ostringstream theIntervalClassSetStream;
	theIntervalClassSetStream << "[";
	if (!m_IntervalList.empty())
	{
		theIntervalClassSetStream << m_IntervalList.begin()->circleStepsCW();
        for (set<Interval>::const_iterator i = ++m_IntervalList.begin(); i != m_IntervalList.end(); ++i)
        {
            theIntervalClassSetStream << ",";
            theIntervalClassSetStream << i->circleStepsCW();
        }
	}
	theIntervalClassSetStream << "]";
	return theIntervalClassSetStream.str();
}

const bool IntervalClassSet::hasSpelling() const
{
    for (set<Interval>::const_iterator it = m_IntervalList.begin(); it != m_IntervalList.end(); ++it)
    {
        if (!it->hasSpelling())
        {
            return false;
        }
    }
    return true;
    //all_of(m_IntervalList(), m_IntervalList(), hasSpelling())
}

const bool IntervalClassSet::contains(const IntervalClassSet inIntervalClassSet) const
{
	return includes(m_IntervalList.begin(), m_IntervalList.end(), inIntervalClassSet.m_IntervalList.begin(), inIntervalClassSet.m_IntervalList.end());
}

const bool IntervalClassSet::contains(const Interval& inInterval) const
{
	return m_IntervalList.count(inInterval) > 0;
}

/*************/
/* Modifiers */
/*************/
IntervalClassSet& IntervalClassSet::ignoreSpelling()
{
    if (hasSpelling())
    {
        for (set<Interval>::iterator it = m_IntervalList.begin(); it != m_IntervalList.end(); ++it)
        {
            Interval theIntervalWithoutSpelling = Interval(*it).ignoreSpelling();
            m_IntervalList.erase(it);
            m_IntervalList.insert(theIntervalWithoutSpelling);
        }
    }
	return *this;
}

IntervalClassSet& IntervalClassSet::addInterval(const Interval& inInterval)
{
    if (hasSpelling() && !inInterval.hasSpelling())
    {
        throw invalid_argument("The interval class to be added should have a spelling");
    }
	m_IntervalList.insert(inInterval);
	return *this;
}

IntervalClassSet& IntervalClassSet::deleteInterval(const Interval& inInterval)
{
    if (hasSpelling() && !inInterval.hasSpelling())
    {
        throw invalid_argument("The interval class to be deleted should have a spelling");
    }
	size_t theNumOfDeletes = m_IntervalList.erase(inInterval);
	if (theNumOfDeletes != 1)
	{
		throw invalid_argument("Interval to be deleted does not exist");
	}
	return *this;
}

IntervalClassSet& IntervalClassSet::replaceInterval(const Interval& inIntervalToReplace, const Interval& inReplacementInterval)
{
    if (hasSpelling() && (!inIntervalToReplace.hasSpelling() || !inReplacementInterval.hasSpelling()))
    {
        throw invalid_argument("Both the interval to replace and the replacement interval should have a spelling");
    }
	size_t theNumOfDeletes = m_IntervalList.erase(inIntervalToReplace);
	if (theNumOfDeletes != 1)
	{
		throw invalid_argument("Interval to be replaced does not exist in chord");
	}
	m_IntervalList.insert(inReplacementInterval);
	return *this;
}

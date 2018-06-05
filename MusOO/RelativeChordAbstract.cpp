//============================================================================
/**
	Implementation file for RelativeChordAbstract.h

	@author		Johan Pauwels
	@date		20101222
*/
//============================================================================

// Includes
#include "MusOO/RelativeChordAbstract.h"
#include "MusOO/ChordAbstract.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

using std::string;
using std::ostringstream;
using namespace MusOO;

RelativeChordAbstract::RelativeChordAbstract()
: m_RootInterval(SimpleInterval::undefined()), m_Type(ChordType::none())
{
}

RelativeChordAbstract::RelativeChordAbstract(const SimpleInterval& inRootInterval, const ChordType& inType)
: m_RootInterval(inRootInterval), m_Type(inType)
{
}

RelativeChordAbstract::RelativeChordAbstract( const std::string& inDegree, const ChordType& inChordType, const Mode& inMode )
: m_RootInterval(inDegree, inMode), m_Type(inChordType)
{
}

RelativeChordAbstract::~RelativeChordAbstract()
{
}

bool RelativeChordAbstract::operator==(const RelativeChordAbstract& inRelativeChord) const
{
	return m_RootInterval == inRelativeChord.m_RootInterval && m_Type == inRelativeChord.m_Type;
}

bool RelativeChordAbstract::operator!=(const RelativeChordAbstract& inRelativeChord) const
{
	return m_RootInterval != inRelativeChord.m_RootInterval || m_Type != inRelativeChord.m_Type;
}

bool RelativeChordAbstract::operator<(const RelativeChordAbstract& inRelativeChord) const
{
	if (m_RootInterval != inRelativeChord.m_RootInterval)
	{
		return m_RootInterval < inRelativeChord.m_RootInterval;
	}
	else
	{
		return m_Type < inRelativeChord.m_Type;
	}
}

const SimpleInterval& RelativeChordAbstract::rootInterval() const
{
	return m_RootInterval;
}

const ChordType& RelativeChordAbstract::type() const
{
	return m_Type;
}

const bool RelativeChordAbstract::isTrueRelativeChord() const
{
	return m_Type != ChordType::none();
}

const bool RelativeChordAbstract::hasSpelling() const
{
    return m_RootInterval.hasSpelling() && m_Type.hasSpelling();
}

RelativeChordAbstract& RelativeChordAbstract::ignoreSpelling()
{
    if (isTrueRelativeChord())
    {
        m_RootInterval.ignoreSpelling();
        m_Type.ignoreSpelling();
    }
    return *this;
}

//============================================================================
/**
	Implementation file for RelativeChord.h

	@author		Johan Pauwels
	@date		20101222
*/
//============================================================================

// Includes
#include "MusOO/RelativeChord.h"
#include "MusOO/Chord.h"
#include "MusOO/Key.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

using std::string;
using std::ostringstream;
using namespace MusOO;

const RelativeChord& RelativeChord::silence()
{
	static const RelativeChord silence(SimpleInterval::silence(), ChordType::none());
	return silence;
}

const RelativeChord& RelativeChord::none()
{
	static const RelativeChord none(SimpleInterval::none(), ChordType::none());
	return none;
}

const RelativeChord& RelativeChord::unknown()
{
	static const RelativeChord unknown(SimpleInterval::undefined(), ChordType::none());
	return unknown;
}

RelativeChord::RelativeChord()
: m_RootInterval(SimpleInterval::undefined()), m_Type(ChordType::none())
{
}

RelativeChord::RelativeChord(const SimpleInterval& inRootInterval, const ChordType& inType)
: m_RootInterval(inRootInterval), m_Type(inType)
{
}

RelativeChord::RelativeChord(const Key& inKey, const Chord& inChord)
: m_RootInterval(inKey.tonic(), inChord.root()), m_Type(inChord.type())
{
	if (inChord == Chord::silence())
	{
		*this = silence();
	}
	else if (inChord == Chord::none())
	{
		*this = none();
	}
	else if (inChord == Chord::undefined())
	{
		*this = unknown();
	}
	if (inKey == Key::silence())
	{
		std::runtime_error("Cannot deduce relative chord when key is silence");
	}
}

RelativeChord::RelativeChord( const std::string& inDegree, const ChordType& inChordType, const Mode& inMode )
	: m_RootInterval(inDegree, inMode), m_Type(inChordType)
{
}

RelativeChord::~RelativeChord()
{
	// Nothing to do...
}

bool RelativeChord::operator==(const RelativeChord& inRelativeChord) const
{
	return m_RootInterval == inRelativeChord.m_RootInterval && m_Type == inRelativeChord.m_Type;
}

bool RelativeChord::operator!=(const RelativeChord& inRelativeChord) const
{
	return m_RootInterval != inRelativeChord.m_RootInterval || m_Type != inRelativeChord.m_Type;
}

bool RelativeChord::operator<(const RelativeChord& inRelativeChord) const
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

const SimpleInterval& RelativeChord::rootInterval() const
{
	return m_RootInterval;
}

const ChordType& RelativeChord::type() const
{
	return m_Type;
}

const bool RelativeChord::isTrueRelativeChord() const
{
	return m_Type != ChordType::none();
}

const bool RelativeChord::hasSpelling() const
{
    return m_RootInterval.hasSpelling() && m_Type.hasSpelling();
}

RelativeChord& RelativeChord::ignoreSpelling()
{
    if (isTrueRelativeChord())
    {
        m_RootInterval.ignoreSpelling();
        m_Type.ignoreSpelling();
    }
    return *this;
}

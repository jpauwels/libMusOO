//============================================================================
/**
	Implementation file for Chord.h
	
	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================

// Includes
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>
#include "Chord.h"
#include "Key.h"

using std::vector;
using std::set;
using std::ostringstream;

const Chord& Chord::none()
{
	static const Chord none(Chroma::none(), ChordType::none());
	return none;
}
const Chord& Chord::silence()
{
	static const Chord silence(Chroma::silence(), ChordType::none());
	return silence;
}
const Chord& Chord::undefined()
{
	static const Chord undefined(Chroma::undefined(), ChordType::none());
	return undefined;
}

Chord::Chord()
{

}

Chord::Chord(const Chroma& inRoot, const ChordType& inChordType)
: m_Root(inRoot), m_Type(inChordType)
{
}

Chroma& Chord::root()
{
	return m_Root;
}

const Chroma& Chord::root() const
{
	return m_Root;
}

ChordType& Chord::type()
{
	return m_Type;
}

const ChordType& Chord::type() const
{
	return m_Type;
}

//const std::string Chord::str() const
//{
//	if (*this == Chord::silence())
//	{
//		return "S";
//	}
//	else if (*this == Chord::noChord())
//	{
//		return "N";
//	}
//	else if (*this == Chord::unknown())
//	{
//		return "X";
//	}
//	return m_Root.str() + " " + m_Type.str();
//}

Chord::~Chord()
{

}

bool Chord::operator==(const Chord& inChord) const
{
	return m_Root == inChord.m_Root && m_Type == inChord.m_Type;
}

bool Chord::operator!=(const Chord& inChord) const
{
	return m_Root != inChord.m_Root || m_Type != inChord.m_Type;
}

const bool Chord::isTrueChord() const
{
	return m_Type != ChordType::none();
}

const bool Chord::isDiatonic(const Key& inKey) const
{
	if (!isTrueChord())
	{
		return false;
	}
	set<Chroma> theChordChromas = chromas();
    set<Chroma> theKeyChromas = inKey.chromas();
	for (set<Chroma>::const_iterator it = theChordChromas.begin(); it != theChordChromas.end(); ++it)
	{
		// return false as soon as one chroma is not part of key
		if (find(theKeyChromas.begin(), theKeyChromas.end(), *it) == theKeyChromas.end())
		{
			return false;
		}
	}
	return true;
}

void Chord::addChroma(const Chroma& inChroma)
{
	type().addInterval(Interval(root(), inChroma));
}

void Chord::deleteChroma(const Chroma& inChroma)
{
	type().deleteInterval(Interval(root(), inChroma));
}

void Chord::replaceChroma(const Chroma& inChromaToReplace, const Chroma& inReplacementChroma)
{
	type().replaceInterval(Interval(root(), inChromaToReplace), Interval(root(), inReplacementChroma));
}

void Chord::addBass(const Chroma& inChroma)
{
	type().addBass(Interval(root(), inChroma));
}

void Chord::deleteBass(const Chroma& inChroma)
{
	type().deleteBass();
}

const std::set<Chroma> Chord::chromas() const
{
	set<Chroma> theChromaSet;
	for (set<Interval>::const_iterator it = m_Type.m_IntervalList.begin(); it != m_Type.m_IntervalList.end(); ++it)
	{
		theChromaSet.insert(Chroma(m_Root, *it));
	}
	return theChromaSet;
}

const std::set<Chroma> Chord::commonChromas(const Chord& inOtherChord) const
{
    set<Chroma> theChromaSet = chromas();
    set<Chroma> theOtherChromaSet = inOtherChord.chromas();
    set<Chroma> theCommonChromas;
	set_intersection(theChromaSet.begin(), theChromaSet.end(), theOtherChromaSet.begin(), theOtherChromaSet.end(), std::inserter(theCommonChromas, theCommonChromas.end()));
    return theCommonChromas;
}

const Chroma Chord::bass(bool inDefaultToRoot) const
{
	Chroma theBassChroma(m_Root, m_Type.m_Bass);
    if (inDefaultToRoot && theBassChroma == Chroma::undefined())
    {
        theBassChroma = root();
    }
    return theBassChroma;
}

const bool Chord::hasSpelling() const
{
    return m_Root.hasSpelling() && m_Type.hasSpelling();
}

Chord& Chord::ignoreSpelling()
{
    if (isTrueChord())
    {
        m_Root.ignoreSpelling();
        m_Type.ignoreSpelling();
    }
    return *this;
}

//============================================================================
/**
	Implementation file for Key.h
	
	@author		Johan Pauwels
	@date		20100322
*/
//============================================================================

// Includes
#include <string>
#include <vector>
#include <set>
#include "Key.h"
#include "Chord.h"
#include "RelativeChord.h"

using std::string;
using std::vector;
using std::set;

const Key& Key::silence()
{
	static const Key silence(Chroma::silence(), Mode::none());
	return silence;
}

const Key& Key::none()
{
	static const Key none(Chroma::none(), Mode::none());
	return none;
}

const Key& Key::undefined()
{
	static const Key undefined(Chroma::undefined(), Mode::none());
	return undefined;
}

Key::Key()
: m_Tonic(Chroma::undefined()), m_Mode(Mode::none())
{
}

Key::Key(const Chroma& inTonic, const Mode& inMode)
: m_Tonic(inTonic), m_Mode(inMode)
{
}

Key::~Key()
{
}

Chroma& Key::tonic()
{
	return m_Tonic;
}

const Chroma& Key::tonic() const
{
	return m_Tonic;
}

Mode& Key::mode()
{
	return m_Mode;
}

const Mode& Key::mode() const
{
	return m_Mode;
}

//const std::string Key::str() const
//{
//	if (m_Tonic == Chroma::silence())
//	{
//		return "Silence";
//	}
//	else if (m_Tonic == Chroma::noChroma())
//	{
//		return "NoKey";
//	}
//	else if (m_Tonic == Chroma::undefined())
//	{
//		return "Undefined";
//	}
//	return m_Tonic.str() + " " + m_Mode.str();
//}

bool Key::operator==(const Key& inKey) const
{
	return m_Mode == inKey.m_Mode && m_Tonic == inKey.m_Tonic;
}

bool Key::operator!=(const Key& inKey) const
{
	return m_Mode != inKey.m_Mode || m_Tonic != inKey.m_Tonic;
}

const std::set<Chroma> Key::chromas() const
{
	set<Chroma> theChromaSet;
	for (set<Interval>::const_iterator it = m_Mode.m_IntervalList.begin(); it != m_Mode.m_IntervalList.end(); ++it)
	{
		theChromaSet.insert(Chroma(m_Tonic, *it));
	}
	return theChromaSet;
}

const size_t Key::chromaticCOFDistance(const Key& inKey) const
{
	return mode().chromaticCOFDistance(Interval(tonic(), inKey.tonic()), inKey.mode());
}

Chord Key::chord(const RelativeChord& inRelChord) const
{
	//return Chord(tonic()+inRelChord.rootInterval(), inRelChord.type());
	return Chord(Chroma(tonic(),inRelChord.rootInterval()), inRelChord.type());
}

RelativeChord Key::relativeChord(const Chord& inChord) const
{
	return RelativeChord(Interval(tonic(), inChord.root()), inChord.type());
}

const bool Key::isTrueKey() const
{
	return m_Mode != Mode::none();
}

const bool Key::hasSpelling() const
{
    return m_Tonic.hasSpelling() && m_Mode.hasSpelling();
}

Key& Key::ignoreSpelling()
{
    if (isTrueKey())
    {
        m_Tonic.ignoreSpelling();
        m_Mode.ignoreSpelling();
    }
    return *this;
}

void Key::addChroma(const Chroma& inChroma)
{
	mode().addInterval(Interval(tonic(), inChroma));
}

void Key::deleteChroma(const Chroma& inChroma)
{
	mode().deleteInterval(Interval(tonic(), inChroma));
}

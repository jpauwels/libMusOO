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

const Chord& Chord::noChord()
{
	static const Chord noChord(Chroma::noChroma(), ChordType::none());
	return noChord;
}
const Chord& Chord::silence()
{
	static const Chord silence(Chroma::silence(), ChordType::none());
	return silence;
}
const Chord& Chord::unknown()
{
	static const Chord unknown(Chroma::undefined(), ChordType::none());
	return unknown;
}

Chord::Chord(const Chord& inChord)
: m_Root(inChord.m_Root), m_Type(inChord.m_Type)
{
}

Chord::Chord()
{

}

Chord::Chord(const Chroma& inRoot, const ChordType& inChordType)
: m_Root(inRoot), m_Type(inChordType)
{
}

Chord& Chord::operator=(const Chord& inChord)
{
	//check for self reference
	if (this != &inChord)
	{
		m_Root = inChord.m_Root;
		m_Type = inChord.m_Type;
	}
	return *this;
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

const bool Chord::isRealChord() const
{
	return m_Type != ChordType::none();
}

const bool Chord::isDiatonic(const Key& inKey) const
{
	if (!isRealChord())
	{
		return false;
	}
	vector<Chroma> theChordChromas = chromaList();
	vector<Chroma> theKeyChromas = inKey.chromaList();
	for (vector<Chroma>::const_iterator it = theChordChromas.begin(); it != theChordChromas.end(); ++it)
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

const std::vector<Chroma> Chord::chromaList() const
{
	vector<Chroma> theChromaList;
	for (set<Interval>::const_iterator it = m_Type.m_Formula.begin(); it != m_Type.m_Formula.end(); ++it)
	{
		theChromaList.push_back(Chroma(m_Root, *it));
	}
	return theChromaList;
}

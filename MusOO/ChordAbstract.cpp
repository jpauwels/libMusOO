//============================================================================
/**
	Implementation file for ChordAbstract.h
	
	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================

// Includes
#include "MusOO/ChordAbstract.h"
#include "MusOO/Key.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>
#include <iterator>

using std::vector;
using std::set;
using std::ostringstream;

using namespace MusOO;

ChordAbstract::ChordAbstract()
{
}

ChordAbstract::ChordAbstract(const Chroma& inRoot, const ChordType& inChordType)
: m_Root(inRoot), m_Type(inChordType)
{
}

Chroma& ChordAbstract::root()
{
	return m_Root;
}

const Chroma& ChordAbstract::root() const
{
	return m_Root;
}

ChordType& ChordAbstract::type()
{
	return m_Type;
}

const ChordType& ChordAbstract::type() const
{
	return m_Type;
}

ChordAbstract::~ChordAbstract()
{
}

bool ChordAbstract::operator==(const ChordAbstract& inChordAbstract) const
{
	return m_Root == inChordAbstract.m_Root && m_Type == inChordAbstract.m_Type;
}

bool ChordAbstract::operator!=(const ChordAbstract& inChordAbstract) const
{
	return m_Root != inChordAbstract.m_Root || m_Type != inChordAbstract.m_Type;
}

bool ChordAbstract::operator<(const ChordAbstract& inChordAbstract) const
{
    return m_Root < inChordAbstract.m_Root || m_Type < inChordAbstract.m_Type;
}

const bool ChordAbstract::isTrueChord() const
{
	return m_Type != ChordType::none() && m_Type != ChordType::undefined();
}

const bool ChordAbstract::isDiatonic(const Key& inKey) const
{
	if (!isTrueChord())
	{
		return false;
	}
    if (inKey.mode() == Mode::minorGeneral())
    {
        return isDiatonic(Key(inKey.tonic(), Mode::minorNatural())) || isDiatonic(Key(inKey.tonic(), Mode::minorHarmonic())) || isDiatonic(Key(inKey.tonic(), Mode::minorMelodic()));
    }
	set<Chroma> theChordAbstractChromas = chromas();
    set<Chroma> theKeyChromas = inKey.chromas();
    vector<Chroma> theNonDiatonicChromas(cardinality());
    if (std::set_difference(theChordAbstractChromas.begin(), theChordAbstractChromas.end(), theKeyChromas.begin(), theKeyChromas.end(), theNonDiatonicChromas.begin()) - theNonDiatonicChromas.begin() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ChordAbstract::addChroma(const Chroma& inChroma)
{
	type().addInterval(SimpleInterval(root(), inChroma));
}

void ChordAbstract::deleteChroma(const Chroma& inChroma)
{
	type().deleteInterval(SimpleInterval(root(), inChroma));
}

void ChordAbstract::replaceChroma(const Chroma& inChromaToReplace, const Chroma& inReplacementChroma)
{
	type().replaceInterval(SimpleInterval(root(), inChromaToReplace), SimpleInterval(root(), inReplacementChroma));
}

void ChordAbstract::addBass(const Chroma& inChroma)
{
	type().addBass(SimpleInterval(root(), inChroma));
}

void ChordAbstract::deleteBass(const Chroma& inChroma)
{
	type().deleteBass();
}

const std::set<Chroma> ChordAbstract::chromas() const
{
	set<Chroma> theChromaSet;
	for (set<SimpleInterval>::const_iterator it = m_Type.begin(); it != m_Type.end(); ++it)
	{
		theChromaSet.insert(Chroma(m_Root, *it));
	}
	return theChromaSet;
}

const std::set<Chroma> ChordAbstract::commonChromas(const ChordAbstract& inOtherChordAbstract) const
{
    set<Chroma> theChromaSet = chromas();
    set<Chroma> theOtherChromaSet = inOtherChordAbstract.chromas();
    set<Chroma> theCommonChromas;
	set_intersection(theChromaSet.begin(), theChromaSet.end(), theOtherChromaSet.begin(), theOtherChromaSet.end(), std::inserter(theCommonChromas, theCommonChromas.end()));
    return theCommonChromas;
}

const Chroma ChordAbstract::bass(bool inDefaultToRoot) const
{
	Chroma theBassChroma(m_Root, m_Type.m_Bass);
    if (inDefaultToRoot && theBassChroma == Chroma::undefined())
    {
        theBassChroma = root();
    }
    return theBassChroma;
}

const size_t ChordAbstract::cardinality() const
{
    return m_Type.cardinality();
}

const bool ChordAbstract::hasSpelling() const
{
    return m_Root.hasSpelling() && m_Type.hasSpelling();
}

ChordAbstract& ChordAbstract::ignoreSpelling()
{
    if (isTrueChord())
    {
        m_Root.ignoreSpelling();
        m_Type.ignoreSpelling();
    }
    return *this;
}

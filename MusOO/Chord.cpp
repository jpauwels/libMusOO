//============================================================================
/**
	Implementation file for Chord.h
	
	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================

// Includes
#include "MusOO/Chord.h"
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
	return m_Type != ChordType::none() && m_Type != ChordType::undefined();
}

const bool Chord::isDiatonic(const Key& inKey) const
{
	if (!isTrueChord())
	{
		return false;
	}
    if (inKey.mode() == Mode::minorGeneral())
    {
        return isDiatonic(Key(inKey.tonic(), Mode::minorNatural())) || isDiatonic(Key(inKey.tonic(), Mode::minorHarmonic())) || isDiatonic(Key(inKey.tonic(), Mode::minorMelodic()));
    }
	set<Chroma> theChordChromas = chromas();
    set<Chroma> theKeyChromas = inKey.chromas();
    vector<Chroma> theNonDiatonicChromas(cardinality());
    if (std::set_difference(theChordChromas.begin(), theChordChromas.end(), theKeyChromas.begin(), theKeyChromas.end(), theNonDiatonicChromas.begin()) - theNonDiatonicChromas.begin() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Chord::addChroma(const Chroma& inChroma)
{
	type().addInterval(SimpleInterval(root(), inChroma));
}

void Chord::deleteChroma(const Chroma& inChroma)
{
	type().deleteInterval(SimpleInterval(root(), inChroma));
}

void Chord::replaceChroma(const Chroma& inChromaToReplace, const Chroma& inReplacementChroma)
{
	type().replaceInterval(SimpleInterval(root(), inChromaToReplace), SimpleInterval(root(), inReplacementChroma));
}

void Chord::addBass(const Chroma& inChroma)
{
	type().addBass(SimpleInterval(root(), inChroma));
}

void Chord::deleteBass(const Chroma& inChroma)
{
	type().deleteBass();
}

const std::set<Chroma> Chord::chromas() const
{
	set<Chroma> theChromaSet;
	for (set<Interval>::const_iterator it = m_Type.m_set.begin(); it != m_Type.m_set.end(); ++it)
	{
		theChromaSet.insert(Chroma(m_Root, it->simpleInterval()));
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

const size_t Chord::cardinality() const
{
    return m_Type.cardinality();
}

const Chord Chord::triad(bool inWithBass) const
{
    return Chord(m_Root, m_Type.triad(inWithBass));
}

const Chord Chord::tetrad(bool inWithBass) const
{
    return Chord(m_Root, m_Type.tetrad(inWithBass));
}

const bool Chord::hasSpelling() const
{
    return m_Root.hasSpelling() && m_Type.hasSpelling();
}

Chord Chord::withoutSpelling() const
{
    return Chord(*this).ignoreSpelling();
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

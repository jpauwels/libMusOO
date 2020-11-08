#ifndef ChordAbstract_h
#define ChordAbstract_h

//============================================================================
/**
	Base class representing an abstract chord.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include "MusOO/ChromaAbstract.h"
#include "MusOO/ChordTypeAbstract.h"
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

namespace MusOO
{
template <typename Key, typename Chroma, typename Mode> class KeyAbstract;

template <typename Chord, typename Chroma, typename ChordType>
class ChordAbstract
{
public:

    template <typename OtherChord, typename OtherChroma, typename OtherChordType> friend class ChordAbstract; // to access m_Root and m_Type from other Chord types
    
    using ChromaT = Chroma;
    using ChordTypeT = ChordType;
    
	static const Chord& none();
	static const Chord& silence();
	static const Chord& undefined();

	/** Default constructor. */
	ChordAbstract();
    /** Generalised copy constructor. */
    template <typename OtherChord, typename OtherChroma, typename OtherChordType>
    ChordAbstract(const ChordAbstract<OtherChord, OtherChroma, OtherChordType>& inChord);
	ChordAbstract(const Chroma& inRoot, const ChordType& inChordType);
    
    /** Destructor. */
    virtual ~ChordAbstract();

    static const Chord chordFromChromas(const Chroma& inRoot, const std::set<Chroma>& inChromas, const Chroma& inBass = Chroma::undefined());
    static const std::set<Chord> allChordsFromChromas(const std::set<Chroma>& inChromas, const Chroma& inBass = Chroma::undefined());
    
	// assignment operator
	//ChordAbstract& operator=(const ChordAbstract& inChordAbstract) = default;

	/** Operators */
	bool operator==(const ChordAbstract& inChordAbstract) const;
	bool operator!=(const ChordAbstract& inChordAbstract) const;
    bool operator<(const ChordAbstract& inChordAbstract) const;

	Chroma& root();
	const Chroma& root() const;
	ChordType& type();
	const ChordType& type() const;

	const std::set<Chroma> chromas() const;
    const std::set<Chroma> commonChromas(const Chord& inOtherChord) const;
    const Chroma bass(bool inDefaultToRoot) const;
	const size_t cardinality() const;
    
    /** Returns the basic triad the current chord can be mapped to
     @return		a ChordAbstract object with ChordType of size 3 or ChordType::rootOnly() */
    const Chord triad(bool inWithBass) const;
    const Chord tetrad(bool inWithBass) const;

	const bool isTrueChord() const;

    template <typename Key, typename OtherChroma, typename Mode>
	const bool isDiatonic(const KeyAbstract<Key, OtherChroma, Mode>& inKey) const;
	
	void addChroma(const Chroma& inChroma);
	void deleteChroma(const Chroma& inChroma);
	void replaceChroma(const Chroma& inChromaToReplace, const Chroma& inReplacementChroma);
	void addBass(const Chroma& inChroma);
	void deleteBass(const Chroma& inChroma);
    
    const bool hasSpelling() const;
    Chord withoutSpelling() const;
    Chord& ignoreSpelling();
    
    virtual const std::string str() const = 0;
    
protected:
	
	Chroma m_Root;
	ChordType m_Type;

private:
};


template <typename Chord, typename Chroma, typename ChordType>
std::ostream& operator<<(std::ostream& inOutputStream, const ChordAbstract<Chord, Chroma, ChordType>& inChord)
{
    inOutputStream << inChord.str();
    return inOutputStream;
}

template <typename Chord, typename Chroma, typename ChordType>
std::istream& operator>>(std::istream& inInputStream, ChordAbstract<Chord, Chroma, ChordType>& inChord)
{
    std::string theChordString;
    inInputStream >> theChordString;
    inChord = Chord(theChordString);
    return inInputStream;
}


template <typename Chord, typename Chroma, typename ChordType>
const Chord& ChordAbstract<Chord, Chroma, ChordType>::none()
{
    static const Chord none(Chroma::none(), ChordType::none());
    return none;
}
template <typename Chord, typename Chroma, typename ChordType>
const Chord& ChordAbstract<Chord, Chroma, ChordType>::silence()
{
    static const Chord silence(Chroma::silence(), ChordType::none());
    return silence;
}
template <typename Chord, typename Chroma, typename ChordType>
const Chord& ChordAbstract<Chord, Chroma, ChordType>::undefined()
{
    static const Chord undefined(Chroma::undefined(), ChordType::none());
    return undefined;
}

template <typename Chord, typename Chroma, typename ChordType>
ChordAbstract<Chord, Chroma, ChordType>::ChordAbstract()
{
}

template <typename Chord, typename Chroma, typename ChordType>
ChordAbstract<Chord, Chroma, ChordType>::ChordAbstract(const Chroma& inRoot, const ChordType& inChordType)
: m_Root(inRoot), m_Type(inChordType)
{
}

template <typename Chord, typename Chroma, typename ChordType>
template <typename OtherChord, typename OtherChroma, typename OtherChordType>
ChordAbstract<Chord, Chroma, ChordType>::ChordAbstract(const ChordAbstract<OtherChord, OtherChroma, OtherChordType>& inChord)
: m_Root(inChord.m_Root), m_Type(inChord.m_Type)
{
}

template <typename Chord, typename Chroma, typename ChordType>
ChordAbstract<Chord, Chroma, ChordType>::~ChordAbstract()
{
}

template <typename Chord, typename Chroma, typename ChordType>
const Chord ChordAbstract<Chord, Chroma, ChordType>::chordFromChromas(const Chroma& inRoot, const std::set<Chroma>& inChromas, const Chroma& inBass /*= Chroma::undefined()*/)
{
    ChordType chordType;
    for (typename std::set<Chroma>::const_iterator iChroma = inChromas.begin(); iChroma != inChromas.end(); ++iChroma)
    {
        chordType.add(SimpleInterval(inRoot, *iChroma));
    }
    chordType.addBass(SimpleInterval(inRoot, inBass));
    return Chord(inRoot, chordType);
}

template <typename Chord, typename Chroma, typename ChordType>
const std::set<Chord> ChordAbstract<Chord, Chroma, ChordType>::allChordsFromChromas(const std::set<Chroma>& inChromas, const Chroma& inBass /*= Chroma::undefined()*/)
{
    std::set<Chord> allChords;
    for (typename std::set<Chroma>::const_iterator iChroma = inChromas.begin(); iChroma != inChromas.end(); ++iChroma)
    {
        allChords.insert(chordFromChromas(*iChroma, inChromas, inBass));
    }
    return allChords;
}

template <typename Chord, typename Chroma, typename ChordType>
const Chord ChordAbstract<Chord, Chroma, ChordType>::triad(bool inWithBass) const
{
    return Chord(m_Root, m_Type.triad(inWithBass));
}

template <typename Chord, typename Chroma, typename ChordType>
const Chord ChordAbstract<Chord, Chroma, ChordType>::tetrad(bool inWithBass) const
{
    return Chord(m_Root, m_Type.tetrad(inWithBass));
}

template <typename Chord, typename Chroma, typename ChordType>
template <typename Key, typename OtherChroma, typename Mode>
const bool ChordAbstract<Chord, Chroma, ChordType>::isDiatonic(const KeyAbstract<Key, OtherChroma, Mode>& inKey) const
{
    if (!isTrueChord())
    {
        return false;
    }
    if (inKey.mode() == Mode::minorGeneral())
    {
        return isDiatonic(Key(inKey.tonic(), Mode::minorNatural())) ||
        isDiatonic(Key(inKey.tonic(), Mode::minorHarmonic())) ||
        isDiatonic(Key(inKey.tonic(), Mode::minorMelodic()));
    }
    std::set<Chroma> theChordAbstractChromas = chromas();
    std::set<Chroma> theKeyChromas = inKey.chromas();
    std::vector<Chroma> theNonDiatonicChromas(cardinality());
    if (std::set_difference(theChordAbstractChromas.begin(), theChordAbstractChromas.end(), theKeyChromas.begin(), theKeyChromas.end(), theNonDiatonicChromas.begin()) - theNonDiatonicChromas.begin() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename Chord, typename Chroma, typename ChordType>
Chroma& ChordAbstract<Chord, Chroma, ChordType>::root()
{
    return m_Root;
}

template <typename Chord, typename Chroma, typename ChordType>
const Chroma& ChordAbstract<Chord, Chroma, ChordType>::root() const
{
    return m_Root;
}

template <typename Chord, typename Chroma, typename ChordType>
ChordType& ChordAbstract<Chord, Chroma, ChordType>::type()
{
    return m_Type;
}

template <typename Chord, typename Chroma, typename ChordType>
const ChordType& ChordAbstract<Chord, Chroma, ChordType>::type() const
{
    return m_Type;
}

template <typename Chord, typename Chroma, typename ChordType>
bool ChordAbstract<Chord, Chroma, ChordType>::operator==(const ChordAbstract& inChordAbstract) const
{
    return m_Root == inChordAbstract.m_Root && m_Type == inChordAbstract.m_Type;
}

template <typename Chord, typename Chroma, typename ChordType>
bool ChordAbstract<Chord, Chroma, ChordType>::operator!=(const ChordAbstract& inChordAbstract) const
{
    return m_Root != inChordAbstract.m_Root || m_Type != inChordAbstract.m_Type;
}

template <typename Chord, typename Chroma, typename ChordType>
bool ChordAbstract<Chord, Chroma, ChordType>::operator<(const ChordAbstract& inChordAbstract) const
{
    return m_Root < inChordAbstract.m_Root || m_Type < inChordAbstract.m_Type;
}

template <typename Chord, typename Chroma, typename ChordType>
const bool ChordAbstract<Chord, Chroma, ChordType>::isTrueChord() const
{
    return m_Type != ChordType::none() && m_Type != ChordType::undefined();
}

template <typename Chord, typename Chroma, typename ChordType>
void ChordAbstract<Chord, Chroma, ChordType>::addChroma(const Chroma& inChroma)
{
    type().addInterval(SimpleInterval(root(), inChroma));
}

template <typename Chord, typename Chroma, typename ChordType>
void ChordAbstract<Chord, Chroma, ChordType>::deleteChroma(const Chroma& inChroma)
{
    type().deleteInterval(SimpleInterval(root(), inChroma));
}

template <typename Chord, typename Chroma, typename ChordType>
void ChordAbstract<Chord, Chroma, ChordType>::replaceChroma(const Chroma& inChromaToReplace, const Chroma& inReplacementChroma)
{
    type().replaceInterval(SimpleInterval(root(), inChromaToReplace), SimpleInterval(root(), inReplacementChroma));
}

template <typename Chord, typename Chroma, typename ChordType>
void ChordAbstract<Chord, Chroma, ChordType>::addBass(const Chroma& inChroma)
{
    type().addBass(SimpleInterval(root(), inChroma));
}

template <typename Chord, typename Chroma, typename ChordType>
void ChordAbstract<Chord, Chroma, ChordType>::deleteBass(const Chroma& inChroma)
{
    type().deleteBass();
}

template <typename Chord, typename Chroma, typename ChordType>
const std::set<Chroma> ChordAbstract<Chord, Chroma, ChordType>::chromas() const
{
    std::set<Chroma> theChromaSet;
    for (std::set<SimpleInterval>::const_iterator it = m_Type.begin(); it != m_Type.end(); ++it)
    {
        theChromaSet.insert(Chroma(m_Root, *it));
    }
    return theChromaSet;
}

template <typename Chord, typename Chroma, typename ChordType>
const std::set<Chroma> ChordAbstract<Chord, Chroma, ChordType>::commonChromas(const Chord& inOtherChord) const
{
    std::set<Chroma> theChromaSet = chromas();
    std::set<Chroma> theOtherChromaSet = inOtherChord.chromas();
    std::set<Chroma> theCommonChromas;
    std::set_intersection(theChromaSet.begin(), theChromaSet.end(), theOtherChromaSet.begin(), theOtherChromaSet.end(), std::inserter(theCommonChromas, theCommonChromas.end()));
    return theCommonChromas;
}

template <typename Chord, typename Chroma, typename ChordType>
const Chroma ChordAbstract<Chord, Chroma, ChordType>::bass(bool inDefaultToRoot) const
{
    Chroma theBassChroma(m_Root, m_Type.m_Bass);
    if (inDefaultToRoot && theBassChroma == Chroma::undefined())
    {
        theBassChroma = root();
    }
    return theBassChroma;
}

template <typename Chord, typename Chroma, typename ChordType>
const size_t ChordAbstract<Chord, Chroma, ChordType>::cardinality() const
{
    return m_Type.cardinality();
}

template <typename Chord, typename Chroma, typename ChordType>
const bool ChordAbstract<Chord, Chroma, ChordType>::hasSpelling() const
{
    return m_Root.hasSpelling() && m_Type.hasSpelling();
}

template <typename Chord, typename Chroma, typename ChordType>
Chord& ChordAbstract<Chord, Chroma, ChordType>::ignoreSpelling()
{
    if (isTrueChord())
    {
        m_Root.ignoreSpelling();
        m_Type.ignoreSpelling();
    }
    return static_cast<Chord&>(*this);
}

template <typename Chord, typename Chroma, typename ChordType>
Chord ChordAbstract<Chord, Chroma, ChordType>::withoutSpelling() const
{
    return Chord(static_cast<const Chord&>(*this)).ignoreSpelling();
}

}
#endif	// #ifndef ChordAbstract_h

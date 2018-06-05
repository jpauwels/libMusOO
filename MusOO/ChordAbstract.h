#ifndef ChordAbstract_h
#define ChordAbstract_h

//============================================================================
/**
	Base class representing an abstract chord.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include <string>
#include "MusOO/Chroma.h"
#include "MusOO/ChordType.h"

namespace MusOO
{
class Key;

class ChordAbstract
{
public:

    template <typename Chord>
	static const Chord& none();
    template <typename Chord>
	static const Chord& silence();
    template <typename Chord>
	static const Chord& undefined();

	//default constructor
	ChordAbstract();
	ChordAbstract(const Chroma& inRoot, const ChordType& inChordType);
    
    template <typename Chord>
    static const Chord chordFromChromas(const Chroma& inRoot, const std::set<Chroma>& inChromas, const Chroma& inBass = Chroma::undefined());
    template <typename Chord>
    static const std::set<Chord> allChordsFromChromas(const std::set<Chroma>& inChromas, const Chroma& inBass = Chroma::undefined());
    
	//copy constructor
	//ChordAbstract(const ChordAbstract& inChordAbstract) = default;

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
    const std::set<Chroma> commonChromas(const ChordAbstract& inOtherChordAbstract) const;
    const Chroma bass(bool inDefaultToRoot) const;
	const size_t cardinality() const;
    
    /** Returns the basic triad the current chord can be mapped to
     @return		a ChordAbstract object with ChordType of size 3 or ChordType::rootOnly() */
    template <typename Chord>
    const Chord triad(bool inWithBass) const;
    template <typename Chord>
    const Chord tetrad(bool inWithBass) const;

	const bool isTrueChord() const;

	/** Destructor. */
	virtual ~ChordAbstract();

	const bool isDiatonic(const Key& inKey) const;
	
	void addChroma(const Chroma& inChroma);
	void deleteChroma(const Chroma& inChroma);
	void replaceChroma(const Chroma& inChromaToReplace, const Chroma& inReplacementChroma);
	void addBass(const Chroma& inChroma);
	void deleteBass(const Chroma& inChroma);
    
    const bool hasSpelling() const;
    template <typename Chord>
    Chord withoutSpelling() const;
    ChordAbstract& ignoreSpelling();
    
protected:
	
    virtual const std::unique_ptr<ChordAbstract> create(const Chroma& inRoot, const ChordType& inChordType) = 0;

	Chroma m_Root;
	ChordType m_Type;

private:
};
    

template <typename Chord>
const Chord& ChordAbstract::none()
{
    static const Chord none(Chroma::none(), ChordType::none());
    return none;
}
template <typename Chord>
const Chord& ChordAbstract::silence()
{
    static const Chord silence(Chroma::silence(), ChordType::none());
    return silence;
}
template <typename Chord>
const Chord& ChordAbstract::undefined()
{
    static const Chord undefined(Chroma::undefined(), ChordType::none());
    return undefined;
}

template <typename Chord>
const Chord ChordAbstract::chordFromChromas(const Chroma& inRoot, const std::set<Chroma>& inChromas, const Chroma& inBass /*= Chroma::undefined()*/)
{
    ChordType chordType;
    for (std::set<Chroma>::const_iterator iChroma = inChromas.begin(); iChroma != inChromas.end(); ++iChroma)
    {
        chordType.add(SimpleInterval(inRoot, *iChroma));
    }
    chordType.addBass(SimpleInterval(inRoot, inBass));
    return Chord(inRoot, chordType);
}

template <typename Chord>
const std::set<Chord> ChordAbstract::allChordsFromChromas(const std::set<Chroma>& inChromas, const Chroma& inBass /*= Chroma::undefined()*/)
{
    std::set<Chord> allChords;
    for (std::set<Chroma>::const_iterator iChroma = inChromas.begin(); iChroma != inChromas.end(); ++iChroma)
    {
        allChords.insert(chordFromChromas<Chord>(*iChroma, inChromas, inBass));
    }
    return allChords;
}

template <typename Chord>
const Chord ChordAbstract::triad(bool inWithBass) const
{
    return Chord(m_Root, m_Type.triad(inWithBass));
}

template <typename Chord>
const Chord ChordAbstract::tetrad(bool inWithBass) const
{
    return Chord(m_Root, m_Type.tetrad(inWithBass));
}

template <typename Chord>
Chord ChordAbstract::withoutSpelling() const
{
    return Chord(*this).ignoreSpelling();
}

}


#endif	// #ifndef ChordAbstract_h

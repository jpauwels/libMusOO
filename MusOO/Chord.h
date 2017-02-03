#ifndef Chord_h
#define Chord_h

//============================================================================
/**
	Base class representing a chord.

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

class Chord
{
public:

	static const Chord& none();
	static const Chord& silence();
	static const Chord& undefined();

	//default constructor
	Chord();
	Chord(const Chroma& inRoot, const ChordType& inChordType);

	//copy constructor
	//Chord(const Chord& inChord) = default;

	// assignment operator
	//Chord& operator=(const Chord& inChord) = default;

	/** Operators */
	bool operator==(const Chord& inChord) const;
	bool operator!=(const Chord& inChord) const;

	Chroma& root();
	const Chroma& root() const;
	ChordType& type();
	const ChordType& type() const;

	const std::set<Chroma> chromas() const;
    const std::set<Chroma> commonChromas(const Chord& inOtherChord) const;
    const Chroma bass(bool inDefaultToRoot) const;
	const size_t cardinality() const;
    
    /** Returns the basic triad the current chord can be mapped to
     @return		a Chord object with ChordType of size 3 or ChordType::rootOnly() */
    const Chord triad(bool inWithBass) const;
    const Chord tetrad(bool inWithBass) const;

	const bool isTrueChord() const;

	/** Destructor. */
	virtual ~Chord();

	const bool isDiatonic(const Key& inKey) const;
	
	void addChroma(const Chroma& inChroma);
	void deleteChroma(const Chroma& inChroma);
	void replaceChroma(const Chroma& inChromaToReplace, const Chroma& inReplacementChroma);
	void addBass(const Chroma& inChroma);
	void deleteBass(const Chroma& inChroma);
    
    const bool hasSpelling() const;
    Chord withoutSpelling() const;
    Chord& ignoreSpelling();
    
protected:
	
	Chroma m_Root;
	ChordType m_Type;

private:
};
}


#endif	// #ifndef Chord_h

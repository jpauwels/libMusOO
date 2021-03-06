#ifndef Key_h
#define Key_h

//============================================================================
/**
	Class representing a key.

	@author		Johan Pauwels
	@date		20100322
	@todo		implement stream operators for key class
*/
//============================================================================
#include <string>
#include "MusOO/Chroma.h"
#include "MusOO/Mode.h"

namespace MusOO
{
class RelativeChord;
class Chord;

class Key
{
public:

	static const Key& silence();
    static const Key& none();
    static const Key& undefined();

	/** Default constructor. */
	Key();
	Key(const Chroma& inTonic, const Mode& inMode);

	bool operator==(const Key& inKey) const;
	bool operator!=(const Key& inKey) const;

	Chroma& tonic();
	const Chroma& tonic() const;
	Mode& mode();
	const Mode& mode() const;
	
	/** Destructor. */
	virtual ~Key();

	const std::set<Chroma> chromas() const;
	const size_t cardinality() const;

	const size_t chromaticCOFDistance(const Key& inKey) const;
	
	/** Returns the chord that arises from interpreting a given relative chord in this key */
	Chord chord(const RelativeChord& inRelChord) const;
	/* Returns the relative chord that arises from interpreting a given chord in this key */
	RelativeChord relativeChord(const Chord& inChord) const;
    
    const bool isTrueKey() const;
    
    const bool hasSpelling() const;
    Key withoutSpelling() const;
    Key& ignoreSpelling();
    
    void addChroma(const Chroma& inChroma);
	void deleteChroma(const Chroma& inChroma);
    
protected:

	Chroma m_Tonic;
	Mode m_Mode;

private:


};
}
#endif	// #ifndef Key_h

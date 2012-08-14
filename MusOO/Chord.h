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
#include "Chroma.h"
#include "ChordType.h"

class Key;

class Chord
{
public:

	static const Chord& noChord();
	static const Chord& silence();
	static const Chord& unknown();

	//default constructor
	Chord();
	Chord(const Chroma& inRoot, const ChordType& inChordType);

	//copy constructor
	Chord(const Chord& inChord);

	// assignment operator
	Chord& operator=(const Chord& inChord);

	/** Operators */
	bool operator==(const Chord& inChord) const;
	bool operator!=(const Chord& inChord) const;

	Chroma& root();
	const Chroma& root() const;
	ChordType& type();
	const ChordType& type() const;
//	virtual const std::string str() const;

	const std::vector<Chroma> chromaList() const;

	const bool isRealChord() const;

	/** Destructor. */
	virtual ~Chord();

	const bool isDiatonic(const Key& inKey) const;

protected:
	
	Chroma m_Root;
	ChordType m_Type;

private:


};


#endif	// #ifndef Chord_h

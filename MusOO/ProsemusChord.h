#ifndef ProsemusChord_h
#define ProsemusChord_h

//============================================================================
/**
	Class representing a chord with Prosemus syntax.

	@author		Johan Pauwels
	@date		20101220
*/
//============================================================================
#include <string>
#include "Chord.h"

class ProsemusChordType : public ChordType
{
public:

	/** Default constructor. */
	ProsemusChordType();
	ProsemusChordType(std::string inName);
	/** Copy constructor */
	ProsemusChordType(const ChordType& inChordType);

	/** Destructor. */
	virtual ~ProsemusChordType();

	const std::string str() const;

private:

	static const std::map<std::string,ChordType> s_TypeStringMap;

};


class ProsemusChord : public Chord
{
public:

	/** Default constructor. */
	ProsemusChord();
	ProsemusChord(const std::string& inChordString);
	// copy constructor
	ProsemusChord(const Chord& inChord);

	/** Destructor. */
	virtual ~ProsemusChord();

	const std::string str() const;

protected:


private:


};

#endif	// #ifndef ProsemusChord_h

#ifndef ChordQuaero_h
#define ChordQuaero_h

//============================================================================
/**
 Class representing a chord with Quaero syntax.
 
 @author	Johan Pauwels
 @date		20120719
 */
//============================================================================
#include <string>
#include "MusOO/Chord.h"
#include "MusOO/ChromaSolfege.h"

namespace MusOO
{
class ChordTypeQuaero : public ChordType
{
public:
    
    friend class ModeQuaero; // to access getConstrainedString() in ModeQuaero::str
	
	/** Default constructor. */
	ChordTypeQuaero();
	ChordTypeQuaero(std::string inName);
	/** Copy constructor */
	ChordTypeQuaero(const ChordType& inChordType);
	
	/** Destructor. */
	virtual ~ChordTypeQuaero();
	
	const std::string str(const Chroma& inRootChroma = Chroma::undefined()) const;
	
private:
	
	static const std::map<std::string,ChordType> s_TypeStringMap;
	static const std::string getConstrainedString(const ChromaSolfege& inChromaSolfege);
	
};


class ChordQuaero : public Chord
{
public:
    
    friend class KeyQuaero; // to access trimRight() in KeyQuaero::KeyQuaero
	
	/** Default constructor. */
	ChordQuaero();
	ChordQuaero(const std::string& inChordString);
	// copy constructor
	ChordQuaero(const Chord& inChord);
	
	/** Destructor. */
	virtual ~ChordQuaero();
	
	const std::string str() const;
	
protected:
	
	
private:
	static const std::string trimRight(const std::string& inString);
	
};

std::ostream& operator<<(std::ostream& inOutputStream, const ChordQuaero& inChord);
std::istream& operator>>(std::istream& inInputStream, ChordQuaero& inChord);
std::ostream& operator<<(std::ostream& inOutputStream, const ChordTypeQuaero& inChordType);
std::istream& operator>>(std::istream& inInputStream, ChordTypeQuaero& inChordType);
}
#endif	// #ifndef ChordQuaero_h

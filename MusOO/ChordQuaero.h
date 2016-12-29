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

namespace MusOO
{
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
}
#endif	// #ifndef ChordQuaero_h

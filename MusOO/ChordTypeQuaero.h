#ifndef ChordTypeQuaero_h
#define ChordTypeQuaero_h

//============================================================================
/**
 Class representing a chord type with Quaero syntax.
 
 @author	Johan Pauwels
 @date		20120719
 */
//============================================================================
#include <string>
#include "MusOO/ChordType.h"
#include "MusOO/Chroma.h"

namespace MusOO
{
class ChromaSolfege;
    
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

std::ostream& operator<<(std::ostream& inOutputStream, const ChordTypeQuaero& inChordType);
std::istream& operator>>(std::istream& inInputStream, ChordTypeQuaero& inChordType);
}
#endif	// #ifndef ChordTypeQuaero_h

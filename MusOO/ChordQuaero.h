#ifndef ChordQuaero_h
#define ChordQuaero_h

//============================================================================
/**
 Class representing a chord with Quaero syntax.
 
 @author	Johan Pauwels
 @date		20120719
 */
//============================================================================
#include "MusOO/ChordAbstract.h"
#include "MusOO/ChromaSolfege.h"
#include "MusOO/ChordTypeQuaero.h"

namespace MusOO
{
class ChordQuaero : public ChordAbstract<ChordQuaero, ChromaSolfege, ChordTypeQuaero>
{
public:
    
    friend class KeyQuaero; // to access trimRight() in KeyQuaero::KeyQuaero
	
    using ChordAbstract<ChordQuaero, ChromaSolfege, ChordTypeQuaero>::ChordAbstract;
    ChordQuaero(const std::string& inChordString);
	
	const std::string str() const;

private:
    
	static const std::string trimRight(const std::string& inString);
	
};

}
#endif	// #ifndef ChordQuaero_h

#ifndef KeyQuaero_h
#define KeyQuaero_h

//============================================================================
/**
 Class representing a key according to the Quaero syntax.
 
 @author	Johan Pauwels
 @date		20130417
 */
//============================================================================
#include "MusOO/Key.h"

namespace MusOO
{
class KeyQuaero : public Key
{
public:
    
	/** Default constructor. */
	KeyQuaero();
	KeyQuaero(const std::string& inKeyString);
	// copy constructor
	KeyQuaero(const Key& inKey);
    KeyQuaero(const Chroma& inTonic, const Mode& inMode);
    
	/** Destructor. */
	virtual ~KeyQuaero();
    
	const std::string str() const;
    
protected:
    
    
private:
    
    
};

std::ostream& operator<<(std::ostream& inOutputStream, const KeyQuaero& inKey);
}
#endif	// #ifndef KeyQuaero_h

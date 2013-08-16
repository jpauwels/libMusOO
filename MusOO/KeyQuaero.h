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
class ModeQuaero : public Mode
{
public:
	ModeQuaero();
	ModeQuaero(const Mode& inMode);
	ModeQuaero(const std::string& inString);
    
	const std::string str(const Chroma& inTonicChroma = Chroma::undefined()) const;
    
private:
    static const std::map<std::string,Mode> s_ModeStringMap;
};

class KeyQuaero : public Key
{
public:
    
	/** Default constructor. */
	KeyQuaero();
	KeyQuaero(const std::string& inKeyString);
	// copy constructor
	KeyQuaero(const Key& inKey);
    
	/** Destructor. */
	virtual ~KeyQuaero();
    
	const std::string str() const;
    
protected:
    
    
private:
    
    
};

std::ostream& operator<<(std::ostream& inOutputStream, const ModeQuaero& inMode);
std::ostream& operator<<(std::ostream& inOutputStream, const KeyQuaero& inKey);
}
#endif	// #ifndef KeyQuaero_h

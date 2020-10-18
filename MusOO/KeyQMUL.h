#ifndef KeyQMUL_h
#define KeyQMUL_h

//============================================================================
/**
	Class representing a key with syntax inspired by the chord syntax of
    Queen Mary University of London.

	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================
#include "MusOO/Key.h"

namespace MusOO
{
class KeyQMUL : public Key
{
public:

	/** Default constructor. */
	KeyQMUL();
	KeyQMUL(std::string inKeyString);
	// copy constructor
	KeyQMUL(const Key& inKey);
    KeyQMUL(const Chroma& inTonic, const Mode& inMode);

	/** Destructor. */
	virtual ~KeyQMUL();

	const std::string str() const;

protected:


private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const KeyQMUL& inKey);
}
#endif	// #ifndef KeyQMUL_h

#ifndef KeyElis_h
#define KeyElis_h

//============================================================================
/**
	Class representing a key according to the Elis syntax.

	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================
#include "MusOO/Key.h"

namespace MusOO
{
class KeyElis : public Key
{
public:

	/** Default constructor. */
	KeyElis();
	KeyElis(const std::string& inKeyString);
	// copy constructor
	KeyElis(const Key& inKey);
    KeyElis(const Chroma& inTonic, const Mode& inMode);

	/** Destructor. */
	virtual ~KeyElis();

	const std::string str() const;

protected:

private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const KeyElis& inKey);
}
#endif	// #ifndef KeyElis_h

#ifndef KeyElis_h
#define KeyElis_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================
#include <string>
#include "Key.h"

class ModeElis : public Mode
{
public:

	ModeElis();
	ModeElis(const Mode& inMode);
	ModeElis(const std::string& inString);

	const std::string str() const;

};

class KeyElis : public Key
{
public:

	/** Default constructor. */
	KeyElis();
	KeyElis(const std::string& inKeyString);
	// copy constructor
	KeyElis(const Key& inKey);

	/** Destructor. */
	virtual ~KeyElis();

	const std::string str() const;

protected:

private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const ModeElis& inMode);
std::ostream& operator<<(std::ostream& inOutputStream, const KeyElis& inKey);

#endif	// #ifndef KeyElis_h

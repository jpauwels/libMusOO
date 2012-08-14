#ifndef ElisKey_h
#define ElisKey_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================
#include <string>
#include "Key.h"

class ElisMode : public Mode
{
public:

	ElisMode();
	ElisMode(const Mode& inMode);
	ElisMode(const std::string& inString);

	const std::string str() const;

};

class ElisKey : public Key
{
public:

	/** Default constructor. */
	ElisKey();
	ElisKey(const std::string& inKeyString);
	// copy constructor
	ElisKey(const Key& inKey);

	/** Destructor. */
	virtual ~ElisKey();

	const std::string str() const;

protected:

private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const ElisMode& inMode);
std::ostream& operator<<(std::ostream& inOutputStream, const ElisKey& inKey);

#endif	// #ifndef ElisKey_h

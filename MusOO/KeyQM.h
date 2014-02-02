#ifndef KeyQM_h
#define KeyQM_h

//============================================================================
/**
	Class representing a key according to the Queen Mary, University of London
	syntax.

	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================
#include "MusOO/Key.h"

namespace MusOO
{
class ModeQM : public Mode
{
public:
	ModeQM();
	ModeQM(const Mode& inMode);
	ModeQM(const std::string& inString);

	const std::string str() const;

};

class KeyQM : public Key
{
public:

	/** Default constructor. */
	KeyQM();
	KeyQM(std::string inKeyString);
	// copy constructor
	KeyQM(const Key& inKey);

	/** Destructor. */
	virtual ~KeyQM();

	const std::string str() const;

protected:


private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const ModeQM& inMode);
std::ostream& operator<<(std::ostream& inOutputStream, const KeyQM& inKey);
}
#endif	// #ifndef KeyQM_h

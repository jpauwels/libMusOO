#ifndef ChordTypeProsemus_h
#define ChordTypeProsemus_h

//============================================================================
/**
	Class representing a chord type with Prosemus syntax.

	@author		Johan Pauwels
	@date		20101220
*/
//============================================================================
#include <string>
#include "MusOO/ChordType.h"

namespace MusOO
{
class ChordTypeProsemus : public ChordType
{
public:

	/** Default constructor. */
	ChordTypeProsemus();
	ChordTypeProsemus(std::string inName);
	/** Copy constructor */
	ChordTypeProsemus(const ChordType& inChordType);

	/** Destructor. */
	virtual ~ChordTypeProsemus();

	const std::string str() const;

private:

	static const std::map<std::string,ChordType> s_TypeStringMap;

};
}
#endif	// #ifndef ChordTypeProsemus_h

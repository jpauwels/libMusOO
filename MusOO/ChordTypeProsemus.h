#ifndef ChordTypeProsemus_h
#define ChordTypeProsemus_h

//============================================================================
/**
	Class representing a chord type with Prosemus syntax.

	@author		Johan Pauwels
	@date		20101220
*/
//============================================================================
#include "MusOO/ChordTypeAbstract.h"

namespace MusOO
{
class ChordTypeProsemus : public ChordTypeAbstract<ChordTypeProsemus>
{
public:

    using ChordTypeAbstract<ChordTypeProsemus>::ChordTypeAbstract;
	ChordTypeProsemus(std::string inName);

	const std::string str() const;

private:

	static const std::map<const std::string,const ChordTypeProsemus> s_TypeStringMap;

};

}
#endif	// #ifndef ChordTypeProsemus_h

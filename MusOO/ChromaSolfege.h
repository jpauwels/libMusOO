#ifndef ChromaSolfege_h
#define ChromaSolfege_h

//============================================================================
/**
 Class representing a chroma with solfege syntax.
 
 @author	Johan Pauwels
 @date		20120720
 */
//============================================================================
#include <string>
#include <map>
#include "MusOO/Chroma.h"

namespace MusOO
{
class ChromaSolfege : public Chroma
{
public:
	
	/** Default constructor. */
	ChromaSolfege();
	ChromaSolfege(const std::string& inName);
	ChromaSolfege(const Chroma& inReference, const Interval& inInterval);
	/** Copy constructor. */
	ChromaSolfege(const Chroma& inChroma);
	
	/** Destructor. */
	virtual ~ChromaSolfege();
	
	const std::string str() const;
	
protected:

	
private:
	static const std::string s_linePositionToString[];
	static const std::map<std::string,ptrdiff_t> s_stringToLinePositionMap;
};
}
#endif	// #ifndef ChromaSolfege_h

#ifndef ChromaSolfege_h
#define ChromaSolfege_h

//============================================================================
/**
 Class representing a chroma with solfege syntax.
 
 @author	Johan Pauwels
 @date		20120720
 */
//============================================================================
#include "MusOO/ChromaAbstract.h"
#include <map>

namespace MusOO
{
class ChromaSolfege : public ChromaAbstract<ChromaSolfege>
{
public:
	
	using ChromaAbstract<ChromaSolfege>::ChromaAbstract;
    ChromaSolfege(const std::string& inName);

	const std::string str() const;
	
protected:

	
private:
	static const std::string s_linePositionToString[];
	static const std::map<std::string,ptrdiff_t> s_stringToLinePositionMap;
};

}
#endif	// #ifndef ChromaSolfege_h

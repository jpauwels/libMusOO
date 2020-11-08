#ifndef ChordTypeQMUL_h
#define ChordTypeQMUL_h

//============================================================================
	/**
	Class representing a chord type with syntax defined by Harte et al.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include "MusOO/ChordTypeAbstract.h"
#include <map>

namespace MusOO
{
class ChordTypeQMUL : public ChordTypeAbstract<ChordTypeQMUL>
{
public:

	using ChordTypeAbstract<ChordTypeQMUL>::ChordTypeAbstract;
	ChordTypeQMUL(std::string inName);

	const std::string str() const;

protected:

	void parseFormulaModifier(std::string inFormulaModifier);

	void addNote(const std::string& inDegree);
	void addBassNote(const std::string& inDegree);
	void replaceNote(const std::string& inToBeReplaced, const std::string& inReplacement);
	void deleteNote(const std::string& inDegree);

private:

	static const std::map<std::string,ChordTypeQMUL> s_TypeStringMap;
};

}
#endif	// #ifndef ChordTypeQMUL_h

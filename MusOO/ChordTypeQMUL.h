#ifndef ChordTypeQMUL_h
#define ChordTypeQMUL_h

//============================================================================
	/**
	Class representing a chord type with syntax defined by Harte et al.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include <string>
#include <map>
#include "MusOO/ChordType.h"

namespace MusOO
{
class ChordTypeQMUL : public ChordType
{
public:

	/** Default constructor. */
	ChordTypeQMUL();
	ChordTypeQMUL(std::string inName);
	/** Copy constructor */
	ChordTypeQMUL(const ChordType& inChordType);

	/** Destructor. */
	virtual ~ChordTypeQMUL();

	const std::string str() const;

protected:

	void parseFormulaModifier(std::string inFormulaModifier);

	void addNote(const std::string& inDegree);
	void addBassNote(const std::string& inDegree);
	void replaceNote(const std::string& inToBeReplaced, const std::string& inReplacement);
	void deleteNote(const std::string& inDegree);

private:

	static const std::map<std::string,ChordType> s_TypeStringMap;
};

std::ostream& operator<<(std::ostream& inOutputStream, const ChordTypeQMUL& inChordType);
std::istream& operator>>(std::istream& inInputStream, ChordTypeQMUL& inChordType);
}
#endif	// #ifndef ChordTypeQMUL_h

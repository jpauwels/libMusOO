#ifndef ChordQM_h
#define ChordQM_h

//============================================================================
	/**
	Class representing a chord with syntax defined by Harte et al.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include <string>
#include <map>
#include "MusOO/Chord.h"

namespace MusOO
{
class ChordTypeQM : public ChordType
{
public:

	/** Default constructor. */
	ChordTypeQM();
	ChordTypeQM(std::string inName);
	/** Copy constructor */
	ChordTypeQM(const ChordType& inChordType);

	/** Destructor. */
	virtual ~ChordTypeQM();

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

class ChordQM : public Chord
{
public:

	/** Default constructor. */
	ChordQM();
	ChordQM(const std::string& inChordString);
	// copy constructor
	ChordQM(const Chord& inChord);

	/** Destructor. */
	virtual ~ChordQM();

	const std::string str() const;

protected:


private:


};

class ChordChordino : public Chord
{
public:

	/** Default constructor. */
	ChordChordino();
	ChordChordino(std::string inChordString);
	// copy constructor
	ChordChordino(const Chord& inChord);

	/** Destructor. */
	virtual ~ChordChordino();

	const std::string str() const;

protected:


private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const ChordQM& inChord);
std::istream& operator>>(std::istream& inInputStream, ChordQM& inChord);
std::ostream& operator<<(std::ostream& inOutputStream, const ChordTypeQM& inChordType);
std::istream& operator>>(std::istream& inInputStream, ChordTypeQM& inChordType);
std::ostream& operator<<(std::ostream& inOutputStream, const ChordChordino& inChord);
std::istream& operator>>(std::istream& inInputStream, ChordChordino& inChord);
}
#endif	// #ifndef ChordQM_h

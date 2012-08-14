#ifndef QMChord_h
#define QMChord_h

//============================================================================
	/**
	Class representing a chord with syntax defined by Harte et al.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include <string>
#include <map>
#include "Chord.h"

class QMChordType : public ChordType
{
public:

	/** Default constructor. */
	QMChordType();
	QMChordType(std::string inName);
	/** Copy constructor */
	QMChordType(const ChordType& inChordType);

	/** Destructor. */
	virtual ~QMChordType();

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

class QMChord : public Chord
{
public:

	/** Default constructor. */
	QMChord();
	QMChord(const std::string& inChordString);
	// copy constructor
	QMChord(const Chord& inChord);

	/** Destructor. */
	virtual ~QMChord();

	const std::string str() const;

protected:


private:


};

class ChordinoChord : public Chord
{
public:

	/** Default constructor. */
	ChordinoChord();
	ChordinoChord(std::string inChordString);
	// copy constructor
	ChordinoChord(const Chord& inChord);

	/** Destructor. */
	virtual ~ChordinoChord();

	const std::string str() const;

protected:


private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const QMChord& inChord);
std::istream& operator>>(std::istream& inInputStream, QMChord& inChord);
std::ostream& operator<<(std::ostream& inOutputStream, const QMChordType& inChordType);
std::istream& operator>>(std::istream& inInputStream, QMChordType& inChordType);

#endif	// #ifndef QMChord_h

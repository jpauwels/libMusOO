#ifndef RelativeChord_h
#define RelativeChord_h

//============================================================================
/**
	Class representing a relative chord.

	@author		Johan Pauwels
	@date		20101222
*/
//============================================================================
#include "Chord.h"
#include "Key.h"

class RelativeChord
{
public:

	const static RelativeChord& silence();
	const static RelativeChord& none();
	const static RelativeChord& unknown();

	/** Default constructor. */
	RelativeChord();
	RelativeChord(const Interval& inRootInterval, const ChordType& inType);
	RelativeChord(const Key& inKey, const Chord& inChord);
	RelativeChord(const std::string& inDegree, const ChordType& inChordType, const Mode& inMode);
//	RelativeChord(const RelativeChord& inRelativeChord);

	/** Destructor. */
	virtual ~RelativeChord();

	bool operator==(const RelativeChord& inRelativeChord) const;
	bool operator!=(const RelativeChord& inRelativeChord) const;
	bool operator<(const RelativeChord& inRelativeChord) const;
	// assignment operator
	RelativeChord& operator=(const RelativeChord& inRelativeChord);

//	const std::string str() const;
	const std::string asDegree(const Mode& inMode) const;

	const Interval& rootInterval() const;
	const ChordType& type() const;

protected:

	Interval m_RootInterval;
	ChordType m_Type;

private:


};

class QMRelativeChord : public RelativeChord
{
public:
	QMRelativeChord();
	QMRelativeChord(const std::string& inString, const Mode inMode);
	QMRelativeChord(const RelativeChord& inRelativeChord);

	//assignment operator
// 		QMRelativeChord& operator=(const RelativeChord& inRelativeChord);
};

#endif	// #ifndef RelativeChord_h

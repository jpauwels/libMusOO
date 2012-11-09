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

	static const RelativeChord& silence();
	static const RelativeChord& none();
	static const RelativeChord& unknown();

	/** Default constructor. */
	RelativeChord();
	RelativeChord(const Interval& inRootInterval, const ChordType& inType);
	RelativeChord(const Key& inKey, const Chord& inChord);
	RelativeChord(const std::string& inDegree, const ChordType& inChordType, const Mode& inMode);

	/** Destructor. */
	virtual ~RelativeChord();

	bool operator==(const RelativeChord& inRelativeChord) const;
	bool operator!=(const RelativeChord& inRelativeChord) const;
	bool operator<(const RelativeChord& inRelativeChord) const;

//	const std::string str() const;
	const std::string asDegree(const Mode& inMode) const;

	const Interval& rootInterval() const;
	const ChordType& type() const;
    
    const bool isTrueRelativeChord() const;
    
    const bool hasSpelling() const;
    RelativeChord& ignoreSpelling();
    
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

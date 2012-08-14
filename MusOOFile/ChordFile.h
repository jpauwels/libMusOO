#ifndef ChordFile_h
#define ChordFile_h

//============================================================================
/**
	Abstract base class representing a file on disc containing chords with 
	timestamps.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include "TimedChord.h"

class ChordFile
{
public:

	ChordFile();
	/** Destructor. */
	virtual ~ChordFile();

	const ChordSequence& readAll();
	const ChordSequence readRange(double inStartTime, double inEndTime);
	void writeAll(ChordSequence& inTimedChords);
	bool isEmpty() const;

	virtual void open(const std::string& inFileName) = 0;
	virtual void close() = 0;

protected:

	bool m_FileHasChanged;
	ChordSequence m_TimedChords;
};

#endif	// #ifndef ChordFile_h

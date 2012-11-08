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

	ChordFile(const bool inPitchSpelled);
	/** Destructor. */
	virtual ~ChordFile();

	const TimedChordSequence& readAll();
	const TimedChordSequence readRange(double inStartTime, double inEndTime);
	void writeAll(TimedChordSequence& inTimedChords);
	bool isEmpty() const;

	virtual void open(const std::string& inFileName) = 0;
	virtual void close() = 0;

protected:

	bool m_FileHasChanged;
	TimedChordSequence m_TimedChords;
    bool m_PitchSpelled;
};

#endif	// #ifndef ChordFile_h

#ifndef ChordFileSonicAnnotatorCSV_h
#define ChordFileSonicAnnotatorCSV_h

//============================================================================
/**
	Class representing a file on disk containing chord segments according to
	syntax used by Matthias Mauch.

	@author		Johan Pauwels
	@date		20110608
*/
//============================================================================
#include <string>
#include <fstream>
#include "ChordFile.h"

template <typename ChordLabel>
class ChordFileSonicAnnotatorCSV : public ChordFile
{
public:

	ChordFileSonicAnnotatorCSV(const bool inPitchSpelled);
	ChordFileSonicAnnotatorCSV(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~ChordFileSonicAnnotatorCSV();

	virtual void open(const std::string& inFileName);
	virtual void close();

private:

	typedef TimedLabel<ChordLabel> TimedSAChord;
	typedef std::vector<TimedChord> TimedSAChordSequence;

	std::fstream m_File;
	std::string m_FileName;
};

// Include template implementation
#include "ChordFileSonicAnnotatorCSV.cpp"

#endif	// #ifndef ChordFileSonicAnnotatorCSV_h

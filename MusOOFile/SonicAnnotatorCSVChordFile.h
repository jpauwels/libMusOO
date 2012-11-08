#ifndef SonicAnnotatorCSVChordFile_h
#define SonicAnnotatorCSVChordFile_h

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
class SonicAnnotatorCSVChordFile : public ChordFile
{
public:

	SonicAnnotatorCSVChordFile(const bool inPitchSpelled);
	SonicAnnotatorCSVChordFile(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~SonicAnnotatorCSVChordFile();

	virtual void open(const std::string& inFileName);
	virtual void close();

private:

	typedef TimedLabel<ChordLabel> TimedSAChord;
	typedef std::vector<TimedChord> TimedSAChordSequence;

	std::fstream m_File;
	std::string m_FileName;
};

// Include template implementation
#include "SonicAnnotatorCSVChordFile.cpp"

#endif	// #ifndef SonicAnnotatorCSVChordFile_h

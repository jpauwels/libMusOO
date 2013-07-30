#ifndef ChordFileProsemus_h
#define ChordFileProsemus_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20101222
*/
//============================================================================
#include <fstream>
#include <string>
#include "ChordFile.h"
#include "ChordProsemus.h"
#include "TimedLabel.h"

class ChordFileProsemus : public ChordFile
{
public:

	/** Default constructor. */
	ChordFileProsemus(const bool inPitchSpelled);
	ChordFileProsemus(std::string inFilePath, const bool inPitchSpelled);

	/** Destructor. */
	virtual ~ChordFileProsemus();

	virtual void open(const std::string& inFilePath);
	virtual void close();

protected:


private:

	typedef TimedLabel<ProsemusChord> TimedProsemusChord;
	std::fstream m_File;
	std::string m_FilePath;

};

#endif	// #ifndef ChordFileProsemus_h

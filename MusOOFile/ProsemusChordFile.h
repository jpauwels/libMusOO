#ifndef ProsemusChordFile_h
#define ProsemusChordFile_h

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
#include "ProsemusChord.h"
#include "TimedLabel.h"

class ProsemusChordFile : public ChordFile
{
public:

	/** Default constructor. */
	ProsemusChordFile();
	ProsemusChordFile(std::string inFilePath);

	/** Destructor. */
	virtual ~ProsemusChordFile();

	virtual void open(const std::string& inFilePath);
	virtual void close();

protected:


private:

	typedef TimedLabel<ProsemusChord> TimedProsemusChord;
	std::fstream m_File;
	std::string m_FilePath;

};

#endif	// #ifndef ProsemusChordFile_h

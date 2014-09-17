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
#include "MusOOFile/ChordFile.h"
#include "MusOO/TimedLabel.h"
#include "MusOO/ChordProsemus.h"

namespace MusOO
{
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

	typedef TimedLabel<ChordProsemus> TimedProsemusChord;
	std::fstream m_File;
	std::string m_FilePath;

};
}
#endif	// #ifndef ChordFileProsemus_h

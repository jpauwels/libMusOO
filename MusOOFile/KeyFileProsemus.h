#ifndef KeyFileProsemus_h
#define KeyFileProsemus_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20110111
*/
//============================================================================
#include <string>
#include <fstream>
#include "MusOOFile/KeyFile.h"

namespace MusOO
{
class KeyFileProsemus : public KeyFile
{
public:

	KeyFileProsemus(const bool inPitchSpelled);
	KeyFileProsemus(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~KeyFileProsemus();

	virtual void open(const std::string& inFileName);
	virtual void close();

protected:


private:

	std::fstream m_File;
	std::string m_FileName;
};
}
#endif	// #ifndef KeyFileProsemus_h

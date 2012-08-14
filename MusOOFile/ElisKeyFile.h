#ifndef ElisKeyFile_h
#define ElisKeyFile_h

//============================================================================
/**
	Class representing a file containing a timed sequence of keys using Elis
	syntax.

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include <string>
#include "KeyFile.h"
#include "ElisKey.h"
#include "LabFile.h"

class ElisKeyFile : public KeyFile
{
public:

	typedef TimedLabel<ElisKey> TimedElisKey;
	typedef std::vector<TimedElisKey> ElisKeySequence;

	ElisKeyFile();
	ElisKeyFile(std::string inFileName);
	/** Destructor. */
	virtual ~ElisKeyFile();

	virtual void open(const std::string& inFileName);
	virtual void close();

private:

	LabFile<ElisKey> m_File;

};
#endif	// #ifndef ElisKeyFile_h

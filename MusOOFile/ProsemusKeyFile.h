#ifndef ProsemusKeyFile_h
#define ProsemusKeyFile_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20110111
*/
//============================================================================
#include <string>
#include <fstream>
#include "KeyFile.h"

class ProsemusKeyFile : public KeyFile
{
public:

	ProsemusKeyFile(const bool inPitchSpelled);
	ProsemusKeyFile(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~ProsemusKeyFile();

	virtual void open(const std::string& inFileName);
	virtual void close();

protected:


private:

	std::fstream m_File;
	std::string m_FileName;
};

#endif	// #ifndef ProsemusKeyFile_h

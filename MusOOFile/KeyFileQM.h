#ifndef KeyFileQM_h
#define KeyFileQM_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include <string>
#include "MusOOFile/KeyFile.h"
#include "MusOO/KeyQM.h"
#include "MusOOFile/LabFile.h"

namespace MusOO
{
class KeyFileQM : public KeyFile
{
public:

	typedef TimedLabel<KeyQM> TimedKeyQM;
	typedef std::vector<TimedKeyQM> KeyQMSequence;

	KeyFileQM(const bool inPitchSpelled);
	KeyFileQM(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~KeyFileQM();

	virtual void open(const std::string& inFileName);
	virtual void close();

private:
	
//	KeyQMSequence m_TimedKeys;
	LabFile<KeyQM> m_File;
};
}
#endif	// #ifndef KeyFileQM_h

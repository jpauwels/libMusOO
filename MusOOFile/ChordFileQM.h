#ifndef ChordFileQM_h
#define ChordFileQM_h

//============================================================================
/**
	Class representing a file on disk containing chord segments according to
	syntax used at QM.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include <string>
#include "MusOOFile/ChordFile.h"
#include "MusOO/ChordQM.h"
#include "MusOOFile/LabFile.h"


namespace MusOO
{
class ChordFileQM : public ChordFile
{
public:

	ChordFileQM(const bool inPitchSpelled);
	ChordFileQM(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~ChordFileQM();

	virtual void open(const std::string& inFileName);
	virtual void close();

private:

	typedef TimedLabel<ChordQM> TimedChordQM;
	typedef std::vector<TimedChordQM> TimedChordQMSequence;

	LabFile<ChordQM> m_File;
};
}
#endif	// #ifndef ChordFileQM_h

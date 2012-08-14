#ifndef QMChordFile_h
#define QMChordFile_h

//============================================================================
/**
	Class representing a file on disk containing chord segments according to
	syntax used at QM.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include <string>
#include "ChordFile.h"
#include "QMChord.h"
#include "LabFile.h"


class QMChordFile : public ChordFile
{
public:

	QMChordFile();
	QMChordFile(std::string inFileName);
	/** Destructor. */
	virtual ~QMChordFile();

	virtual void open(const std::string& inFileName);
	virtual void close();

private:

	typedef TimedLabel<QMChord> TimedQMChord;
	typedef std::vector<TimedQMChord> QMChordSequence;

	LabFile<QMChord> m_File;
};

#endif	// #ifndef QMChordFile_h

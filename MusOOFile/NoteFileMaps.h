#ifndef NoteFileMaps_h
#define NoteFileMaps_h

//============================================================================
/**
	Class representing a note file according to the MAPS syntax.

	@author		Johan Pauwels
	@date		20101203
*/
//============================================================================
#include <string>
#include <vector>
#include "NoteFile.h"
#include "NoteMidi.h"
#include "LabFile.h"

class NoteFileMaps : public NoteFile
{
public:

	/** Default constructor. */
	NoteFileMaps();
	NoteFileMaps(std::string inFileName);

	/** Destructor. */
	virtual ~NoteFileMaps();

	virtual void open(const std::string& inFileName);
	virtual void close();

protected:


private:

	typedef TimedLabel<NoteMidi> TimedNoteMidi;
	typedef std::vector<TimedNoteMidi> NoteMidiSequence;

	LabFile<NoteMidi> m_LabFile;
	static const std::string s_HeaderInit[];


};

#endif	// #ifndef NoteFileMaps_h

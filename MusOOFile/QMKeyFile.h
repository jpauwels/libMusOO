#ifndef QMKeyFile_h
#define QMKeyFile_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include <string>
#include "KeyFile.h"
#include "QMKey.h"
#include "LabFile.h"

class QMKeyFile : public KeyFile
{
public:

	typedef TimedLabel<QMKey> TimedQMKey;
	typedef std::vector<TimedQMKey> QMKeySequence;

	QMKeyFile();
	QMKeyFile(std::string inFileName);
	/** Destructor. */
	virtual ~QMKeyFile();

	virtual void open(const std::string& inFileName);
	virtual void close();

private:
	
//	QMKeySequence m_TimedKeys;
	LabFile<QMKey> m_File;
};

#endif	// #ifndef QMKeyFile_h

#ifndef LabFile_h
#define LabFile_h

//============================================================================
/**
	Template class representing .

	@author		Johan Pauwels
	@date		20100325
	@todo		implement stream operators
*/
//============================================================================
#include <string>
#include <fstream>
#include <vector>
#include "TimedLabel.h"

template <typename Label>
class LabFile
{
public:

	/** Default constructor. */
	LabFile(const std::vector<std::string>& inHeader = std::vector<std::string>());

	LabFile(const std::string& inFileName, 
		const std::vector<std::string>& inHeader = std::vector<std::string>());

	void open(const std::string& inFileName);

	const std::vector<TimedLabel<Label> >& readAll();
	void writeAll(std::vector<TimedLabel<Label> >& inLabels);

	TimedLabel<Label>& readNext();
	void add(TimedLabel<Label>& inLabel);

	/** Destructor. */
	virtual ~LabFile();

protected:
	std::fstream m_LabFile;
	std::string m_LabFileName;
	std::vector<TimedLabel<Label> > m_TimedLabels; // replace vector with set?
	typename std::vector<TimedLabel<Label> >::iterator m_Iterator;
	bool m_FileHasChanged;
	std::vector<std::string> m_Header;

private:
	void close();

};

// Include template implementation
#include "LabFile.cpp"

#endif	// #ifndef LabFile_h
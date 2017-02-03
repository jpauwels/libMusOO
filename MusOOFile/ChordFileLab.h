#ifndef ChordFileLab_h
#define ChordFileLab_h

//============================================================================
/**
    Class representing a lab file on disk containing chord segments.

    @author	Johan Pauwels
    @date	20160531
*/
//============================================================================
#include <string>
#include "MusOOFile/ChordFile.h"
#include "MusOOFile/LabFile.h"


namespace MusOO
{
template <typename ChordLabel>
class ChordFileLab : public ChordFile
{
public:

    ChordFileLab(const bool inPitchSpelled);
    ChordFileLab(std::string inFileName, const bool inPitchSpelled);
    /** Destructor. */
    virtual ~ChordFileLab();

    virtual void open(const std::string& inFileName);
    virtual void close();

private:

    typedef TimedLabel<ChordLabel> TimedChordLabLabel;
    typedef std::vector<TimedChordLabLabel> TimedChordLabSequence;

    LabFile<ChordLabel> m_File;
};
}

template <typename T>
MusOO::ChordFileLab<T>::ChordFileLab(const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
}

template <typename T>
MusOO::ChordFileLab<T>::ChordFileLab(std::string inFileName, const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
    open(inFileName);
}

template <typename T>
MusOO::ChordFileLab<T>::~ChordFileLab()
{
    close();
}

template <typename T>
void MusOO::ChordFileLab<T>::open(const std::string& inFileName)
{
    m_FileHasChanged = false;
    m_File.open(inFileName);
    m_TimedChords = TimedChordSequence(m_File.readAll().begin(), m_File.readAll().end());
    ChordFile::open(inFileName);
}

template <typename T>
void MusOO::ChordFileLab<T>::close()
{
    if (m_FileHasChanged)
    {
        ChordFile::close();
        TimedChordLabSequence theChords(m_TimedChords.begin(), m_TimedChords.end());
        m_File.writeAll(theChords);
    }
}

#endif // #ifndef ChordFileLab_h

#ifndef ChordFileUtil_h
#define ChordFileUtil_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include <stdexcept>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "MusOOFile/ChordFileLab.h"
#include "MusOOFile/ChordFileProsemus.h"
#include "MusOOFile/ChordFileSonicAnnotatorCSV.h"
#include "MusOOFile/ChordFileMuDesc.h"
#include "MusOO/ChordQuaero.h"
#include "MusOO/ChordQMUL.h"
#include "MusOO/ChordChordino.h"


namespace MusOO { namespace ChordFileUtil
{
	ChordFile* const newChordFileFromExtension(const boost::filesystem::path& inFileName, const bool inPitchSpelled, const std::string& inFileFormat = "auto")
	{
        using boost::algorithm::ends_with;
		if (inFileFormat == "QMUL" || (inFileFormat == "auto" && (inFileName.extension() == ".lab" || inFileName.extension() == ".txt")))
		{
			return new ChordFileLab<ChordQMUL>(inFileName.string(), inPitchSpelled);
		}
		if (inFileFormat == "Chordino")
		{
			return new ChordFileLab<ChordChordino>(inFileName.string(), inPitchSpelled);
		}
		else if (inFileFormat == "Prosemus" || (inFileFormat == "auto" && inFileName.extension() == ".chords"))
		{
			return new ChordFileProsemus(inFileName.string(), inPitchSpelled);
		}
		else if (inFileFormat == "SonicAnnotator" || (inFileFormat == "auto" && inFileName.extension() == ".csv"))
		{
			return new ChordFileSonicAnnotatorCSV<ChordQMUL>(inFileName.string(), inPitchSpelled);
		}
		else if (inFileFormat == "QuaeroEval" || (inFileFormat == "auto" && ends_with(inFileName.stem().string(), ".f") && inFileName.extension() == ".xml"))
		{
			return new ChordFileMuDesc<ChordChordino>(inFileName.string(), inPitchSpelled);
		}
		else if (inFileFormat == "Quaero" || (inFileFormat == "auto" && inFileName.extension() == ".xml"))
		{
			return new ChordFileMuDesc<ChordQuaero>(inFileName.string(), inPitchSpelled);
		}
		else if (inFileFormat == "auto")
		{
			throw std::invalid_argument("Cannot automatically derive chord file format from extension of file '" + inFileName.string() + "'");
		}
		else
		{
			throw std::invalid_argument("Unknown file format selector '" + inFileFormat + "' for chord file '" + inFileName.string() + "'");
		}
	}
    
    const TimedChordSequence readChordSequenceFromFile(const boost::filesystem::path& inFilePath, const bool inPitchSpelled, const std::string& inFileFormat = "auto")
    {
        if (!exists(inFilePath))
        {
            throw std::runtime_error("The file '" + inFilePath.string() + "' does not exist");
        }
        ChordFile* const theChordFile = newChordFileFromExtension(inFilePath, inPitchSpelled, inFileFormat);
        if (theChordFile->isEmpty())
        {
            throw std::runtime_error("The file '" + inFilePath.string() + "' does not contain any chords");
        }
        const TimedChordSequence retChords = theChordFile->readAll();
        delete theChordFile;
        return retChords;
    }
} }

#endif	// #ifndef ChordFileUtil_h

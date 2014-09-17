#ifndef KeyFileUtil_h
#define KeyFileUtil_h

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
#include "MusOOFile/KeyFileElis.h"
#include "MusOOFile/KeyFileQM.h"
#include "MusOOFile/KeyFileProsemus.h"
#include "MusOOFile/KeyFileMuDesc.h"
#include "MusOO/KeyQuaero.h"

namespace MusOO { namespace KeyFileUtil
{
	KeyFile* const newKeyFileFromExtension(const boost::filesystem::path& inFileName, const bool inPitchSpelled, const std::string& inFileFormat = "auto")
	{
        using boost::algorithm::ends_with;
		if (inFileFormat == "Elis" || (inFileFormat == "auto" && (inFileName.extension() == ".txt" || (ends_with(inFileName.stem().string(), "-keys") && inFileName.extension() == ".lab"))))
		{
			return new KeyFileElis(inFileName.string(), inPitchSpelled);
		}
		else if (inFileFormat == "QMUL" || (inFileFormat == "auto" && inFileName.extension() == ".lab"))
		{
			return new KeyFileQM(inFileName.string(), inPitchSpelled);
		}
		else if (inFileFormat == "Prosemus" || (inFileFormat == "auto" && inFileName.extension() == ".key"))
		{
			return new KeyFileProsemus(inFileName.string(), inPitchSpelled);
		}
		else if (inFileFormat == "Quaero" || (inFileFormat == "auto" && inFileName.extension() == ".xml"))
		{
			return new KeyFileMuDesc<KeyQuaero>(inFileName.string(), inPitchSpelled);
		}
		else if (inFileFormat == "auto")
		{
			throw std::invalid_argument("Cannot automatically derive key file format from extension of file " + inFileName.string());
		}
		else
		{
			throw std::invalid_argument("Unknown file format selector " + inFileFormat + " for key file " + inFileName.string());
		}
	}

    const TimedKeySequence readKeySequenceFromFile(const boost::filesystem::path& inFilePath, const bool inPitchSpelled, const std::string& inFileFormat = "auto")
    {
        KeyFile* const theKeyFile = KeyFileUtil::newKeyFileFromExtension(inFilePath, inPitchSpelled, inFileFormat);
        if (theKeyFile->isEmpty())
        {
            delete theKeyFile;
            throw std::runtime_error("The file " + inFilePath.string() + " does not contain any keys");
        }
        const TimedKeySequence retKeySequence = theKeyFile->readAll();
        delete theKeyFile;
        return retKeySequence;
    }

} }

#endif	// #ifndef KeyFileUtil_h

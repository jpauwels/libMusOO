#ifndef QMKey_h
#define QMKey_h

//============================================================================
/**
	Class representing a key according to the Queen Mary, University of London
	syntax.

	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================
#include <string>
#include "Key.h"

class QMMode : public Mode
{
public:
	QMMode();
	QMMode(const Mode& inMode);
	QMMode(const std::string& inString);

	const std::string str() const;

};

class QMKey : public Key
{
public:

	/** Default constructor. */
	QMKey();
	QMKey(const std::string& inKeyString);
	// copy constructor
	QMKey(const Key& inKey);

	/** Destructor. */
	virtual ~QMKey();

	const std::string str() const;

protected:


private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const QMMode& inMode);
std::ostream& operator<<(std::ostream& inOutputStream, const QMKey& inKey);

#endif	// #ifndef QMKey_h

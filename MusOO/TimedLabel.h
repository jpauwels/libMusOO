#ifndef TimedLabel_h
#define TimedLabel_h

//============================================================================
/**
	Template class representing a timed event.

	@author		Johan Pauwels
	@date		20100322
*/
//============================================================================
#include <string>
#include <fstream>

template <typename T>
class TimedLabel
{
public:

	/** Default constructor. */
	TimedLabel();
	TimedLabel(const double inOnset, const double inOffset, const T& inLabel);
	template <typename T2>
	TimedLabel(const TimedLabel<T2>& inLabel);

	/** Destructor. */
	virtual ~TimedLabel();

	bool operator==(const TimedLabel<T>& inLabel) const;
	bool operator!=(const TimedLabel<T>& inLabel) const;
	bool operator<(const TimedLabel<T>& inLabel) const;
	template <typename T2>
	TimedLabel<T>& operator=(const TimedLabel<T2>& inLabel);

	double& onset();
	const double& onset() const;
	double& offset();
	const double& offset() const;
	T& label();
	const T& label() const;

protected:
	double m_Onset;
	double m_Offset;
	T m_Label;

private:


};

template <typename T>
std::ostream& operator<<(std::ostream& inOutputStream, const TimedLabel<T>& inLabel);

// Include template implementation
#include "TimedLabel.cpp"

#endif	// #ifndef TimedLabel_h

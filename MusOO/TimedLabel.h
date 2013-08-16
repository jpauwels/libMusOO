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

namespace MusOO
{
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
}


template <typename T>
MusOO::TimedLabel<T>::TimedLabel()
{
}

template <typename T>
MusOO::TimedLabel<T>::TimedLabel(const double inOnset, const double inOffset, const T& inLabel)
: m_Onset(inOnset), m_Offset(inOffset), m_Label(inLabel)
{
}

template <typename T>
template <typename T2>
MusOO::TimedLabel<T>::TimedLabel(const TimedLabel<T2>& inLabel)
: m_Onset(inLabel.onset()), m_Offset(inLabel.offset()), m_Label(inLabel.label())
{
}

template <typename T>
MusOO::TimedLabel<T>::~TimedLabel()
{
	// Nothing to do...
}

template <typename T>
bool MusOO::TimedLabel<T>::operator==(const TimedLabel<T>& inLabel) const
{
	return m_Onset == inLabel.m_Onset && m_Offset == inLabel.m_Offset && m_Label == inLabel.label();
    
}

template <typename T>
bool MusOO::TimedLabel<T>::operator!=(const TimedLabel<T>& inLabel) const
{
	return m_Onset != inLabel.m_Onset || m_Offset != inLabel.m_Offset || m_Label != inLabel.label();
}

template <typename T>
bool MusOO::TimedLabel<T>::operator<(const TimedLabel<T>& inLabel) const
{
	if (m_Onset < inLabel.m_Onset || (m_Onset == inLabel.m_Onset && m_Offset < inLabel.m_Offset))
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
template <typename T2>
MusOO::TimedLabel<T>& MusOO::TimedLabel<T>::operator=(const TimedLabel<T2>& inLabel)
{
	m_Onset = inLabel.onset();
	m_Offset = inLabel.offset();
	m_Label = inLabel.label();
	return *this;
}

template <typename T>
double& MusOO::TimedLabel<T>::onset()
{
	return m_Onset;
}

template <typename T>
const double& MusOO::TimedLabel<T>::onset() const
{
	return m_Onset;
}

template <typename T>
double& MusOO::TimedLabel<T>::offset()
{
	return m_Offset;
}

template <typename T>
const double& MusOO::TimedLabel<T>::offset() const
{
	return m_Offset;
}

template <typename T>
T& MusOO::TimedLabel<T>::label()
{
	return m_Label;
}

template <typename T>
const T& MusOO::TimedLabel<T>::label() const
{
	return m_Label;
}

template <typename T>
std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const MusOO::TimedLabel<T>& inLabel)
{
	inOutputStream << std::fixed << inLabel.onset()  << "\t" << inLabel.offset() << "\t" << inLabel.label();
	return inOutputStream;
}

#endif	// #ifndef TimedLabel_h

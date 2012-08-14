//============================================================================
/**
	Implementation file for TimedLabel.h

	@author		Johan Pauwels
	@date		20100322
*/
//============================================================================

// Guard against multiple template implementation inclusions
#ifndef TimedLabel_CPP
#define TimedLabel_CPP

// Includes
#include "TimedLabel.h"

template <typename T>
TimedLabel<T>::TimedLabel()
{
}

template <typename T>
TimedLabel<T>::TimedLabel(const double inOnset, const double inOffset, const T& inLabel)
: m_Onset(inOnset), m_Offset(inOffset), m_Label(inLabel)
{
}

template <typename T>
template <typename T2>
TimedLabel<T>::TimedLabel(const TimedLabel<T2>& inLabel)
: m_Onset(inLabel.onset()), m_Offset(inLabel.offset()), m_Label(inLabel.label())
{
}

template <typename T>
TimedLabel<T>::~TimedLabel()
{
	// Nothing to do...
}

template <typename T>
bool TimedLabel<T>::operator==(const TimedLabel<T>& inLabel) const
{
	return m_Onset == inLabel.m_Onset && m_Offset == inLabel.m_Offset && m_Label == inLabel.label();

}

template <typename T>
bool TimedLabel<T>::operator!=(const TimedLabel<T>& inLabel) const
{
	return m_Onset != inLabel.m_Onset || m_Offset != inLabel.m_Offset || m_Label != inLabel.label();
}

template <typename T>
bool TimedLabel<T>::operator<(const TimedLabel<T>& inLabel) const
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
TimedLabel<T>& TimedLabel<T>::operator=(const TimedLabel<T2>& inLabel)
{
	m_Onset = inLabel.onset();
	m_Offset = inLabel.offset();
	m_Label = inLabel.label();
	return *this;
}

template <typename T>
double& TimedLabel<T>::onset()
{
	return m_Onset;
}

template <typename T>
const double& TimedLabel<T>::onset() const
{
	return m_Onset;
}

template <typename T>
double& TimedLabel<T>::offset()
{
	return m_Offset;
}

template <typename T>
const double& TimedLabel<T>::offset() const
{
	return m_Offset;
}

template <typename T>
T& TimedLabel<T>::label()
{
	return m_Label;
}

template <typename T>
const T& TimedLabel<T>::label() const
{
	return m_Label;
}


template <typename T>
std::ostream& operator<<(std::ostream& inOutputStream, const TimedLabel<T>& inLabel)
{
	inOutputStream << std::fixed << inLabel.onset()  << "\t" << inLabel.offset() << "\t" << inLabel.label();
	return inOutputStream;
}

#endif  // #ifndef TimedLabel_CPP

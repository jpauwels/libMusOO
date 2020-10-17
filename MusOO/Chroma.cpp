//============================================================================
/**
	Implementation file for Chroma.h

	@author		Johan Pauwels
	@date		20100322
*/
//============================================================================

// Includes
#include <string>
	using std::string;
#include <stdexcept>
	using std::invalid_argument;
#include <limits>
	using std::numeric_limits;
#include <ostream>
#include <vector>
	using std::vector;
#include "MusOO/Chroma.h"
#include "MusOO/SimpleInterval.h"
using namespace MusOO;

const Chroma& Chroma::silence()
{
	static const Chroma silence(numeric_limits<ptrdiff_t>::max(), true);
	return silence;
}
const Chroma& Chroma::none()
{
	static const Chroma noChroma(numeric_limits<ptrdiff_t>::max()-1, true);
	return noChroma;
}
const Chroma& Chroma::undefined()
{
	static const Chroma undefined(numeric_limits<ptrdiff_t>::max()-2, true);
	return undefined;
}
Chroma Chroma::Fb()
{
	static const Chroma Fb(-6, true);
	return Fb;
}
Chroma Chroma::Cb()
{
	static const Chroma Cb(-5, true);
	return Cb;
}
Chroma Chroma::Gb()
{
	static const Chroma Gb(-4, true);
	return Gb;
}
Chroma Chroma::Db()
{
	static const Chroma Db(-3, true);
	return Db;
}
Chroma Chroma::Ab()
{
	static const Chroma Ab(-2, true);
	return Ab;
}
Chroma Chroma::Eb()
{
	static const Chroma Eb(-1, true);
	return Eb;
}
Chroma Chroma::Bb()
{
	static const Chroma Bb(0, true);
	return Bb;
}
Chroma Chroma::F()
{
	static const Chroma F(1, true);
	return F;
}
Chroma Chroma::C()
{
	static const Chroma C(2, true);
	return C;
}
Chroma Chroma::G()
{
	static const Chroma G(3, true);
	return G;
}
Chroma Chroma::D()
{
	static const Chroma D(4, true);
	return D;
}
Chroma Chroma::A()
{
	static const Chroma A(5, true);
	return A;
}
Chroma Chroma::E()
{
	static const Chroma E(6, true);
	return E;
}
Chroma Chroma::B()
{
	static const Chroma B(7, true);
	return B;
}
Chroma Chroma::Fs()
{
	static const Chroma Fs(8, true);
	return Fs;
}
Chroma Chroma::Cs()
{
	static const Chroma Cs(9, true);
	return Cs;
}
Chroma Chroma::Gs()
{
	static const Chroma Gs(10, true);
	return Gs;
}
Chroma Chroma::Ds()
{
	static const Chroma Ds(11, true);
	return Ds;
}
Chroma Chroma::As()
{
	static const Chroma As(12, true);
	return As;
}
Chroma Chroma::Es()
{
	static const Chroma Es(13, true);
	return Es;
}
Chroma Chroma::Bs()
{
	static const Chroma Bs(14, true);
	return Bs;
}
const std::vector<Chroma>& Chroma::circleOfFifths(const Chroma& inStartChroma /* = Chroma::A*/, const bool inHasSpelling /*= false*/)
{
	static vector<Chroma> theCircleOfFifths(12);
	for(ptrdiff_t i = 0; i < 12; ++i)
	{
		theCircleOfFifths[i] = Chroma((inStartChroma.m_LinePosition+i)%12, inHasSpelling);
	}
	return theCircleOfFifths;
}

Chroma::Chroma() 
: m_LinePosition(Chroma::undefined().m_LinePosition), m_HasSpelling(true)
{
}

Chroma::Chroma(const ptrdiff_t inCirclePosition, const bool inHasSpelling)
: m_LinePosition(inCirclePosition), m_HasSpelling(inHasSpelling)
{
}

Chroma::Chroma(const Chroma& inReference, const SimpleInterval& inInterval)
: m_LinePosition(inReference.m_LinePosition + inInterval.m_LinePosition),
  m_HasSpelling(inReference.m_HasSpelling && inInterval.hasSpelling())
{
    if (!inInterval.isTrueSimpleInterval())
    {
        m_LinePosition = inInterval.m_LinePosition;
        m_HasSpelling = true;
    }
    if (!m_HasSpelling)
    {
        m_LinePosition = wrapIntoRange(m_LinePosition, -1, 11);
    }
}

Chroma::~Chroma()
{
	// Nothing to do...
}

const ptrdiff_t Chroma::stringModifierToCircleSteps(const std::string& inStringModifier)
{
	ptrdiff_t theCircleModifier = 0;
	for (size_t i = 0; i < inStringModifier.length(); i++)
	{
		//if the next character is a flat, move 7 positions to the left
		if (!inStringModifier.substr(i,1).compare("b"))
		{
			theCircleModifier -= 7;
		}
		//if the next character is a sharp or an "s", move 7 positions to the right
		else if (!inStringModifier.substr(i,1).compare("#") || !inStringModifier.substr(i,1).compare("s"))
		{
			theCircleModifier += 7;
		}
		else
		{
			throw invalid_argument("Unknown modifier '" + inStringModifier.substr(i,1) + "'");
		}
	}
	return theCircleModifier;
}

const bool Chroma::hasSpelling() const
{
	return m_HasSpelling;
}

Chroma Chroma::withoutSpelling() const
{
	return Chroma(*this).ignoreSpelling();
}

Chroma& Chroma::ignoreSpelling()
{
    if (isTrueChroma())
    {
        m_HasSpelling = false;
    }
	return *this;
}

const bool Chroma::operator==(const Chroma& inChroma) const
{
	if (!isTrueChroma() || !inChroma.isTrueChroma() || (m_HasSpelling && inChroma.m_HasSpelling))
	{
		return m_LinePosition == inChroma.m_LinePosition;
	}
	else
	{
        return ((m_LinePosition % 12) + 12) % 12 == ((inChroma.m_LinePosition % 12) + 12) % 12;
	}
}

const bool Chroma::operator!=(const Chroma& inChroma) const
{
	return !(*this == inChroma);
}

Chroma& Chroma::operator+=(const SimpleInterval& inInterval)
{
	m_LinePosition += inInterval.m_LinePosition;
	m_HasSpelling = m_HasSpelling && inInterval.m_LinePosition;
	return *this;
}

Chroma& Chroma::operator-=(const SimpleInterval& inInterval)
{
	m_LinePosition += inInterval.m_LinePosition;
	m_HasSpelling = m_HasSpelling && inInterval.m_LinePosition;
	return *this;
}

bool Chroma::operator<(const Chroma& inChroma) const
{
	if (!isTrueChroma() || !inChroma.isTrueChroma())
	{
		return m_LinePosition < inChroma.m_LinePosition;
	}
	else
	{
		if (((m_LinePosition % 12) + 12) % 12 != ((inChroma.m_LinePosition % 12) + 12) % 12)
		{
			return ((m_LinePosition % 12) + 12) % 12 < ((inChroma.m_LinePosition % 12) + 12) % 12;
		}
		else
		{
			if (m_HasSpelling && inChroma.m_HasSpelling)
			{
				return m_LinePosition < inChroma.m_LinePosition;
			}
			else
			{
				return false;
			}
		}
	}
}

const bool Chroma::isTrueChroma() const
{
	return m_LinePosition < numeric_limits<ptrdiff_t>::max()-2;
}

const ptrdiff_t Chroma::wrapIntoRange(const ptrdiff_t inValue, const ptrdiff_t inStartIncluded, const ptrdiff_t inEndExcluded)
{
    return inStartIncluded + mod(inValue - inStartIncluded, inEndExcluded - inStartIncluded);
}

const ptrdiff_t Chroma::mod(const ptrdiff_t inValue, const ptrdiff_t inModulo)
{
    const ptrdiff_t rem = inValue % inModulo;
    return (rem < 0)?inModulo+rem:rem;
}

const ptrdiff_t Chroma::mod12(const ptrdiff_t inValue)
{
    return mod(inValue, 12);
}

#include "Segment.h"

using fei::Segment;

Segment::Segment()
: a(fei::Vec2::ZERO),
  b(fei::Vec2::ZERO)
{
}

Segment::Segment(fei::Vec2 aa, fei::Vec2 bb)
: a(aa),
  b(bb)
{
}

const fei::Vec2 Segment::getVector() const
{
	return b - a;
}

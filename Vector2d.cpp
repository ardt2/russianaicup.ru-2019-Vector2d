#include "MyStrategy.hpp"


// ============================================================================
using namespace std;


// ============================================================================
void Point2::Draw(const ColorFloat& color) const
{
	Log.Point(*this, Point2(0.2, 0.2), color);
}


// ============================================================================
void Line2::Draw(const ColorFloat& color) const
{
	Log.Line(*this, P2, color);
}


// ============================================================================
void Rect2::Draw(const ColorFloat& color) const
{
	Line2(TopLeft(), TopRight()).Draw(color);
	Line2(TopRight(), BottomRight()).Draw(color);
	Line2(BottomRight(), BottomLeft()).Draw(color);
	Line2(BottomLeft(), TopLeft()).Draw(color);
}


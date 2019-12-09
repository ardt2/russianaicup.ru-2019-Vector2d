
#ifndef _MY_VECTOR2D_HPP_
#define _MY_VECTOR2D_HPP_


// ============================================================================
#include <cmath>

#include <vector>
#include <string>


// ============================================================================
const double MyEps1 = 1e-3;


// ============================================================================
// Angle180
// ============================================================================
class Vect2;

// ----------------------------------------------------------------------------
class TAngle180
{
	// ------------------------------------------------------------------------
	public:
		// bool IsNullAngle = false; // 
		double a = 0;


	// ========================================================================
	public:
		virtual ~TAngle180()
		{
		}

		// --------------------------------------------------------------------
		TAngle180()
		{
		}

		// angle приходит от -PI до PI, в данном случае можно не проверять.
		// ----------------------------------------------------------
		TAngle180(double angle) : a(angle)
		{
		}

		// ----------------------------------------------------------
		TAngle180(const TAngle180& angle) : a(angle.a)
		{
		}

		// ----------------------------------------------------------
		//TAngle180(const TAngle180&& angle) = delete;

		// ----------------------------------------------------------
		TAngle180(const Vect2& v);


		// --------------------------------------------------------------------
		operator double() const
		{
			return a;
		}

		// ----------------------------------------------------------
		operator Vect2() const;


		// --------------------------------------------------------------------
		TAngle180& operator=(TAngle180& r)
		{
			a = r.a;

			return *this;
		}

		// --------------------------------------------------------------------
		// TAngle180& operator=(TAngle180&& r) = delete;



};


// ============================================================================
// Point2
// ============================================================================
class Vect2;

// ----------------------------------------------------------------------------
class Point2 : public Vec2Double
{
	// --------------------------------------------------------------
	public:
		bool IsNullPoint = false;


	// --------------------------------------------------------------
	public:
		// Point2() = delete; // Ладно, снижу требования для удобства.
		// Это чтобы не было неинициализированных переменных. Тут бы нужен assert времени компиляции. )

		// ------------------------------------------------
		Point2(const Vec2Double& v) : Vec2Double(v)
		{
		}

		// ------------------------------------------------
		Point2(double x, double y) : Vec2Double(x, y)
		{
		
		}

		// ------------------------------------------------
		Point2(const Point2& p = Point2(0, 0), bool isnull = false) // И Point() 
			: Vec2Double(p.x, p.y),
			  IsNullPoint(isnull)
		{
		}

		// ------------------------------------------------
		Point2(const Unit& u)
		{
			x = u.position.x;
			y = u.position.y;
		}

		// ------------------------------------------------
		Point2(const LootBox& b)
		{
			x = b.position.x;
			y = b.position.y;
		}

		// ------------------------------------------------
		Point2(const Bullet& b)
		{
			x = b.position.x;
			y = b.position.y;
		}

		// ------------------------------------------------
		Point2(const Mine& b)
		{
			x = b.position.x;
			y = b.position.y;
		}


		// ==========================================================
		operator Vec2Float() const
		{
			return Vec2Float((float)x, (float)y);
		}


		// ==========================================================
		Point2& operator=(const Point2& r)
		{
			x = r.x;
			y = r.y;

			return *this;
		}

		// ----------------------------------------------------------
		Point2& operator-=(const Vect2& rv);

		// ------------------------------------------------
		Point2& operator+=(const Vect2& rv);


		// ==========================================================
		bool operator==(const Point2& r)
		{
			return (abs(x - r.x) < MyEps1) && (abs(y - r.y) < MyEps1);
		}

		// ------------------------------------------------
		bool operator!=(const Point2& r)
		{
			return (abs(x - r.x) >= MyEps1) || (abs(y - r.y) >= MyEps1);
		}


		// ==========================================================
		std::string ToString()
		{
			return std::to_string(x).erase(5) + ", " + std::to_string(y);
		}

		// ----------------------------------------------------------
		void Draw(const ColorFloat& color = Red) const;


};

// ----------------------------------------------------------------------------
const Point2 ZeroPoint = Point2(0.0, 0.0);
const Point2 NullPoint = Point2(ZeroPoint, true);


// ============================================================================
// Vect2
// ============================================================================
class Vect2 : public Point2
{
	// --------------------------------------------------------------
	public:
		// Vect2() = delete;

		// ------------------------------------------------
		//Vect2(bool isnull = false) : Point2(isnull)		
		//{ 
		// Неявное преобразование из double! Можно explicit поставить, но сделаем Vect2() по другому.
		//}

		// ------------------------------------------------
		//explicit Vect2(const Point2& p = ZeroPoint) : Point2(p)
		//{
		// Запрещено для разделения точки и вектора.
		//}

		// ------------------------------------------------
		Vect2(const Vect2 & p = Vect2(0, 0), bool isnull = false) : Point2(p, isnull)
		{
		}

		// ------------------------------------------------
		Vect2(double x, double y) : Point2(x, y)
		{
		}

		// ------------------------------------------------
		// explicit здесь - следствие разделения точки и вектора. В паре мест придется (Vect2)v написать.
		explicit Vect2(const Vec2Double & v) : Point2(v)
		{
		}


		// ==========================================================
		Vect2& operator=(const Vect2& r)
		{
			Point2::operator=(r);

			return *this;
		}

		// ----------------------------------------------------------
		Vect2 operator-() const // Редко, но используется.
		{
			return Vect2(-x, -y);
		}

		// ----------------------------------------------------------
		Vect2 & operator+=(const Vect2 & r)
		{
			Point2::operator+=(r);

			return *this;
		}

		// ------------------------------------------------
		Vect2 operator+(const Vect2 & r) const
		{
			Vect2 res(*this);
			res.operator+=(r);

			return *this;
		}

		// ----------------------------------------------------------
		Vect2 & operator-=(const Vect2 & r)
		{
			Point2::operator-=(r);

			return *this;
		}

		// ------------------------------------------------
		Vect2 operator-(const Vect2 & r) const
		{
			Vect2 res(*this);
			res.operator-=(r);

			return *this;
		}

		// ----------------------------------------------------------
		Vect2 & operator *=(double k)
		{
			x *= k; y *= k;

			return *this;
		}

		// ------------------------------------------------
		Vect2 operator*(double k) const
		{
			Vect2 res(*this);

			return res *= k;
		}

		// ----------------------------------------------------------
		Vect2 & operator /=(double k)
		{
			const double eps = MyEps1 / 1000;
			if (abs(k) > eps)
			{
				x /= k; y /= k;
			}
			else
			{
				x /= eps; y /= eps;
			}

			return *this;
		}

		// ------------------------------------------------
		Vect2 operator/(double k) const
		{
			Vect2 res(*this);

			return res /= k;
		}

		// ==========================================================
		double Dot(const Vect2& rv)
		{
			double res = 0;

			return res;
		}

		// ------------------------------------------------
		double Cross(const Vect2& rv)
		{
			double res = 0;

			return res;
		}

		// ==========================================================
		double LenghtSqr() const
		{
			return x * x + y * y;
		}

		// ------------------------------------------------
		double Length() const
		{
			return sqrt(LenghtSqr());
		}

		// ------------------------------------------------
		Vect2& Normalize()
		{
			return operator/=(Length());
		}

		// ------------------------------------------------
		Vect2 GetNormalized() const
		{
			Vect2 res(*this);

			return res.Normalize();
		}

		// ----------------------------------------------------------
		void Draw(const ColorFloat& color = Blue)
		{
			Point2::Draw(color);
		}
};

// ------------------------------------------------------------------
const Vect2 NullVect = Vect2(Vect2(0, 0), true);
const Vect2 ZeroVect = Vect2(0.0, 0.0);


// ============================================================================
inline TAngle180::TAngle180(const Vect2& v)
{
	a = v.y == 0 ? 1e12 : atan(v.x / v.y);
}

// ----------------------------------------------------------------------------
inline TAngle180::operator Vect2() const
{
	return Vect2(std::sin(a), std::cos(a));
}


// ============================================================================
inline Point2& Point2::operator+=(const Vect2& rv)
{
	x += rv.x;
	y += rv.y;

	return *this;
}

// ------------------------------------------------------------------
inline Point2& Point2::operator-=(const Vect2& rv)
{
	x -= rv.x;
	y -= rv.y;

	return *this;
}


// ------------------------------------------------------------------
inline Vect2 operator-(const Point2& l, const Point2& r)
{
	Vect2 res(l.x, l.y);
	return res -= Vect2(r.x, r.y);
}

// ------------------------------------------------------------------
inline Point2 operator+(const Point2& l, const Vect2& r)
{
	Point2 res(l);
	return res += r;
}

// ------------------------------------------------------------------
inline Point2 operator-(const Point2& l, const Vect2& r)
{
	Point2 res(l);
	return res -= r;
}


// ============================================================================
// Line2
// ============================================================================
class Line2 : public Point2
{
	// --------------------------------------------------------------
	public:
		Point2 P2 = Point2(0,0);

	// --------------------------------------------------------------
	public:

		// ----------------------------------------------------------
		//Line2() = delete;

		// ------------------------------------------------
		Line2() : Point2(), P2()
		{
		}

		// ------------------------------------------------
		Line2(const Point2& p1, const Point2& p2) : Point2(p1), P2(p2)
		{
		}



		// ------------------------------------------------
		void Draw(const ColorFloat& color = White) const;

};

// ----------------------------------------------------------------------------
const Line2 ZeroLine(ZeroPoint, ZeroPoint);
const Line2 NullLine(NullPoint, NullPoint);


// ============================================================================
// Rect2
// ============================================================================
// Позиция (Point2) - середина нижней стороны.
class Rect2 : public Point2
{
	// --------------------------------------------------------------
	public:
		int id;
		Point2 Size;

		//const Point2& TopLeft;
		//const Point2& BottomRight;

		//std::vector<Point2> Corners = std::vector<Point2>(4, Point2());


	// --------------------------------------------------------------
	public:
		virtual ~Rect2() {}

		// ----------------------------------------------------------
		//Rect2() = delete;

		// ------------------------------------------------
		Rect2(bool isnull = false) : Rect2(NullPoint, 0, 0)
		{
		}

		// ------------------------------------------------
		Rect2(const Point2& p, double w, double h) 
			: Point2(p),
			  Size(w, h),
			  //TopLeft(Corners[0]),
			  //BottomRight(Corners[2])
			  id(-1)
		{
		}

		// ------------------------------------------------
		Rect2(const Point2& p, const Point2& size)
			: Rect2(p, size.x, size.y)
		{
		}

		// ------------------------------------------------
		Rect2(const Unit& u)
			:  Point2(u),
			   Size(u.size),
			   id(u.id)
		{
		}

		// ------------------------------------------------
		Rect2(const Bullet& b)
			:  Point2(b),
			   Size(b.size, b.size),
			   id(b.unitId)
		{
		}


		// ==========================================================
		Rect2& operator=(const Rect2& r)
		{
			Point2::operator=(r);
			Size = r.Size;
			id = r.id;
		}


		// ==========================================================
		Point2 Center() const
		{
			return *this + Vect2(0, Size.y / 2);
		}

		// ------------------------------------------------
		Point2 TopLeft() const
		{
			return *this + Vect2(-Size.x / 2, Size.y);
		}

		// ------------------------------------------------
		Point2 TopRight() const
		{
			return *this + Vect2(Size.x / 2, Size.y);
		}

		// ------------------------------------------------
		Point2 BottomRight() const
		{
			return *this + Vect2(Size.x / 2, 0); // 0 - MyEps1
		}

		// ------------------------------------------------
		Point2 BottomLeft() const
		{
			return *this + Vect2(-Size.x / 2, 0);
		}


		// ==========================================================
		bool Contain(const Point2& p) const
		{
			double topleftx = TopLeft().x, toplefty = TopLeft().y,
				bottomrightx = BottomRight().x, bottomrighty = BottomRight().y;

			if (p.x >= topleftx && p.x <= bottomrightx
				&& p.y <= toplefty && p.y >= bottomrighty)
			{
				return true;
			}

			return false;
		}

		// ----------------------------------------------------------
		bool Intersect(const Rect2& rect) const
		{
			if (rect.Contain(TopLeft())
				|| rect.Contain(TopRight())
				|| rect.Contain(BottomRight())
				|| rect.Contain(BottomLeft()))
			{
				return true;
			}

			return false;
		}


		// ==========================================================
		void Draw(const ColorFloat& color = Blue) const;

};

// ----------------------------------------------------------------------------
const Rect2 NullRect(NullPoint, NullPoint);



#endif






/*

*/
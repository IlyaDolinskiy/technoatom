#pragma once

#include <iostream>
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

float const kEps = 1e-5;

class Point2D
{

public:

  Point2D() = default;

  Point2D(Point2D const & obj)
    : m_x(obj.m_x)
    , m_y(obj.m_y)
  {}

  Point2D(float x, float y)
    : m_x(x)
    , m_y(y)
  {}

  Point2D(Point2D && obj)
  {
    std::swap(m_x, obj.m_x);
    std::swap(m_y, obj.m_y);
  }

  Point2D & operator = (Point2D && obj)
  {
    std::swap(m_x, obj.m_x);
    std::swap(m_y, obj.m_y);
    return *this;
  }

  Point2D(std::initializer_list<float> const & lst)
  {
    float * vals[] = { &m_x, &m_y };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  bool operator == (Point2D const & obj) const
  {
    return EqualWithEps(m_x, obj.m_x) && EqualWithEps(m_y, obj.m_y);
  }
  float & x() { return m_x; }
  float & y() { return m_y; }
  float const & x() const { return m_x; }
  float const & y() const { return m_y; }

  Point2D & operator = (Point2D const & obj)
  {
    if (this == &obj) return *this;
    m_x = obj.m_x;
    m_y = obj.m_y;
    return *this;
  }

  friend float atan2(Point2D const & obj) { return atan2(obj.y(), obj.x()); }

  bool operator != (Point2D const & obj) const
  {
    return !operator==(obj);
  }
  bool operator < (Point2D const & obj) const
  {
    if (m_x < obj.m_x) return true;
    return m_y < obj.m_y;
  }

  Point2D operator + (Point2D const & obj) const
  {
    return{ m_x + obj.m_x, m_y + obj.m_y };
  }
  Point2D operator - (Point2D const & obj) const
  {
    return{ m_x - obj.m_x, m_y - obj.m_y };
  }
  Point2D operator - () const
  {
    return{ -m_x, -m_y };
  }
  Point2D operator * (float scale) const
  {
    return{ m_x * scale, m_y * scale };
  }
  Point2D operator / (float scale) const
  {
    try
    {
      if (fabs(scale) < kEps) throw std::invalid_argument("Division by zero!");
      return{ m_x / scale, m_y / scale };
    }
    catch (const std::exception & ex)
    {
      std::cerr << ex.what();
    }
  }

  Point2D & operator += (Point2D const & obj)
  {
    m_x += obj.m_x;
    m_y += obj.m_y;
    return *this;
  }
  Point2D & operator -= (Point2D const & obj)
  {
    m_x -= obj.m_x;
    m_y -= obj.m_y;
    return *this;
  }
  Point2D & operator *= (float scale)
  {
    m_x *= scale;
    m_y *= scale;
    return *this;
  }
  Point2D & operator /= (float scale)
  {
    try
    {
      if (fabs(scale) < kEps) throw std::invalid_argument("Division by zero!");
      m_x /= scale;
      m_y /= scale;
      return *this;
    }
    catch (const std::exception & ex)
    {
      std::cerr << ex.what();
    }
  }

  float operator [] (unsigned int index) const
  {
    if (index >= 2) return 0.0f;
    return index == 0 ? m_x : m_y;
  }

  //struct Hash
  //{
  //  size_t operator()(Point2D const & p) const
  //  {
  //    auto hasher = std::hash<float>();
  //    return (hasher(p.x()) ^ (hasher(p.y()) << 1));
  //  }
  //};

  friend std::ostream & operator << (std::ostream & os, Point2D const & obj)
  {
    os << "Point2D {" << obj.x() << ", " << obj.y() << "}";
    return os;
  }

private:

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }

  float m_x = 0.0f, m_y = 0.0f;

};

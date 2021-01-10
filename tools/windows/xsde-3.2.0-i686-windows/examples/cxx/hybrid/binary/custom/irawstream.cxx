// file      : examples/cxx/hybrid/binary/custom/irawstream.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <string.h> // memcpy

#include "irawstream.hxx"

using namespace xml_schema;

const char* irawstream::
align (size_t a, size_t n)
{
  size_t r = pos_ % a;

  if (r)
    n += a - r;

  if (buf_.size () - pos_ < n)
    throw raw_exception ();

  const char* p = buf_.data () + pos_;

  if (r)
    p += a - r;

  pos_ += n;
  return p;
}

void irawstream::
operator>> (std::string& x)
{
  size_t n = *reinterpret_cast<const size_t*> (
    align (sizeof (size_t), sizeof (size_t)));

  x.clear ();

  if (n != 0)
  {
    x.resize (n);
    memcpy (const_cast<char*> (x.c_str ()), align (1, n), n);
  }
}

void irawstream::
operator>> (buffer& x)
{
  size_t n = *reinterpret_cast<const size_t*> (
    align (sizeof (size_t), sizeof (size_t)));

  x.size (n);

  if (n != 0)
    memcpy (x.data (), align (1, n), n);
}

void
operator>> (irawstream& s, string_sequence& x)
{
  size_t n;
  irawstream::as_size as_size (n);
  s >> as_size;

  x.clear ();

  if (n > 0)
  {
    x.reserve (n);
    std::string i;

    while (n--)
    {
      s >> i;
      x.push_back (i);
    }
  }
}

void
operator>> (irawstream& s, qname& x)
{
  std::string p, n;

  s >> p;
  s >> n;

  x.prefix (p);
  x.name (n);
}

void
operator>> (irawstream& s, time_zone& x)
{
  short h, m;
  s >> h;
  s >> m;

  x.zone_hours (h);
  x.zone_minutes (m);
}

void
operator>> (irawstream& s, date& x)
{
  int y;
  unsigned short m, d;
  bool zp;

  s >> y;
  s >> m;
  s >> d;
  s >> zp;

  x.year (y);
  x.month (m);
  x.day (d);

  if (zp)
  {
    time_zone& z = x;
    s >> z;
  }
}

void
operator>> (irawstream& s, date_time& x)
{
  int y;
  unsigned short m, d, h, mi;
  double se;
  bool zp;

  s >> y;
  s >> m;
  s >> d;
  s >> h;
  s >> mi;
  s >> se;
  s >> zp;

  x.year (y);
  x.month (m);
  x.day (d);
  x.hours (h);
  x.minutes (mi);
  x.seconds (se);

  if (zp)
  {
    time_zone& z = x;
    s >> z;
  }
}

void
operator>> (irawstream& s, duration& x)
{
  bool n;
  unsigned int y, m, d, h, mi;
  double se;

  s >> n;
  s >> y;
  s >> m;
  s >> d;
  s >> h;
  s >> mi;
  s >> se;

  x.negative (n);
  x.years (y);
  x.months (m);
  x.days (d);
  x.hours (h);
  x.minutes (mi);
  x.seconds (se);
}

void
operator>> (irawstream& s, gday& x)
{
  unsigned short d;
  bool zp;

  s >> d;
  s >> zp;

  x.day (d);

  if (zp)
  {
    time_zone& z = x;
    s >> z;
  }
}

void
operator>> (irawstream& s, gmonth& x)
{
  unsigned short m;
  bool zp;

  s >> m;
  s >> zp;

  x.month (m);

  if (zp)
  {
    time_zone& z = x;
    s >> z;
  }
}

void
operator>> (irawstream& s, gmonth_day& x)
{
  unsigned short d, m;
  bool zp;

  s >> d;
  s >> m;
  s >> zp;

  x.day (d);
  x.month (m);

  if (zp)
  {
    time_zone& z = x;
    s >> z;
  }
}

void
operator>> (irawstream& s, gyear& x)
{
  int y;
  bool zp;

  s >> y;
  s >> zp;

  x.year (y);

  if (zp)
  {
    time_zone& z = x;
    s >> z;
  }
}

void
operator>> (irawstream& s, gyear_month& x)
{
  int y;
  unsigned short m;
  bool zp;

  s >> y;
  s >> m;
  s >> zp;

  x.year (y);
  x.month (m);

  if (zp)
  {
    time_zone& z = x;
    s >> z;
  }
}

void
operator>> (irawstream& s, xml_schema::time& x)
{
  unsigned short h, m;
  double se;
  bool zp;

  s >> h;
  s >> m;
  s >> se;
  s >> zp;

  x.hours (h);
  x.minutes (m);
  x.seconds (se);

  if (zp)
  {
    time_zone& z = x;
    s >> z;
  }
}

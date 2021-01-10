// file      : examples/cxx/hybrid/binary/custom/orawstream.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <string.h> // memcpy

#include "orawstream.hxx"

using namespace xml_schema;

char* orawstream::
align (size_t a, size_t n)
{
  size_t s = buf_.size ();
  size_t c = buf_.capacity ();
  size_t r = s % a;

  if (r)
    n += a - r;

  if (c - s < n)
  {
    // Do exponential growth.
    //
    size_t nc = s + n;
    c *= 2;

    if (nc < c)
      nc = c;

    buf_.capacity (nc);
  }

  char* p = buf_.data () + s;

  if (r)
    p += a - r;

  buf_.size (s + n);
  return p;
}

void orawstream::
operator<< (const std::string& x)
{
  size_t n = x.length ();
  char* p = align (sizeof (size_t), sizeof (size_t) + n);

  *reinterpret_cast<size_t*> (p) = n;
  p += sizeof (size_t);
  memcpy (p, x.c_str (), n);
}

void orawstream::
operator<< (const buffer& x)
{
  size_t n = x.size ();
  char* p = align (sizeof (size_t), sizeof (size_t) + n);

  *reinterpret_cast<size_t*> (p) = n;
  p += sizeof (size_t);
  memcpy (p, x.data (), n);
}

void
operator<< (orawstream& s, const string_sequence& x)
{
  s << orawstream::as_size (x.size ());

  for (string_sequence::const_iterator i = x.begin ();
       i != x.end (); ++i)
  {
    s << *i;
  }
}

void
operator<< (orawstream& s, const qname& x)
{
  s << x.prefix ();
  s << x.name ();
}

void
operator<< (orawstream& s, const time_zone& x)
{
  s << x.zone_hours ();
  s << x.zone_minutes ();
}

void
operator<< (orawstream& s, const date& x)
{
  s << x.year ();
  s << x.month ();
  s << x.day ();
  bool zp = x.zone_present ();
  s << zp;

  if (zp)
  {
    const time_zone& z = x;
    s << z;
  }
}

void
operator<< (orawstream& s, const date_time& x)
{
  s << x.year ();
  s << x.month ();
  s << x.day ();
  s << x.hours ();
  s << x.minutes ();
  s << x.seconds ();
  bool zp = x.zone_present ();
  s << zp;

  if (zp)
  {
    const time_zone& z = x;
    s << z;
  }
}

void
operator<< (orawstream& s, const duration& x)
{
  s << x.negative ();
  s << x.years ();
  s << x.months ();
  s << x.days ();
  s << x.hours ();
  s << x.minutes ();
  s << x.seconds ();
}

void
operator<< (orawstream& s, const gday& x)
{
  s << x.day ();
  bool zp = x.zone_present ();
  s << zp;

  if (zp)
  {
    const time_zone& z = x;
    s << z;
  }
}

void
operator<< (orawstream& s, const gmonth& x)
{
  s << x.month ();
  bool zp = x.zone_present ();
  s << zp;

  if (zp)
  {
    const time_zone& z = x;
    s << z;
  }
}

void
operator<< (orawstream& s, const gmonth_day& x)
{
  s << x.month ();
  s << x.day ();
  bool zp = x.zone_present ();
  s << zp;

  if (zp)
  {
    const time_zone& z = x;
    s << z;
  }
}

void
operator<< (orawstream& s, const gyear& x)
{
  s << x.year ();
  bool zp = x.zone_present ();
  s << zp;

  if (zp)
  {
    const time_zone& z = x;
    s << z;
  }
}

void
operator<< (orawstream& s, const gyear_month& x)
{
  s << x.year ();
  s << x.month ();
  bool zp = x.zone_present ();
  s << zp;

  if (zp)
  {
    const time_zone& z = x;
    s << z;
  }
}

void
operator<< (orawstream& s, const xml_schema::time& x)
{
  s << x.hours ();
  s << x.minutes ();
  s << x.seconds ();
  bool zp = x.zone_present ();
  s << zp;

  if (zp)
  {
    const time_zone& z = x;
    s << z;
  }
}

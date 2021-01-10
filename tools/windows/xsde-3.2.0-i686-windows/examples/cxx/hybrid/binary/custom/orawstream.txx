// file      : examples/cxx/hybrid/binary/custom/orawostream.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <string.h> // memcpy

template <typename T>
void
operator<< (orawstream& s, const xml_schema::pod_sequence<T>& x)
{
  size_t n = x.size ();

  s << orawstream::as_size (x.size ());

  if (n != 0)
  {
    size_t mn = sizeof (T) * n;
    char* p = s.align (sizeof (T), mn);
    memcpy (p, x.begin (), mn);
  }
}

template <typename T>
void
operator<< (orawstream& s, const xml_schema::fix_sequence<T>& x)
{
  s << orawstream::as_size (x.size ());

  for (typename xml_schema::fix_sequence<T>::const_iterator i = x.begin ();
       i != x.end (); ++i)
  {
    s << *i;
  }
}

template <typename T>
void
operator<< (orawstream& s, const xml_schema::var_sequence<T>& x)
{
  s << orawstream::as_size (x.size ());

  for (typename xml_schema::var_sequence<T>::const_iterator i = x.begin ();
       i != x.end (); ++i)
  {
    s << *i;
  }
}

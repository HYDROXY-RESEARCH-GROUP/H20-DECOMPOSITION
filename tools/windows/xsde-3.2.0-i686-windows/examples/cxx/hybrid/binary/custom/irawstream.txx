// file      : examples/cxx/hybrid/binary/custom/irawostream.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <string.h> // memcpy

template <typename T>
void
operator>> (irawstream& s, xml_schema::pod_sequence<T>& x)
{
  size_t n;
  irawstream::as_size as_size (n);
  s >> as_size;

  x.clear ();

  if (n > 0)
    x.assign (
      reinterpret_cast<const T*> (s.align (sizeof (T), sizeof (T) * n)), n);
}

template <typename T>
void
operator>> (irawstream& s, xml_schema::fix_sequence<T>& x)
{
  size_t n;
  irawstream::as_size as_size (n);
  s >> as_size;

  x.clear ();

  if (n > 0)
  {
    x.reserve (n);

    while (n--)
    {
      T i;
      s >> i;
      x.push_back (i);
    }
  }
}

template <typename T>
void
operator>> (irawstream& s, xml_schema::var_sequence<T>& x)
{
  size_t n;
  irawstream::as_size as_size (n);
  s >> as_size;

  x.clear ();

  if (n > 0)
  {
    x.reserve (n);

    while (n--)
    {
      T* p = new T;
      typename xml_schema::var_sequence<T>::guard g (p);
      s >> *p;
      g.release ();
      x.push_back (p);
    }
  }
}

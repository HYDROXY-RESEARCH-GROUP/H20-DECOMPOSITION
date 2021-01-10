// file      : examples/cxx/hybrid/binary/custom/orawstream.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

inline orawstream::
orawstream (xml_schema::buffer& buf)
    : buf_ (buf)
{
}

inline void orawstream::
operator<< (bool x)
{
  *align (1, 1) = x;
}

inline void orawstream::
operator<< (signed char x)
{
  *reinterpret_cast<signed char*> (align (1, 1)) = x;
}

inline void orawstream::
operator<< (unsigned char x)
{
  *reinterpret_cast<unsigned char*> (align (1, 1)) = x;
}

inline void orawstream::
operator<< (short x)
{
  *reinterpret_cast<short*> (align (2, 2)) = x;
}

inline void orawstream::
operator<< (unsigned short x)
{
  *reinterpret_cast<unsigned short*> (align (2, 2)) = x;
}

inline void orawstream::
operator<< (int x)
{
  *reinterpret_cast<int*> (align (4, 4)) = x;
}

inline void orawstream::
operator<< (unsigned int x)
{
  *reinterpret_cast<unsigned int*> (align (4, 4)) = x;
}

inline void orawstream::
operator<< (long x)
{
  *reinterpret_cast<long*> (
    align (sizeof (long), sizeof (long))) = x;
}

inline void orawstream::
operator<< (unsigned long x)
{
  *reinterpret_cast<unsigned long*> (
    align (sizeof (unsigned long), sizeof (unsigned long))) = x;
}

#ifdef XSDE_LONGLONG
inline void orawstream::
operator<< (long long x)
{
  *reinterpret_cast<long long*> (align (8, 8)) = x;
}

inline void orawstream::
operator<< (unsigned long long x)
{
  *reinterpret_cast<unsigned long long*> (align (8, 8)) = x;
}
#endif

inline void orawstream::
operator<< (as_size x)
{
  *reinterpret_cast<size_t*> (
    align (sizeof (size_t), sizeof (size_t))) = x.s_;
}

inline void orawstream::
operator<< (float x)
{
  *reinterpret_cast<float*> (
    align (sizeof (float), sizeof (float))) = x;
}

inline void orawstream::
operator<< (double x)
{
  *reinterpret_cast<double*> (
    align (sizeof (double), sizeof (double))) = x;
}

inline void
operator<< (orawstream&, const xml_schema::any_type&)
{
}

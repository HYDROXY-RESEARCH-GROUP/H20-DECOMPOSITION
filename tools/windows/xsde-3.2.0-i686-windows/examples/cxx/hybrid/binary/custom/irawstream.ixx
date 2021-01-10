// file      : examples/cxx/hybrid/binary/custom/irawstream.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

inline irawstream::
irawstream (const xml_schema::buffer& buf, size_t start)
    : buf_ (buf), pos_ (start)
{
}

inline void irawstream::
operator>> (bool& x)
{
  x = *align (1, 1) ? 1 : 0; // Suppress VC++ "forcing value" warning.
}

inline void irawstream::
operator>> (signed char& x)
{
  x = *reinterpret_cast<const signed char*> (align (1, 1));
}

inline void irawstream::
operator>> (unsigned char& x)
{
  x = *reinterpret_cast<const unsigned char*> (align (1, 1));
}

inline void irawstream::
operator>> (short& x)
{
  x = *reinterpret_cast<const short*> (align (2, 2));
}

inline void irawstream::
operator>> (unsigned short& x)
{
  x = *reinterpret_cast<const unsigned short*> (align (2, 2));
}

inline void irawstream::
operator>> (int& x)
{
  x = *reinterpret_cast<const int*> (align (4, 4));
}

inline void irawstream::
operator>> (unsigned int& x)
{
  x = *reinterpret_cast<const unsigned int*> (align (4, 4));
}

inline void irawstream::
operator>> (long& x)
{
  x = *reinterpret_cast<const long*> (
    align (sizeof (long), sizeof (long)));
}

inline void irawstream::
operator>> (unsigned long& x)
{
  x = *reinterpret_cast<const unsigned long*> (
    align (sizeof (unsigned long), sizeof (unsigned long)));
}

#ifdef XSDE_LONGLONG
inline void irawstream::
operator>> (long long& x)
{
  x = *reinterpret_cast<const long long*> (align (8, 8));
}

inline void irawstream::
operator>> (unsigned long long& x)
{
  x = *reinterpret_cast<const unsigned long long*> (align (8, 8));
}
#endif

inline void irawstream::
operator>> (as_size& x)
{
  x.s_ = *reinterpret_cast<const size_t*> (
    align (sizeof (size_t), sizeof (size_t)));
}

inline void irawstream::
operator>> (float& x)
{
  x = *reinterpret_cast<const float*> (
    align (sizeof (float), sizeof (float)));
}

inline void irawstream::
operator>> (double& x)
{
  x = *reinterpret_cast<const double*> (
    align (sizeof (double), sizeof (double)));
}

inline void
operator>> (irawstream&, xml_schema::any_type&)
{
}

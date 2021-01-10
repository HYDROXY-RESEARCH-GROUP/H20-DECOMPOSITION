// file      : examples/cxx/hybrid/binary/custom/exceptions.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include "exceptions.hxx"

const char* raw_exception::
what () const throw ()
{
  return "RAW stream operation failed";
}

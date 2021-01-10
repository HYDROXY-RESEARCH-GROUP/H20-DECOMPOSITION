// file      : examples/cxx/hybrid/binary/custom/exceptions.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef EXCEPTIONS_HXX
#define EXCEPTIONS_HXX

#include <exception> // std::exception

struct raw_exception: std::exception
{
  virtual const char*
  what () const throw ();
};

#endif // EXCEPTIONS_HXX

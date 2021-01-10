// file      : examples/cxx/serializer/minimal/people.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef PEOPLE_HXX
#define PEOPLE_HXX

#include <stddef.h> // size_t

enum gender
{
  male,
  female
};

struct person
{
  const char* first_name_;
  const char* last_name_;
  gender gender_;
  unsigned short age_;
};

struct people
{
  person* people_;
  size_t size_;
};

#endif // PEOPLE_HXX

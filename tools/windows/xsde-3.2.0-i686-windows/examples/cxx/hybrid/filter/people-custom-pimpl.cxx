// file      : examples/cxx/hybrid/filter/people-custom-pimpl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

// Include people-pimpl.hxx (which includes people-custom-pimpl.hxx)
// instead of people-custom-pimpl.hxx.
//
#include "people-pimpl.hxx"

void people_pimpl::
age_filter (unsigned short min, unsigned short max)
{
  min_age_ = min;
  max_age_ = max;
}

void people_pimpl::
person (const ::person& p)
{
  // Check if the age constraints are met.
  //
  unsigned short age = p.age ();

  if (age >= min_age_ && age <= max_age_)
    people_base_pimpl::person (p);
}

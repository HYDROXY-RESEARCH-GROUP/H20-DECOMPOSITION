// file      : examples/cxx/hybrid/filter/people-custom-simpl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

// Include people-simpl.hxx (which includes people-custom-simpl.hxx)
// instead of people-custom-simpl.hxx.
//
#include "people-simpl.hxx"

void people_simpl::
gender_filter (gender g)
{
  gender_ = g;
}

bool people_simpl::
person_next ()
{
  // See if we have any more person records with the gender we
  // are interested in.
  //
  people::person_const_iterator& i = people_base_simpl_state_.person_;
  people::person_const_iterator& e = people_base_simpl_state_.person_end_;

  for (; i != e; ++i)
  {
    if (i->gender () == gender_)
      break;
  }

  return i != e;
}

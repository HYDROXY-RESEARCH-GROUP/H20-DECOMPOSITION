// file      : examples/cxx/serializer/polyroot/supermen-simpl-mixin.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include "supermen-simpl-mixin.hxx"

//
//
void person_simpl::
pre (const person& p)
{
  person_ = &p;
}

std::string person_simpl::
name ()
{
  return person_->name ();
}

//
//
bool superman_simpl::
can_fly ()
{
  return static_cast<const superman*> (person_)->can_fly ();
}

//
//
unsigned int batman_simpl::
wing_span ()
{
  return static_cast<const batman*> (person_)->wing_span ();
}

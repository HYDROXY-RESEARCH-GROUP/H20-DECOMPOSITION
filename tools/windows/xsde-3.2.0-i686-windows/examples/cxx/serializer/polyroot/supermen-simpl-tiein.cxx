// file      : examples/cxx/serializer/polyroot/supermen-simpl-tiein.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include "supermen-simpl-tiein.hxx"

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
superman_simpl::
superman_simpl ()
    : superman_sskel (&base_impl_)
{
}

bool superman_simpl::
can_fly ()
{
  return superman_ ().can_fly ();
}

const superman& superman_simpl::
superman_ ()
{
  return *static_cast<const superman*> (base_impl_.person_);
}

//
//
batman_simpl::
batman_simpl ()
    : batman_sskel (&base_impl_)
{
}

unsigned int batman_simpl::
wing_span ()
{
  return batman_ ().wing_span ();
}

const batman& batman_simpl::
batman_ ()
{
  return static_cast<const batman&> (base_impl_.superman_ ());
}

// file      : examples/cxx/serializer/polymorphism/supermen-simpl-tiein.cxx
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

//
//
void supermen_simpl::
pre (const supermen& s)
{
  supermen_ = &s;
  i_ = s.begin ();
}

bool supermen_simpl::
person_next ()
{
  return i_ != supermen_->end ();
}

const person& supermen_simpl::
person ()
{
  const ::person& p = **i_++;

  // Map type id to serializer type. We could have also done this in a
  // custom serializer_map implementation in which case we could simply
  // pass a pointer to the person instance as type id.
  //
  xml_schema::serializer_context& ctx = _context ();

  switch (p.type ())
  {
  case person_type:
    {
      ctx.type_id (person_sskel::_static_type ());
      break;
    }
  case superman_type:
    {
      ctx.type_id (superman_sskel::_static_type ());
      break;
    }
  case batman_type:
    {
      ctx.type_id (batman_sskel::_static_type ());
      break;
    }
  }

  return p;
}


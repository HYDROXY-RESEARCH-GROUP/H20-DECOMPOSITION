// file      : examples/cxx/serializer/polymorphism/supermen-simpl-mixin.cxx
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

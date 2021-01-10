// file      : tests/cxx/serializer/polymorphism/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test substitution groups and xsi:type support.
//
#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct base_simpl: base_sskel
{
  virtual int
  a ()
  {
    return 1;
  }
};

struct interm_type_simpl: interm_type_sskel
{
  interm_type_simpl ()
      : interm_type_sskel (&base_impl_)
  {
  }

  virtual int
  b ()
  {
    return 2;
  }

  base_simpl base_impl_;
};

struct interm_simpl: interm_sskel
{
  interm_simpl ()
      : interm_sskel (&base_impl_)
  {
  }

  virtual int
  b ()
  {
    return 2;
  }

  base_simpl base_impl_;
};

struct derived_type_simpl: derived_type_sskel
{
  derived_type_simpl ()
      : derived_type_sskel (&base_impl_)
  {
  }

  virtual int
  c ()
  {
    return 3;
  }

  interm_type_simpl base_impl_;
};

struct derived_simpl: derived_sskel
{
  derived_simpl ()
      : derived_sskel (&base_impl_)
  {
  }

  virtual int
  c ()
  {
    return 3;
  }

  interm_simpl base_impl_;
};

struct type_simpl: type_sskel
{
  virtual void
  pre ()
  {
    i_ = 0;
  }

  virtual bool
  base_next ()
  {
    return i_ < 5;
  }

  virtual void
  base ()
  {
    xml_schema::serializer_context& ctx = _context ();

    switch (i_++)
    {
    case 0:
      {
        ctx.type_id (base_sskel::_static_type ());
        break;
      }
    case 1:
      {
        ctx.type_id (interm_type_sskel::_static_type ());
        break;
      }
    case 2:
      {
        ctx.type_id (interm_sskel::_static_type ());
        break;
      }
    case 3:
      {
        ctx.type_id (derived_type_sskel::_static_type ());
        break;
      }
    case 4:
      {
        ctx.type_id (derived_sskel::_static_type ());
        break;
      }
    }
  }

private:
  int i_;
};

int
main ()
{
#ifdef XSDE_EXCEPTIONS
  try
  {
#endif
    xml_schema::int_simpl int_s;

    base_simpl base_s;
    interm_type_simpl interm_type_s;
    interm_simpl interm_s;
    derived_type_simpl derived_type_s;
    derived_simpl derived_s;

    xml_schema::serializer_map_impl map (7);
    type_simpl type_s;

    base_s.serializers (int_s);
    interm_type_s.serializers (int_s, int_s);
    interm_s.serializers (int_s, int_s);
    derived_s.serializers (int_s, int_s, int_s);
    derived_type_s.serializers (int_s, int_s, int_s);

    map.insert (base_s);
    map.insert (interm_type_s);
    map.insert (interm_s);
    map.insert (derived_s);
    map.insert (derived_type_s);

    type_s.base_serializer (map);

    xml_schema::document_simpl doc_s (type_s, "test", "root", true);

    doc_s.add_prefix ("t", "test");
    doc_s.add_prefix ("xsi", "http://www.w3.org/2001/XMLSchema-instance");

    type_s.pre ();
    doc_s.serialize (cout);

#ifndef XSDE_EXCEPTIONS
    if (doc_s._error ())
    {
      cerr << "error" << endl;
      return 1;
    }
#endif

    type_s.post ();

    // Test serializer resetting.
    //
    doc_s.reset ();

#ifdef XSDE_EXCEPTIONS
  }
  catch (xml_schema::serializer_exception const& e)
  {
    cerr << e << endl;
    return 1;
  }
#endif

  return 0;
}

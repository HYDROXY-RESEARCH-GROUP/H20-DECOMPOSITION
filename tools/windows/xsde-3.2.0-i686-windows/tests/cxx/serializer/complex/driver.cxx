// file      : tests/cxx/serializer/complex/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test complex types serialization.
//

#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct base_simpl: base_sskel
{
  virtual int
  x ()
  {
    return 123;
  }

  virtual int
  y ()
  {
    return 234;
  }

  virtual int
  a ()
  {
    return -123;
  }

  virtual int
  b ()
  {
    return -234;
  }
};

struct derived_simpl: derived_sskel
{
  derived_simpl ()
      : derived_sskel (&base_impl_)
  {
  }

  virtual int
  z ()
  {
    return 345;
  }

  virtual int
  c ()
  {
    return -345;
  }

private:
  base_simpl base_impl_;
};

struct root_simpl: root_sskel
{
};

int
main ()
{
  xml_schema::int_simpl int_s;
  base_simpl base_s;
  derived_simpl derived_s;
  root_simpl root_s;

  base_s.serializers (int_s, int_s, int_s, int_s);
  derived_s.serializers (int_s, int_s, int_s, int_s, int_s, int_s);
  root_s.serializers (base_s, derived_s);

  xml_schema::document_simpl doc_s (root_s, "test", "root");

  root_s.pre ();
  doc_s.serialize (cout);
  root_s.post ();

  return 0;
}

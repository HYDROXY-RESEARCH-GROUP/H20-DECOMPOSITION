// file      : tests/cxx/serializer/enumeration/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test enumeration type serialization.
//

#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct digit_simpl: digit_sskel
{
  digit_simpl ()
      : digit_sskel (&base_impl_)
  {
  }

private:
  xml_schema::int_simpl base_impl_;
};

struct boolean_simpl: boolean_sskel
{
  boolean_simpl ()
      : boolean_sskel (&base_impl_)
  {
  }

  virtual void
  pre (boolean b)
  {
    int i = b;
    base_impl_.pre (i);
  }

private:
  xml_schema::int_simpl base_impl_;
};

struct root_simpl: root_sskel
{
  virtual int
  digit ()
  {
    return 7;
  }

  virtual ::boolean
  boolean ()
  {
    return TRUE;
  }
};

int
main ()
{
  digit_simpl digit_s;
  boolean_simpl boolean_s;
  root_simpl root_s;

  root_s.serializers (digit_s, boolean_s);

  xml_schema::document_simpl doc_s (root_s, "test", "root");

  root_s.pre ();
  doc_s.serialize (cout);
  root_s.post ();

  return 0;
}

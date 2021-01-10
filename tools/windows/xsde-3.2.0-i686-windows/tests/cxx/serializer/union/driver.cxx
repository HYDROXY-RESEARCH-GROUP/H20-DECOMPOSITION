// file      : tests/cxx/serializer/union/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test union type serialization.
//

#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct int_bool_union_simpl: int_bool_union_sskel
{
  int_bool_union_simpl ()
      : n_ (0)
  {
  }

  virtual void
  _serialize_content ()
  {
    if (n_++ == 0)
      _characters ("123");
    else
      _characters ("false");
  }

private:
  int n_;
};

struct int_bool_base_simpl: int_bool_base_sskel
{
  int_bool_base_simpl ()
      : int_bool_base_sskel (&base_impl_)
  {
  }

  virtual int
  base ()
  {
    return 123;
  }

private:
  int_bool_union_simpl base_impl_;
};

struct root_simpl: root_sskel
{
  virtual void
  pre ()
  {
    n_ = 0;
  }

  virtual bool
  int_bool_union_next ()
  {
    return n_++ < 2;
  }

  virtual bool
  int_bool_base_next ()
  {
    return n_++ < 5;
  }

private:
  int n_;
};

int
main ()
{
  xml_schema::int_simpl int_s;
  int_bool_union_simpl int_bool_union_s;
  int_bool_base_simpl int_bool_base_s;
  root_simpl root_s;

  int_bool_base_s.serializers (int_s);
  root_s.serializers (int_bool_union_s, int_bool_base_s);

  xml_schema::document_simpl doc_s (root_s, "test", "root");

  root_s.pre ();
  doc_s.serialize (cout);
  root_s.post ();

  return 0;
}

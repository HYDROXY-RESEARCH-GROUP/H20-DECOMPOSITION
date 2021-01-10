// file      : tests/cxx/serializer/list/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test list type serialization.
//

#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct int_list_simpl: int_list_sskel
{
  int_list_simpl ()
      : n_ (0)
  {
  }

  virtual void
  pre ()
  {
    i_ = 0;
    n_++;
  }

  virtual bool
  item_next ()
  {
    switch (n_)
    {
    case 1:
      return false;
    case 2:
      return i_++ < 1;
    case 3:
      return i_++ < 3;
    default:
      return false;
    }
  }

  virtual int
  item ()
  {
    return i_;
  }

private:
  int n_, i_;
};

struct int_list_base_simpl: int_list_base_sskel
{
  int_list_base_simpl ()
      : int_list_base_sskel (&base_impl_)
  {
  }

  virtual int
  base ()
  {
    return 123;
  }

private:
  int_list_simpl base_impl_;
};

struct root_simpl: root_sskel
{
  virtual void
  pre ()
  {
    n_ = 0;
  }

  virtual bool
  int_list_next ()
  {
    return n_++ < 3;
  }

  virtual bool
  int_list_base_next ()
  {
    return n_++ < 7;
  }

private:
  int n_;
};

int
main ()
{
  xml_schema::int_simpl int_s;
  int_list_simpl int_list_s;
  int_list_base_simpl int_list_base_s;
  root_simpl root_s;

  int_list_s.serializers (int_s);
  int_list_base_s.serializers (int_s, int_s);
  root_s.serializers (int_list_s, int_list_base_s);

  xml_schema::document_simpl doc_s (root_s, "test", "root");

  root_s.pre ();
  doc_s.serialize (cout);
  root_s.post ();

  return 0;
}

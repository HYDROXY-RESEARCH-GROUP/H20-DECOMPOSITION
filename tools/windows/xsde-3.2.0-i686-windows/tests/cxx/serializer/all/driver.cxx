// file      : tests/cxx/serializer/all/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the all compositor serialization.
//

#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct test_1_simpl: test_1_sskel
{
  virtual int
  a ()
  {
    return 123;
  }

  virtual bool
  b_present ()
  {
    return true;
  }

  virtual int
  b ()
  {
    return 234;
  }
};

struct test_2_simpl: test_2_sskel
{
  test_2_simpl ()
      : i_ (0)
  {
  }

  virtual bool
  all_present ()
  {
    return i_++;
  }

  virtual int
  a ()
  {
    return 123;
  }

  virtual int
  b ()
  {
    return 234;
  }

private:
  int i_;
};

struct root_simpl: root_sskel
{
  virtual void
  pre ()
  {
    n1_ = 0;
    n2_ = 0;
  }

  virtual bool
  test_1_next ()
  {
    return n1_++ < 1;
  }

  virtual bool
  test_2_next ()
  {
    return n2_++ < 2;
  }

private:
  int n1_, n2_;
};

int
main ()
{
  xml_schema::int_simpl int_s;
  test_1_simpl test_1_s;
  test_2_simpl test_2_s;
  root_simpl root_s;

  test_1_s.serializers (int_s, int_s);
  test_2_s.serializers (int_s, int_s);
  root_s.serializers (test_1_s, test_2_s);

  xml_schema::document_simpl doc_s (root_s, "test", "root");

  root_s.pre ();
  doc_s.serialize (cout);
  root_s.post ();

  return 0;
}

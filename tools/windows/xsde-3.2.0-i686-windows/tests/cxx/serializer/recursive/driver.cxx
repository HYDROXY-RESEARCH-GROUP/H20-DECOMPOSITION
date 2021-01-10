// file      : tests/cxx/serializer/recursive/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test recursive type serialization.
//

#include <iostream>

#include "test-sskel.hxx"

using namespace std;

struct sub_type_simpl: virtual sub_type_sskel
{
  sub_type_simpl ()
      : n_ (0)
  {
  }

  virtual void
  pre ()
  {
    n_++;
  }

  // Attributes.
  //
  virtual bool
  name_present ()
  {
    return true;
  }

  virtual int
  name ()
  {
    return n_;
  }

  // Elements.
  //
  virtual bool
  sub_present ()
  {
    return n_ == 1;
  }

  virtual bool
  indir_present ()
  {
    return n_ == 1;
  }

  virtual bool
  sub2_present ()
  {
    return n_ == 1;
  }

  virtual void
  post ()
  {
    n_--;
  }

private:
  int n_;
};

struct indir_type_simpl: virtual indir_type_sskel
{
  // Attributes.
  //
  virtual bool
  name_present ()
  {
    return true;
  }

  virtual int
  name ()
  {
    return 123;
  }

  // Elements.
  //
  virtual bool
  sub_present ()
  {
    return true;
  }
};

struct test_type_simpl: virtual test_type_sskel
{
  // Attributes.
  //
  virtual bool
  name_present ()
  {
    return true;
  }

  virtual int
  name ()
  {
    return 234;
  }
};

int
main ()
{
  xml_schema::int_simpl int_s;
  sub_type_simpl sub_s;
  indir_type_simpl indir_s;
  test_type_simpl test_s;

  sub_s.serializers (int_s, sub_s, indir_s, sub_s);
  indir_s.serializers (int_s, sub_s);
  test_s.serializers (int_s, sub_s);

  xml_schema::document_simpl doc_s (test_s, "test", "root");

  test_s.pre ();
  doc_s.serialize (cout);
  test_s.post ();

  // Test serializer resetting.
  //
  doc_s.reset ();

  return 0;
}

// file      : tests/cxx/serializer/choice/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the choice compositor serialization.
//

#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct test_1_simpl: test_1_sskel
{
  test_1_simpl ()
      : i_ (0)
  {
  }

  virtual void
  pre ()
  {
    j_ = 0;
  }

  virtual choice_arm_tag
  choice_arm ()
  {
    return static_cast<choice_arm_tag> (i_++);
  }

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

  virtual bool
  c_next ()
  {
    return j_++ < 3;
  }

  virtual int
  c ()
  {
    return j_;
  }

private:
  int i_, j_;
};

struct test_2_simpl: test_2_sskel
{
  test_2_simpl ()
      : i_ (0)
  {
  }

  virtual bool
  choice_present ()
  {
    return i_++;
  }

  virtual choice_arm_tag
  choice_arm ()
  {
    return b_tag;
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

struct test_3_simpl: test_3_sskel
{
  virtual void
  pre ()
  {
    i_ = 0;
  }

  virtual bool
  choice_next ()
  {
    return i_++ < 4;
  }

  virtual choice_arm_tag
  choice_arm ()
  {
    return i_ % 2 ? a_tag : b_tag;
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

struct test_4_simpl: test_4_sskel
{
  test_4_simpl ()
      : i_ (0)
  {
  }

  virtual choice_arm_tag
  choice_arm ()
  {
    return static_cast<choice_arm_tag> (i_++);
  }

  virtual int
  a ()
  {
    return 123;
  }

  virtual choice1_arm_tag
  choice1_arm ()
  {
    return c_tag;
  }

  virtual int
  b ()
  {
    return 0;
  }

  virtual int
  c ()
  {
    return 234;
  }

  virtual int
  d ()
  {
    return 345;
  }

  virtual int
  e ()
  {
    return 456;
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
    n3_ = 0;
    n4_ = 0;
  }

  virtual bool
  test_1_next ()
  {
    return n1_++ < 3;
  }

  virtual bool
  test_2_next ()
  {
    return n2_++ < 2;
  }

  virtual bool
  test_3_next ()
  {
    return n3_++ < 1;
  }

  virtual bool
  test_4_next ()
  {
    return n4_++ < 3;
  }

private:
  int n1_, n2_, n3_, n4_;
};

int
main ()
{
  xml_schema::int_simpl int_s;
  test_1_simpl test_1_s;
  test_2_simpl test_2_s;
  test_3_simpl test_3_s;
  test_4_simpl test_4_s;
  root_simpl root_s;

  test_1_s.serializers (int_s, int_s, int_s);
  test_2_s.serializers (int_s, int_s);
  test_3_s.serializers (int_s, int_s);
  test_4_s.serializers (int_s, int_s, int_s, int_s, int_s);
  root_s.serializers (test_1_s, test_2_s, test_3_s, test_4_s);

  xml_schema::document_simpl doc_s (root_s, "test", "root");

  root_s.pre ();
  doc_s.serialize (cout);
  root_s.post ();

  return 0;
}

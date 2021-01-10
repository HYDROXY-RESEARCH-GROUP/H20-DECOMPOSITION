// file      : tests/cxx/serializer/restriction/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test inheritance-by-restriction serialization.
//

#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct test_1_simpl: test_1_sskel
{
#ifdef XSDE_REUSE_STYLE_TIEIN
  test_1_simpl ()
      : test_1_sskel (0)
  {
  }
#endif

  virtual int
  optional ()
  {
    return 123;
  }

  virtual int
  required ()
  {
    return 234;
  }
};

struct test_2_simpl: test_2_sskel
{
#ifdef XSDE_REUSE_STYLE_TIEIN
  test_2_simpl ()
      : test_2_sskel (0)
  {
  }
#endif

  virtual void
  pre ()
  {
    i_ = 0;
  }

  virtual int
  a ()
  {
    return 1;
  }

  virtual bool
  sequence_next ()
  {
    return i_++ < 1;
  }

  virtual int
  b ()
  {
    return 2;
  }

  virtual int
  c ()
  {
    return 3;
  }

  virtual choice_arm_tag
  choice_arm ()
  {
    return e_tag;
  }

  virtual int
  d ()
  {
    return 4;
  }

  virtual int
  e ()
  {
    return 5;
  }

private:
  int i_;
};

struct test_3_simpl: test_3_sskel
{
#ifdef XSDE_REUSE_STYLE_TIEIN
  test_3_simpl ()
      : test_3_sskel (0)
  {
  }
#endif

  virtual int
  a ()
  {
    return 1;
  }

  virtual int
  b ()
  {
    return 2;
  }

  virtual int
  c ()
  {
    return 3;
  }

  virtual int
  d ()
  {
    return 4;
  }

  virtual choice_arm_tag
  choice_arm ()
  {
    return g_tag;
  }

  virtual int
  e ()
  {
    return 5;
  }

  virtual int
  f ()
  {
    return 6;
  }

  virtual int
  g ()
  {
    return 7;
  }

private:
  int i_;
};

struct test_4_simpl: test_4_sskel
{
#ifdef XSDE_REUSE_STYLE_TIEIN
  test_4_simpl ()
      : test_4_sskel (0)
  {
  }
#endif

  virtual int
  a ()
  {
    return 1;
  }

  virtual int
  b ()
  {
    return 2;
  }

  virtual int
  c ()
  {
    return 3;
  }

  virtual int
  d ()
  {
    return 4;
  }

  virtual choice_arm_tag
  choice_arm ()
  {
    return g_tag;
  }

  virtual int
  e ()
  {
    return 5;
  }

  virtual int
  f ()
  {
    return 6;
  }

  virtual int
  g ()
  {
    return 7;
  }

private:
  int i_;
};

struct root_simpl: root_sskel
{
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

  test_1_s.serializers (int_s, int_s);
  test_2_s.serializers (int_s, int_s, int_s, int_s, int_s);
  test_3_s.serializers (int_s, int_s, int_s, int_s, int_s, int_s, int_s);
  test_4_s.serializers (int_s, int_s, int_s, int_s, int_s, int_s, int_s);
  root_s.serializers (test_1_s, test_2_s, test_3_s, test_4_s);

  xml_schema::document_simpl doc_s (root_s, "test", "root");

  root_s.pre ();
  doc_s.serialize (cout);
  root_s.post ();

  return 0;
}

// file      : tests/cxx/serializer/validation/choice/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test choice validation.
//

#include <sstream>
#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct test_1_simpl: virtual test_1_sskel
{
  test_1_simpl (int state)
      : state_ (state)
  {
  }

  virtual bool
  choice_next ()
  {
    return true;
  }

  virtual choice_arm_tag
  choice_arm ()
  {
    return static_cast<choice_arm_tag> (state_);
  }

  //
  //
  virtual bool
  choice1_next ()
  {
    return false;
  }

  virtual choice1_arm_tag
  choice1_arm ()
  {
    return a_tag;
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
  int state_;
};

struct root_simpl: root_sskel
{
};

int
main ()
{
  for (int i = 0; i < 2; ++i)
  {
#ifdef XSDE_EXCEPTIONS
    try
    {
#endif
      test_1_simpl test_1_s (i);
      root_simpl root_s;

      root_s.serializers (test_1_s);

      xml_schema::document_simpl doc_s (root_s, "test", "root");

      root_s.pre ();

      ostringstream os;
      doc_s.serialize (os);

#ifndef XSDE_EXCEPTIONS
      if (xml_schema::serializer_error e = doc_s._error ())
      {
        if (e.type () == xml_schema::serializer_error::schema)
        {
          cout << "schema: " << e.schema_text () << endl;
          continue;
        }
      }
#endif

      root_s.post ();
#ifdef XSDE_EXCEPTIONS
    }
    catch (xml_schema::serializer_schema const& e)
    {
      cout << "schema: " << e.text () << endl;
      continue;
    }
#endif

    cout << "no error" << endl;
  }

  return 0;
}

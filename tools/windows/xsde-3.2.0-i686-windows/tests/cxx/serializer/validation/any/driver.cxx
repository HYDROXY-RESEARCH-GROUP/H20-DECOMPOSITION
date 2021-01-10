// file      : tests/cxx/serializer/validation/any/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test any validation.
//

#include <sstream>
#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct test_1_simpl: virtual test_1_sskel
{
  virtual bool
  any_next ()
  {
    return false;
  }

  virtual void
#ifdef XSDE_STL
  any (std::string&, std::string&)
  {
#else
  any (const char*&, const char*&, bool&)
  {
#endif
  }

  virtual void
  serialize_any ()
  {
  }
};

// ##any
//
struct test_2_simpl: virtual test_2_sskel
{
  virtual void
#ifdef XSDE_STL
  any (std::string& ns, std::string& name)
  {
#else
  any (const char*& ns, const char*& name, bool& free)
  {
    free = false;
#endif
    ns = "foo";
    name = "";
  }

  virtual void
  serialize_any ()
  {
  }
};

// ##other
//
struct test_3_simpl: virtual test_3_sskel
{
  test_3_simpl (int state)
      : state_ (state)
  {
  }

  virtual void
#ifdef XSDE_STL
  any (std::string& ns, std::string& name)
  {
#else
  any (const char*& ns, const char*& name, bool& free)
  {
    free = false;
#endif
    switch (state_)
    {
    case 2:
      {
        // target
        //
        ns = "test";
        name = "x";
        break;
      }
    case 3:
      {
        // local
        //
        ns = "";
        name = "x";
        break;
      }
    }
  }

  virtual void
  serialize_any ()
  {
  }

private:
  int state_;
};

// ##local
//
struct test_4_simpl: virtual test_4_sskel
{
  virtual void
#ifdef XSDE_STL
  any (std::string& ns, std::string& name)
  {
#else
  any (const char*& ns, const char*& name, bool& free)
  {
    free = false;
#endif
    ns = "foo";
    name = "x";
  }

  virtual void
  serialize_any ()
  {
  }
};

// ##targetNamespace
//
struct test_5_simpl: virtual test_5_sskel
{
  test_5_simpl (int state)
      : state_ (state)
  {
  }

  virtual void
#ifdef XSDE_STL
  any (std::string& ns, std::string& name)
  {
#else
  any (const char*& ns, const char*& name, bool& free)
  {
    free = false;
#endif
    switch (state_++)
    {
    case 5:
      {
        // target
        //
        ns = "foo";
        name = "x";
        break;
      }
    case 6:
      {
        // local
        //
        ns = "";
        name = "x";
        break;
      }
    }
  }

  virtual void
  serialize_any ()
  {
  }

private:
  int state_;
};

// foo
//
struct test_6_simpl: virtual test_6_sskel
{
  test_6_simpl (int state)
      : state_ (state)
  {
  }

  virtual void
#ifdef XSDE_STL
  any (std::string& ns, std::string& name)
  {
#else
  any (const char*& ns, const char*& name, bool& free)
  {
    free = false;
#endif
    switch (state_++)
    {
    case 7:
      {
        // bar
        //
        ns = "bar";
        name = "x";
        break;
      }
    case 8:
      {
        // local
        //
        ns = "";
        name = "x";
        break;
      }
    }
  }

  virtual void
  serialize_any ()
  {
  }

private:
  int state_;
};

struct root_simpl: root_sskel
{
  root_simpl (int state)
      : state_ (state)
  {
  }

  virtual choice_arm_tag
  choice_arm ()
  {
    switch (state_)
    {
    case 0:
      return test_1_tag;
    case 1:
      return test_2_tag;
    case 2:
    case 3:
      return test_3_tag;
    case 4:
      return test_4_tag;
    case 5:
    case 6:
      return test_5_tag;
    case 7:
    case 8:
      return test_5_tag;
    default:
      return choice_arm_tag (state_);
    }
  }

private:
  int state_;
};

int
main ()
{
  for (int i = 0; i < 9; ++i)
  {
#ifdef XSDE_EXCEPTIONS
    try
    {
#endif
      test_1_simpl test_1_s;
      test_2_simpl test_2_s;
      test_3_simpl test_3_s (i);
      test_4_simpl test_4_s;
      test_5_simpl test_5_s (i);
      test_6_simpl test_6_s (i);
      root_simpl root_s (i);

      root_s.serializers (test_1_s, test_2_s, test_3_s, test_4_s,
                          test_5_s, test_6_s);

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

// file      : tests/cxx/parser/error-handling/codes/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test error reporting with error codes.
//

#include <string>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>

#include "test-pskel.hxx"

using namespace std;
using namespace test;

struct person_pimpl: person_pskel
{
  person_pimpl (unsigned long i)
      : i_ (i)
  {
  }

  virtual void
  pre ()
  {
    if (i_ == 4)
      _app_error (4);
  }

#ifdef XSDE_STL
  virtual void
  id (string const&)
  {
    if (i_ == 5)
      _app_error (5);
  }
#else
  virtual void
  id (char* s)
  {
    delete[] s;

    if (i_ == 5)
      _app_error (5);
  }
#endif

  virtual void
  age (int age)
  {
    if (i_ == 6)
      _app_error (6);

    age_ = age;
  }

  virtual int
  post_person ()
  {
    if (i_ == 7)
    {
      _app_error (7);
      return 0;
    }

    return age_;
  }

private:
  int age_;
  unsigned long i_;

};


struct type_pimpl: type_pskel
{
  type_pimpl (unsigned long i)
      : i_ (i)
  {
  }

  virtual void
  pre ()
  {
    if (i_ == 1)
      _app_error (1);
  }

  virtual void
  person (int)
  {
    if (i_ == 2)
      _app_error (2);
  }

  virtual void
  post_type ()
  {
    if (i_ == 3)
      _app_error (3);
  }

private:
  unsigned long i_;
};

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " test.xml" << endl;
    return 1;
  }

  // 0: xml error
  //
  // 1: app error from top-level pre
  // 2: app error from top-level callback
  // 3: app error from top-level post
  // 4: app error from nested pre
  // 5: app error from nested attribute callback
  // 6: app error from nested element callback
  // 7: app error from nested post
  //
  // 8: schema error (root element mismatch)
  // 9: schema error (missing required element)
  // 10: schema error (missing required attribute)
  // 11: schema error (extraneous element)
  // 12: schema error (extraneous attribute)
  // 13: schema error (invalid datatype value)
  //
  // 14: io error (no such file)
  //
  //
  for (unsigned long i (0); i < 15; ++i)
  {
    xml_schema::int_pimpl int_p;
    xml_schema::string_pimpl string_p;
    person_pimpl person_p (i);
    type_pimpl type_p (i);

    person_p.parsers (string_p, int_p);
    type_p.parsers (person_p);

    xml_schema::document_pimpl doc_p (type_p, "test", "root");

    //
    //
    typedef xml_schema::parser_error error;

    type_p.pre ();

    if (error e = type_p._error ())
    {
      assert (e.type () == error::app);
      cout << "app: " << e.app_code () << endl;
      continue;
    }


    if (i == 0)
    {
      istringstream is ("<t:root xmlns:t='test'>\n</t:rot>");
      doc_p.parse (is);
    }
    else if (i == 8)
    {
      istringstream is ("<t:rot xmlns:t='test'>\n</t:rot>");
      doc_p.parse (is);
    }
    else if (i == 9)
    {
      istringstream is (
        "<t:root xmlns:t='test'>\n"
        "<person id='a'/>\n"
        "</t:root>");
      doc_p.parse (is);
    }
    else if (i == 10)
    {
      istringstream is (
        "<t:root xmlns:t='test'>\n"
        "<person><age>64</age></person>\n"
        "</t:root>");
      doc_p.parse (is);
    }
    else if (i == 11)
    {
      istringstream is (
        "<t:root xmlns:t='test'>\n"
        "<person id='a'>\n"
        "<age>64</age>\n"
        "<foo/>\n"
        "</person>\n"
        "</t:root>");
      doc_p.parse (is);
    }
    else if (i == 12)
    {
      istringstream is (
        "<t:root xmlns:t='test'>\n"
        "<person id='a' foo='f'>\n"
        "<age>64</age>\n"
        "</person>\n"
        "</t:root>");
      doc_p.parse (is);
    }
    else if (i == 13)
    {
      istringstream is (
        "<t:root xmlns:t='test'>\n"
        "<person id='a'>\n"
        "<age>a64</age>\n"
        "</person>\n"
        "</t:root>");
      doc_p.parse (is);
    }
    else if (i == 14)
    {
      doc_p.parse ("no-such-file.xml");
    }
    else
      doc_p.parse (argv[1]);


    if (error e = doc_p._error ())
    {
      switch (e.type ())
      {
      case error::sys:
        {
          cout << "sys: " << e.sys_code () << ": " << e.sys_text ()
               << endl;
          break;
        }
      case error::xml:
        {
          cout << "xml:" << e.line () << ":" << e.column () << ": "
               << e.xml_code () << ": " << e.xml_text () << endl;
          break;
        }
      case error::schema:
        {
          cout << "schema:" << e.line () << ":" << e.column () << ": "
               << e.schema_code () << ": " << e.schema_text () << endl;
          break;
        }
      case error::app:
        {
          cout << "app:" << e.line () << ":" << e.column () << ": "
               << e.app_code () << endl;
          break;
        }
      default:
        {
          cout << "no error" << endl;
          break;
        }
      }

      continue;
    }

    type_p.post_type ();

    if (error e = type_p._error ())
    {
      assert (e.type () == error::app);
      cout << "app: " << e.app_code () << endl;
      continue;
    }
  }

  return 0;
}

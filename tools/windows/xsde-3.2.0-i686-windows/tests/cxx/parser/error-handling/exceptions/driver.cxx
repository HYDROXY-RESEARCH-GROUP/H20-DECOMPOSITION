// file      : tests/cxx/parser/error-handling/exceptions/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test error reporting with exceptions.
//

#include <string>
#include <sstream>
#include <iostream>

#include "test-pskel.hxx"

using namespace std;
using namespace test;

struct app
{
  app (unsigned long code)
      : code_ (code)
  {
  }

  unsigned long
  code () const
  {
    return code_;
  }

private:
  unsigned long code_;
};

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
      throw app (4);
  }

#ifdef XSDE_STL
  virtual void
  id (string const&)
  {
    if (i_ == 5)
      throw app (5);
  }
#else
  virtual void
  id (char* s)
  {
    delete[] s;

    if (i_ == 5)
      throw app (5);
  }
#endif

  virtual void
  age (int age)
  {
    if (i_ == 6)
      throw app (6);

    age_ = age;
  }

  virtual int
  post_person ()
  {
    if (i_ == 7)
      throw app (7);

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
      throw app (1);
  }

  virtual void
  person (int)
  {
    if (i_ == 2)
      throw app (2);
  }

  virtual void
  post_type ()
  {
    if (i_ == 3)
      throw app (3);
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
    try
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
      type_p.pre ();

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

      type_p.post_type ();
    }
    catch (ios_base::failure const&)
    {
      cout << "io: io error" << endl;
    }
    catch (xml_schema::parser_xml const& e)
    {
      cout << "xml:" << e.line () << ":" << e.column () << ": "
           << e.code () << ": " << e.text () << endl;
    }
    catch (xml_schema::parser_schema const& e)
    {
      cout << "schema:" << e.line () << ":" << e.column () << ": "
           << e.code () << ": " << e.text () << endl;
    }
    catch (app const& e)
    {
      cout << "app: " << e.code () << endl;
    }
  }

  return 0;
}

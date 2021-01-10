// file      : tests/cxx/serializer/error-handling/exceptions/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test error reporting with exceptions.
//

#include <cassert>
#include <sstream>
#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct app
{
  app (int code)
      : code_ (code)
  {
  }

  int
  code () const
  {
    return code_;
  }

private:
  int code_;
};

struct test_simpl: virtual test_sskel
{
  test_simpl (int c)
      : case_ (c)
  {
  }

  virtual void
  pre ()
  {
    if (case_ == 6)
      throw app (case_);

    n_ = 0;
  }

  virtual void
  _pre ()
  {
    if (case_ == 7)
      throw app (case_);

    if (case_ == 19)
      _end_element ();
  }

  // Attributes.
  //
  virtual bool
  x_present ()
  {
    if (case_ == 8)
    {
      throw app (case_);
      return false;
    }

    return true;
  }

  virtual int
  x ()
  {
    if (case_ == 9)
      throw app (case_);

    return -1;
  }

  virtual int
  y ()
  {
    if (case_ == 10)
      throw app (case_);

    return -2;
  }

  // Elements.
  //
  virtual int
  a ()
  {
    if (case_ == 11)
      throw app (case_);

    return 1;
  }

  virtual bool
  b_present ()
  {
    if (case_ == 12)
    {
      throw app (case_);
      return false;
    }

    return true;
  }

  virtual int
  b ()
  {
    if (case_ == 13)
      throw app (case_);

    return 2;
  }

  virtual bool
  c_next ()
  {
    if (case_ == 14)
    {
      throw app (case_);
      return false;
    }

    return n_++ < 3;
  }

  virtual int
  c ()
  {
    if (case_ == 15)
      throw app (case_);

    return 2 + n_;
  }

  virtual void
  _post ()
  {
    if (case_ == 16)
      throw app (case_);
  }

  virtual void
  post ()
  {
    if (case_ == 17)
      throw app (case_);
  }

private:
  int case_;
  int n_;
};

struct root_simpl: root_sskel
{
  root_simpl (int c)
      : case_ (c)
  {
  }

  virtual void
  pre ()
  {
    if (case_ == 1)
      throw app (case_);
  }

  virtual void
  _pre ()
  {
    if (case_ == 2)
      throw app (case_);
  }

  virtual void
  test ()
  {
    if (case_ == 3)
      throw app (case_);
  }

  virtual void
  _post ()
  {
    if (case_ == 4)
      throw app (case_);
  }

  virtual void
  post ()
  {
    if (case_ == 5)
      throw app (case_);
  }

private:
  int case_;
};

struct writer: xml_schema::writer
{
  virtual void
  write (const char*, size_t)
  {
    throw ios_base::failure ("write failed");
  }

  virtual void
  flush ()
  {
    throw ios_base::failure ("write failed");
  }
};

int
main ()
{

  // 1-5 : app errors in the root element serializer
  // 6-17: app errors in the sub element serializer
  // 18  : xml error in document serializer
  // 19  : xml error in sub element serializer
  // 20  : sys error
  //
  for (int i (1); i <= 20; ++i)
  {
    try
    {
      xml_schema::int_simpl int_s;
      test_simpl test_s (i);
      root_simpl root_s (i);

      test_s.serializers (int_s, int_s, int_s, int_s, int_s);
      root_s.serializers (test_s);

      xml_schema::document_simpl doc_s (
        root_s,
        "test",
        (i == 18 ? "bad name" : "root"));

      root_s.pre ();

      ostringstream os;

      if (i == 20)
      {
        writer w;
        doc_s.serialize (w);
      }
      else
        doc_s.serialize (os);

      root_s.post ();
    }
    catch (ios_base::failure const&)
    {
      cout << "sys: write failed" << endl;
    }
    catch (xml_schema::serializer_xml const& e)
    {
      cout << "xml: " << e.text () << endl;
    }
#ifdef XSDE_SERIALIZER_VALIDATION
    catch (xml_schema::serializer_schema const& e)
    {
      cout << "schema: " << e.text () << endl;
    }
#endif
    catch (app const& e)
    {
      cout << "app: " << e.code () << endl;
    }
  }

  return 0;
}

// file      : tests/cxx/serializer/error-handling/codes/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test error reporting with error codes.
//

#include <cassert>
#include <sstream>
#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

// bool fail = true;

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
      _app_error (case_);

    n_ = 0;
  }

  virtual void
  _pre ()
  {
    if (case_ == 7)
      _app_error (case_);

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
      _app_error (case_);
      return false;
    }

    return true;
  }

  virtual int
  x ()
  {
    if (case_ == 9)
      _app_error (case_);

    return -1;
  }

  virtual int
  y ()
  {
    if (case_ == 10)
      _app_error (case_);

    return -2;
  }

  // Elements.
  //
  virtual int
  a ()
  {
    if (case_ == 11)
      _app_error (case_);

    return 1;
  }

  virtual bool
  b_present ()
  {
    if (case_ == 12)
    {
      _app_error (case_);
      return false;
    }

    return true;
  }

  virtual int
  b ()
  {
    if (case_ == 13)
      _app_error (case_);

    return 2;
  }

  virtual bool
  c_next ()
  {
    if (case_ == 14)
    {
      _app_error (case_);
      return false;
    }

    return n_++ < 3;
  }

  virtual int
  c ()
  {
    if (case_ == 15)
      _app_error (case_);

    return 2 + n_;
  }

  virtual void
  _post ()
  {
    if (case_ == 16)
      _app_error (case_);
  }

  virtual void
  post ()
  {
    if (case_ == 17)
      _app_error (case_);
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
      _app_error (case_);
  }

  virtual void
  _pre ()
  {
    if (case_ == 2)
      _app_error (case_);
  }

  virtual void
  test ()
  {
    if (case_ == 3)
      _app_error (case_);
  }

  virtual void
  _post ()
  {
    if (case_ == 4)
      _app_error (case_);
  }

  virtual void
  post ()
  {
    if (case_ == 5)
      _app_error (case_);
  }

private:
  int case_;
};

struct writer: xml_schema::writer
{
  virtual bool
  write (const char*, size_t)
  {
    return false;
  }

  virtual bool
  flush ()
  {
    return false;
  }
};


void
print (xml_schema::serializer_error e)
{
  typedef xml_schema::serializer_error error;

  switch (e.type ())
  {
  case error::sys:
    {
      cout << "sys: " << e.sys_code () << ": " << e.sys_text () << endl;
      break;
    }
  case error::xml:
    {
      cout << "xml: " << e.xml_code () << ": " << e.xml_text () << endl;
      break;
    }
#ifdef XSDE_SERIALIZER_VALIDATION
  case error::schema:
    {
      cout << "schema: " << e.schema_code () << ": " << e.schema_text ()
           << endl;
      break;
    }
#endif
  case error::app:
    {
      cout << "app: " << e.app_code () << endl;
      break;
    }
  default:
    {
      cout << "no error" << endl;
      break;
    }
  }
}

int
main ()
{
  typedef xml_schema::serializer_error error;

  /*
  string output ("<g1:root xmlns:g1=\"test\"><test x=\"-1\" y=\"-2\">"
                 "<a>1</a><b>2</b><c>3</c><c>4</c><c>5</c></test></g1:root>");
  */

  // 1-5 : app errors in the root element serializer
  // 6-17: app errors in the sub element serializer
  // 18  : xml error in document serializer
  // 19  : xml error in sub element serializer
  // 20  : sys error
  //
  for (int i (1); i <= 20; ++i)
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

    if (error e = root_s._error ())
      print (e);
    else
    {
      ostringstream os;

      if (i == 20)
      {
        writer w;
        doc_s.serialize (w);
      }
      else
        doc_s.serialize (os);

      if (error e = doc_s._error ())
        print (e);
      else
      {
        root_s.post ();

        if (error e = root_s._error ())
          print (e);
      }
    }

    /*
    {
      fail = false;

      ostringstream os;

      root_s.pre ();
      assert (!root_s.error ());

      doc_s.serialize (os);
      assert (!doc_s._error ());

      root_s.post ();
      assert (!root_s.error ());

      assert (os.str () == output);

      fail = true;
    }
    */
  }

  return 0;
}

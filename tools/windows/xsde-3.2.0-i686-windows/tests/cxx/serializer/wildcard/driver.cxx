// file      : tests/cxx/serializer/wildcard/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test wildcard (any & anyAttribute) serialization.
//

#include <string.h> // strcpy
#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct content_simpl: virtual content_sskel
{
  virtual int
  x ()
  {
    return 123;
  }

  virtual int
  a ()
  {
    return 321;
  }
};

struct root_simpl: virtual root_sskel
{
#ifdef XSDE_REUSE_STYLE_TIEIN
  root_simpl ()
      : root_sskel (0)
  {
  }
#endif

  virtual void
  pre ()
  {
    aa1_ = 0;
    aa2_ = 0;
    choice_ = 0;
    ae1_ = 0;
  }

  // anyAttribute
  //
  virtual bool
  any_attribute_next ()
  {
    return aa2_++ < 1;
  }

#ifdef XSDE_STL
  virtual void
  any_attribute (std::string& ns, std::string& name)
  {
    ns = "foo";
    name = "x";
  }
#else
  virtual void
  any_attribute (const char*& ns, const char*& name, bool& free)
  {
    char* ns_ = new char[4];
    char* name_ = new char[2];

    strcpy (ns_, "foo");
    strcpy (name_, "x");

    ns = ns_;
    name = name_;
    free = true;
  }
#endif

  virtual void
  serialize_any_attribute ()
  {
    _characters ("foo#x");
  }

    virtual bool
  any_attribute1_next ()
  {
    return aa1_++ < 1;
  }

#ifdef XSDE_STL
  virtual void
  any_attribute1 (std::string& ns, std::string& name)
  {
    ns = "";
    name = "x";
  }
#else
  virtual void
  any_attribute1 (const char*& ns, const char*& name, bool& free)
  {
    ns = "";
    name = "x";
    free = false;
  }
#endif

  virtual void
  serialize_any_attribute1 ()
  {
    _characters ("##local#x");
  }

  // any
  //
#ifdef XSDE_STL
  virtual void
  any (std::string& ns, std::string& name)
  {
    ns = "";
    name = "a";
  }
#else
  virtual void
  any (const char*& ns, const char*& name, bool& free)
  {
    ns = "";
    name = "a";
    free = false;
  }
#endif


  virtual void
  serialize_any ()
  {
    xml_schema::int_simpl int_s;
    content_simpl content_s;

    content_s.serializers (int_s, int_s);

    content_s.pre ();
    content_s._pre_impl (_context ());
    content_s._serialize_attributes ();
    content_s._serialize_content ();
    content_s._post_impl ();
    content_s.post ();
  }

  virtual bool
  choice_next ()
  {
    return choice_ < 2;
  }

  virtual choice_arm_tag
  choice_arm ()
  {
    return static_cast<choice_arm_tag> (choice_++);
  }

  virtual bool
  any1_next ()
  {
    return ae1_ < 3;
  }

#ifdef XSDE_STL
  virtual void
  any1 (::std::string& ns, ::std::string& name)
  {
    ns = "foo";
    name = "a";
  }
#else
  virtual void
  any1 (const char*& ns, const char*& name, bool& free)
  {
    ns = "foo";
    name = "a";
    free = false;
  }
#endif

  virtual void
  serialize_any1 ()
  {
    xml_schema::int_simpl s;

    s.pre (ae1_++);
    s._pre_impl (_context ());
    s._serialize_content ();
    s._post_impl ();
    s.post ();
  }

  virtual bool
  any2_present ()
  {
    return true;
  }

#ifdef XSDE_STL
  virtual void
  any2 (std::string& ns, std::string& name)
  {
    ns = "bar";
    name = "b";
  }
#else
  virtual void
  any2 (const char*& ns, const char*& name, bool& free)
  {
    ns = "bar";
    name = "b";
    free = false;
  }
#endif

  virtual void
  serialize_any2 ()
  {
    _characters ("bar#b");
  }

private:
  int aa1_, aa2_;
  int choice_;
  int ae1_;
};

int
main ()
{
  root_simpl root_s;

  xml_schema::document_simpl doc_s (root_s, "test", "root");

  root_s.pre ();
  doc_s.serialize (cout);
  root_s.post ();

  return 0;
}

// file      : examples/cxx/serializer/hello/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <string>
#include <vector>
#include <iostream>

#include "hello-sskel.hxx"

using namespace std;

struct hello_simpl: hello_sskel
{
  hello_simpl ()
  {
    names_.push_back ("sun");
    names_.push_back ("moon");
    names_.push_back ("world");
  }

  virtual void
  pre ()
  {
    i_ = names_.begin ();
  }

  virtual string
  greeting ()
  {
    return "Hello";
  }

  virtual bool
  name_next ()
  {
    return i_ != names_.end ();
  }

  virtual string
  name ()
  {
    return *i_++;
  }

private:
  typedef vector<string> names;

  names names_;
  names::iterator i_;
};


int
main ()
{
  try
  {
    // Construct the serializer.
    //
    xml_schema::string_simpl string_s;
    hello_simpl hello_s;

    hello_s.greeting_serializer (string_s);
    hello_s.name_serializer (string_s);


    // Create the XML instance document. The second argument to the
    // document's constructor is the document's root element name.
    //
    xml_schema::document_simpl doc_s (hello_s, "hello");
    doc_s.add_no_namespace_schema ("hello.xsd");

    hello_s.pre ();
    doc_s.serialize (cout, xml_schema::document_simpl::pretty_print);
    hello_s.post ();
  }
  catch (const xml_schema::serializer_exception& e)
  {
    cerr << "error: " << e.text () << endl;
    return 1;
  }
  catch (const std::ios_base::failure&)
  {
    cerr << "error: write failure" << endl;
    return 1;
  }

  return 0;
}

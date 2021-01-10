// file      : examples/cxx/parser/hello/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <string>
#include <iostream>

#include "hello-pskel.hxx"

using namespace std;

struct hello_pimpl: hello_pskel
{
  virtual void
  greeting (const string& greeting)
  {
    greeting_ = greeting;
  }

  virtual void
  name (const string& name)
  {
    cout << greeting_ << ", " << name << "!" << endl;
  }

private:
  string greeting_;
};


int
main (int argc, char* argv[])
{
  const char* input;

  if (argc < 2)
  {
    input = "STDIN";
    cerr << "XML file not specified, reading from STDIN" << endl;
  }
  else
    input = argv[1];

  try
  {
    // Construct the parser.
    //
    xml_schema::string_pimpl string_p;
    hello_pimpl hello_p;

    hello_p.greeting_parser (string_p);
    hello_p.name_parser (string_p);


    // Parse the XML instance document. The second argument to the
    // document's constructor is the document's root element name.
    //
    xml_schema::document_pimpl doc_p (hello_p, "hello");

    hello_p.pre ();

    if (argc < 2)
      doc_p.parse (cin);
    else
      doc_p.parse (argv[1]);

    hello_p.post_hello ();
  }
  catch (const xml_schema::parser_exception& e)
  {
    cerr << input << ":" << e.line () << ":" << e.column () << ": "
         << e.text () << endl;
    return 1;
  }
  catch (const std::ios_base::failure&)
  {
    cerr << input << ": unable to open or read failure" << endl;
    return 1;
  }

  return 0;
}

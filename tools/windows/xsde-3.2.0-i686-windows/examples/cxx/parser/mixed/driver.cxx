// file      : examples/cxx/parser/mixed/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <string>
#include <vector>
#include <iostream>

#include "anchor.hxx"
#include "text-pskel.hxx"

#ifndef XSDE_REUSE_STYLE_TIEIN
#  error this example requires the tiein parser reuse support
#endif

using namespace std;

struct anchor_pimpl: anchor_pskel
{
  anchor_pimpl ()
      : anchor_pskel (&base_impl_)
  {
  }

  virtual void
  href (const std::string& uri)
  {
    uri_ = uri;
  }

  virtual anchor
  post_anchor ()
  {
    return anchor (post_string (), uri_);
  }

private:
  xml_schema::string_pimpl base_impl_;
  std::string uri_;
};


struct text_pimpl: text_pskel
{
  virtual void
  a (const anchor& a)
  {
    cout << a.text () << "[" << anchors_.size () << "]";
    anchors_.push_back (a);
  }

  virtual void
  _any_characters (const xml_schema::ro_string& s)
  {
    cout << s;
  }

  virtual void
  post_text ()
  {
    for (anchors::const_iterator i (anchors_.begin ());
         i != anchors_.end ();
         ++i)
    {
      cout << "[" << i - anchors_.begin () << "] " << i->uri () << endl;
    }
  }

private:
  typedef vector<anchor> anchors;
  anchors anchors_;
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
    anchor_pimpl anchor_p;
    text_pimpl text_p;

    anchor_p.href_parser (string_p);
    text_p.a_parser (anchor_p);

    xml_schema::document_pimpl doc_p (text_p, "text");

    text_p.pre ();

    if (argc < 2)
      doc_p.parse (cin);
    else
      doc_p.parse (argv[1]);

    text_p.post_text ();
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

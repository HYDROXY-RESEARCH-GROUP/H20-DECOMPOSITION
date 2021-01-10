// file      : examples/cxx/parser/polyroot/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>

#include "supermen-pskel.hxx" // Get the configuration macros (XSDE_*).

#if defined(XSDE_REUSE_STYLE_MIXIN)
#  include "supermen-pimpl-mixin.hxx"
#elif defined(XSDE_REUSE_STYLE_TIEIN)
#  include "supermen-pimpl-tiein.hxx"
#else
#  error this example requires mixin or tiein parser reuse support
#endif

using std::cerr;
using std::endl;
using xml_schema::ro_string;

// Customize the xml_schema::document object to handle polymorphic
// root element. For more information see the multiroot example.
//
class document_pimpl: public xml_schema::document_pimpl
{
public:
  // Passing the root element name to xml_schema::document_pimpl
  // constructor indicates that we are doing polymorphic parsing.
  // The root element name is used to automatically translate
  // substitutions to type information.
  //
  document_pimpl (xml_schema::parser_map& parser_map)
      : xml_schema::document_pimpl ("person"),
        parser_map_ (parser_map),
        parser_used_ (0)
  {
  }

protected:
  // This function is called to obtain the root element type parser.
  // If the returned pointer is 0 then the whole document content
  // is ignored. The type argument contains the XML Schema type
  // if xsi:type attribute or an element that substitutes the root
  // was specified and 0 otherwise.
  //
  virtual xml_schema::parser_base*
  start_root_element (const ro_string& ns,
                      const ro_string& name,
                      const char* type)
  {
    if (name != "person" || !ns.empty ())
    {
      // If the runtime and the generated code are built with
      // validation enabled then we can also set an XML Schema
      // error.
      //
#ifdef XSDE_PARSER_VALIDATION
      context_.schema_error (
        xml_schema::parser_schema_error::unexpected_element);
#endif
      return 0;
    }

    // Search the parser map. If type is 0 then there is no xsi:type and
    // static type should be used.
    //
    xml_schema::parser_base* p = parser_map_.find (
      type ? type : person_pskel::_static_type ());

    if (p != 0)
    {
      // The map returns a generic parser_base which we will cast to
      // person_pskel in order to call the pre() and post_person()
      // callbacks. If the runtime and the generated code are built
      // with the mixin parser reuse style then we have to use
      // dynamic_cast because of the virtual inheritance.
      //
#ifdef XSDE_REUSE_STYLE_MIXIN
      parser_used_ = dynamic_cast<person_pskel*> (p);
#else
      parser_used_ = static_cast<person_pskel*> (p);
#endif
      parser_used_->pre ();
    }
    else
    {
      // No parser for this type. We could also make this an error
      // by calling the schema_error() function as above.
      //
      parser_used_ = 0;
    }

    return p;
  }

  // This function is called to indicate the completion of document
  // parsing. The parser argument contains the pointer returned by
  // start_root_element.
  //
  virtual void
  end_root_element (const ro_string& /* ns */,
                    const ro_string& /* name */,
                    xml_schema::parser_base* /* parser */)
  {
    // Instead of caching the current parser in parser_used_, we
    // could also cast the parser argument to the person_pskel
    // type.
    //
    if (parser_used_)
      parser_used_->post_person ();
  }

public:
  // If we need to be able to reset and reuse the parser after
  // an error then we also need to override reset() and reset
  // the parser that was used last. Note that you always need
  // to call _reset() from the base.
  //
  virtual void
  reset ()
  {
    xml_schema::document_pimpl::reset ();

    if (parser_used_)
      parser_used_->_reset ();
  }

private:
  xml_schema::parser_map& parser_map_;
  person_pskel* parser_used_;
};

int
main (int argc, char* argv[])
{
  // Check that the load in substitution and inheritance hashmaps
  // is not too high.
  //
#ifndef NDEBUG
  float load = (float) xml_schema::parser_smap_elements ();
  load /= xml_schema::parser_smap_buckets ();

  if (load > 0.8)
  {
    cerr << "substitution hashmap load is " << load << endl;
    cerr << "time to increase XSDE_PARSER_SMAP_BUCKETS" << endl;
  }

#ifdef XSDE_PARSER_VALIDATION
  load = (float) xml_schema::parser_imap_elements ();
  load /= xml_schema::parser_imap_buckets ();

  if (load > 0.8)
  {
    cerr << "inheritance hashmap load is " << load << endl;
    cerr << "time to increase XSDE_PARSER_IMAP_BUCKETS" << endl;
  }
#endif
#endif

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
    xml_schema::boolean_pimpl boolean_p;
    xml_schema::unsigned_int_pimpl unsigned_int_p;

    person_pimpl person_p;
    superman_pimpl superman_p;
    batman_pimpl batman_p;

    person_p.parsers (string_p);
    superman_p.parsers (string_p, boolean_p);
    batman_p.parsers (string_p, boolean_p, unsigned_int_p);

    // Parse the XML document.
    //
    xml_schema::parser_map_impl person_map (5); // 5 hashtable buckets

    person_map.insert (person_p);
    person_map.insert (superman_p);
    person_map.insert (batman_p);

    document_pimpl doc_p (person_map);

    // pre() and post() will be called as part of the start_root_element()
    // and end_root_element() calls.
    //
    if (argc < 2)
      doc_p.parse (std::cin);
    else
      doc_p.parse (argv[1]);
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
}

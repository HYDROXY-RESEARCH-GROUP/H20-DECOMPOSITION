// file      : examples/cxx/hybrid/polyroot/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <memory>   // std::auto_ptr
#include <iostream>

#include "supermen.hxx"
#include "supermen-pimpl.hxx"
#include "supermen-simpl.hxx"

using namespace std;
using xml_schema::ro_string;

// Customize the xml_schema::document object to handle a polymorphic
// root element. For more information see the polyroot and multiroot
// examples in the examples/cxx/parser/ directory.
//
class document_pimpl: public xml_schema::document_pimpl
{
public:
  // Passing the root element name to xml_schema::document_pimpl
  // constructor indicates that we are doing polymorphic parsing.
  // The root element name is used to automatically translate
  // substitutions to type information.
  //
  document_pimpl (person_paggr& paggr)
      : xml_schema::document_pimpl (person_paggr::root_name ()),
        paggr_ (paggr),
        parser_used_ (0)
  {
  }

  person*
  result ()
  {
    return result_.release ();
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
    if (name != person_paggr::root_name () ||
        ns != person_paggr::root_namespace ())
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

    // Search for the parser. If type is 0 then there is no xsi:type and
    // static type should be used.
    //
    if (type == 0)
      parser_used_ = &paggr_.root_parser ();
    else
    {
      // The map returns a generic parser_base which we will cast to
      // person_pskel in order to call the pre() and post_person()
      // callbacks. If the runtime and the generated code are built
      // with the mixin parser reuse style then we have to use
      // dynamic_cast because of the virtual inheritance.
      //
      xml_schema::parser_base* p = paggr_.root_map ().find (type);

#ifdef XSDE_REUSE_STYLE_MIXIN
      parser_used_ = dynamic_cast<person_pskel*> (p);
#else
      parser_used_ = static_cast<person_pskel*> (p);
#endif
    }

    if (parser_used_ != 0)
      parser_used_->pre ();

    return parser_used_;
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
    if (parser_used_ != 0)
      result_.reset (parser_used_->post_person ());
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

    if (parser_used_ != 0)
      parser_used_->_reset ();
  }

private:
  person_paggr& paggr_;
  person_pskel* parser_used_;
  std::auto_ptr<person> result_;
};

void
check_load (); // Defined after main().

int
main (int argc, char* argv[])
{
  // Check that the load in substitution and inheritance hashmaps
  // is not too high.
  //
#ifndef NDEBUG
  check_load ();
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
    // Parse.
    //
    person_paggr person_p;

    // Use our customized document parser. It automatically calls
    // pre() and post() on the chosen parser and stores the result.
    //
    document_pimpl doc_p (person_p);

    if (argc < 2)
      doc_p.parse (cin);
    else
      doc_p.parse (argv[1]);

    auto_ptr<person> p (doc_p.result ());

    // Print what we've got. You can use the standard C++ RTTI or custom
    // type information provided by the object model (--generate-typeinfo
    // option) to detect the object's actual (dynamic) type.
    //
    if (p->_dynamic_type () == batman::_static_type ())
    {
      batman& b = static_cast<batman&> (*p);
      cerr << b.name () << ", batman, wing span " << b.wing_span () << endl;
    }
    else if (superman* s = dynamic_cast<superman*> (p.get ()))
    {
      cerr << s->name () << ", ";

      if (s->can_fly ())
        cerr << "flying ";

      cerr << "superman" << endl;
    }
    else
    {
      cerr << p->name () << ", ordinary person" << endl;
    }

    // Serialize.
    //
    person_saggr person_s;
    person_sskel* ps = 0;

    // Determine the root element serializer to use based on the object's
    // dynamic type.
    //
    const string& dt = p->_dynamic_type ();

    if (dt == person::_static_type ())
      ps = &person_s.root_serializer ();
    else
    {
      // The map returns a generic serializer_base which we will cast to
      // person_sskel in order to call the pre() and post() callbacks. If
      // the runtime and the generated code are built with the mixin
      // serializer reuse style then we have to use dynamic_cast because
      // of the virtual inheritance.
      //
      xml_schema::serializer_base* s =
        person_s.root_map ().find (dt.c_str ());

#ifdef XSDE_REUSE_STYLE_MIXIN
      ps = dynamic_cast<person_sskel*> (s);
#else
      ps = static_cast<person_sskel*> (s);
#endif
    }

    // Create a document serializer for this object. Note that we pass
    // true as the third argument to indicate polymorphic serialization
    // as well as the root element's static type as the last argument
    // which is necessary if the actual root type can differ from its
    // static type.
    //
    xml_schema::document_simpl doc_s (
      *ps, person_s.root_name (), true, person_sskel::_static_type ());

    doc_s.add_no_namespace_schema ("supermen.xsd");

    ps->pre (*p);
    doc_s.serialize (std::cout, xml_schema::document_simpl::pretty_print);
    ps->post ();
  }
  catch (const xml_schema::parser_exception& e)
  {
    cerr << input << ":" << e.line () << ":" << e.column () << ": "
         << e.text () << endl;
    return 1;
  }
  catch (const xml_schema::serializer_exception& e)
  {
    cerr << "error: " << e.text () << endl;
    return 1;
  }
  catch (const std::ios_base::failure&)
  {
    cerr << input << ": unable to open or read/write failure" << endl;
    return 1;
  }

  return 0;
}

#ifndef NDEBUG
// Check that the load in substitution and inheritance hashmaps is not
// too high. See the C++/Parser and C++/Serializer Mappings Getting
// Started Guides for details.
//
void
check_load ()
{
  // Parser.
  //
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

  // Serializer.
  //
  load = (float) xml_schema::serializer_smap_elements ();
  load /= xml_schema::serializer_smap_buckets ();

  if (load > 0.8)
  {
    cerr << "substitution hashmap load is " << load << endl;
    cerr << "time to increase XSDE_SERIALIZER_SMAP_BUCKETS" << endl;
  }

  load = (float) xml_schema::serializer_smap_bucket_elements ();
  load /= xml_schema::serializer_smap_bucket_buckets ();

  if (load > 0.8)
  {
    cerr << "substitution inner hashmap load is " << load << endl;
    cerr << "time to increase XSDE_SERIALIZER_SMAP_BUCKET_BUCKETS" << endl;
  }

#ifdef XSDE_SERIALIZER_VALIDATION
  load = (float) xml_schema::serializer_imap_elements ();
  load /= xml_schema::serializer_imap_buckets ();

  if (load > 0.8)
  {
    cerr << "inheritance hashmap load is " << load << endl;
    cerr << "time to increase XSDE_SERIALIZER_IMAP_BUCKETS" << endl;
  }
#endif
}
#endif

// file      : examples/cxx/hybrid/evolution/passthrough/unknown-type-pimpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef UNKNOWN_TYPE_PIMPL_HXX
#define UNKNOWN_TYPE_PIMPL_HXX

namespace transform
{
  // Customized unknown_type parser implementation.
  //
  class unknown_type_pimpl: public unknown_type_base_pimpl
  {
  public:
    virtual void
    _pre ();

    // Wildcard content callbacks. All the unknown content is routed
    // to these functions. We use them to construct the raw XML
    // representation of the unknown transformation.
    //
    virtual void
    _start_any_element (const xml_schema::ro_string& ns,
                        const xml_schema::ro_string& name,
                        const char* type);

    virtual void
    _end_any_element (const xml_schema::ro_string& ns,
                      const xml_schema::ro_string& name);

    virtual void
    _any_attribute (const xml_schema::ro_string& ns,
                    const xml_schema::ro_string& name,
                    const xml_schema::ro_string& value);

    virtual void
    _any_characters (const xml_schema::ro_string&);

    // Low-level content callbacks. These are normally implemented by
    // the generated parsers. However, we need to intercept them and
    // re-route the known elements and attributes to the base parser
    // and the unknown content to the wildcard callbacks above.
    //
    virtual void
    _start_element (const xml_schema::ro_string& ns,
                        const xml_schema::ro_string& name,
                        const char* type);

    virtual void
    _end_element (const xml_schema::ro_string& ns,
                      const xml_schema::ro_string& name);

    virtual void
    _attribute (const xml_schema::ro_string& ns,
                    const xml_schema::ro_string& name,
                    const xml_schema::ro_string& value);

    virtual void
    _characters (const xml_schema::ro_string&);

  private:
    xml::element* cur_;
  };
}

#endif // UNKNOWN_TYPE_PIMPL_HXX

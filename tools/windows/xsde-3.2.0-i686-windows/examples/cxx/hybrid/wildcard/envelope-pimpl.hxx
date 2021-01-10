// file      : examples/cxx/hybrid/wildcard/envelope-pimpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef ENVELOPE_PIMPL_HXX
#define ENVELOPE_PIMPL_HXX

namespace email
{
  // Customized envelope parser implementation. All wildcard events are
  // routed to the _start_any_element, _end_any_element, _any_attribute,
  // and _any_characters functions. We can dynamically select a parser
  // from the _start_any_element after which all inner content will be
  // automatically routed to this parser. At the end we will get a call
  // to _end_any_element in which we can call post() and save the data.
  //
  class envelope_pimpl: public envelope_base_pimpl
  {
  public:
    envelope_pimpl ()
        : depth_ (0), text_p_ (0), binary_p_ (0)
    {
    }

    // Additional parsers for the wildcard content.
    //
    void
    text_parser (xml_schema::string_pskel& p)
    {
      text_p_ = &p;
    }

    void
    binary_parser (binary_pskel& p)
    {
      binary_p_ = &p;
    }

  public:
    virtual void
    _pre ();

    // If the XSD runtime library was configured with polymorphism
    // support, then _start_any_element has a third argument which
    // is a dynamic type id that comes from xsi:type or substitution
    // groups.
    //
#ifndef XSDE_POLYMORPHIC
    virtual void
    _start_any_element (const xml_schema::ro_string& ns,
                        const xml_schema::ro_string& name);
#else
    virtual void
    _start_any_element (const xml_schema::ro_string& ns,
                        const xml_schema::ro_string& name,
                        const char*);
#endif

    virtual void
    _end_any_element (const xml_schema::ro_string& ns,
                      const xml_schema::ro_string& name);

    // If we need to be able to reset and reuse the parser after
    // an error then we also need to override _reset() and reset
    // the parsers that are used to handle wildcards.
    //
    virtual void
    _reset ();

  private:
    std::size_t depth_;

    // Parsers for the text and binary elements.
    //
  private:
    xml_schema::string_pskel* text_p_;
    binary_pskel* binary_p_;
  };
}

#endif // ENVELOPE_PIMPL_HXX

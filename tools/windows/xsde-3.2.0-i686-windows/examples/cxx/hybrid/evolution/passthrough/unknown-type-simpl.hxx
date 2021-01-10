// file      : examples/cxx/hybrid/evolution/passthrough/unknown-type-simpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef UNKNOWN_TYPE_SIMPL_HXX
#define UNKNOWN_TYPE_SIMPL_HXX

namespace transform
{
  // Customized unknown_type serializer implementation.
  //
  class unknown_type_simpl: public unknown_type_base_simpl
  {
  public:
    // Low-level raw XML serialization callbacks.
    //
    virtual void
    _serialize_attributes ();

    virtual void
    _serialize_content ();

    // Helper functions.
    //
  private:
    void
    serialize (const xml::attributes&);

    void
    serialize (const xml::elements&);
  };
}

#endif // UNKNOWN_TYPE_SIMPL_HXX

// file      : examples/cxx/hybrid/filter/people-custom-simpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef PEOPLE_CUSTOM_SIMPL_HXX
#define PEOPLE_CUSTOM_SIMPL_HXX

// Customized people serializer implementation.
//
class people_simpl: public people_base_simpl
{
public:
  void
  gender_filter (gender);

  virtual bool
  person_next ();

private:
  gender gender_;
};

#endif // PEOPLE_CUSTOM_SIMPL_HXX

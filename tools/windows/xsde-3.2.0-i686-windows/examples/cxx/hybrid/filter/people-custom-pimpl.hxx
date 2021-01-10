// file      : examples/cxx/hybrid/filter/people-custom-pimpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef PEOPLE_CUSTOM_PIMPL_HXX
#define PEOPLE_CUSTOM_PIMPL_HXX

// Customized people parser implementation.
//
class people_pimpl: public people_base_pimpl
{
public:
  void
  age_filter (unsigned short min, unsigned short max);

  virtual void
  person (const ::person&);

private:
  unsigned short min_age_;
  unsigned short max_age_;
};

#endif // PEOPLE_CUSTOM_PIMPL_HXX

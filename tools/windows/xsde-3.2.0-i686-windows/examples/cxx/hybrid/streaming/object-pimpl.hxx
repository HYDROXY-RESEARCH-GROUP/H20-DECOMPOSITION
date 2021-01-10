// file      : examples/cxx/hybrid/streaming/object-pimpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef OBJECT_PIMPL_HXX
#define OBJECT_PIMPL_HXX

// Customized object parser implementation.
//
class object_pimpl: public object_pskel
{
public:
  virtual void
  pre ();

  virtual void
  id (unsigned int);

  virtual void
  position (const ::position&);

  virtual object*
  post_object ();

private:
  unsigned int id_;

  unsigned int count_;
  float avg_lat_;
  float avg_lon_;
};

#endif // OBJECT_PIMPL_HXX

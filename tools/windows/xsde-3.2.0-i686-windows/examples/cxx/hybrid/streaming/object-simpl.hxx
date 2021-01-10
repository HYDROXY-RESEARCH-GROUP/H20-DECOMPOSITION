// file      : examples/cxx/hybrid/streaming/object-simpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef OBJECT_SIMPL_HXX
#define OBJECT_SIMPL_HXX

// Customized object serializer implementation.
//
class object_simpl: public object_sskel
{
public:
  virtual void
  pre (const object&);

  virtual unsigned int
  id ();

  virtual bool
  position_next ();

  virtual const ::position&
  position ();

private:
  unsigned int id_;

  unsigned int count_;
  ::position cur_pos_;
};

#endif // OBJECT_SIMPL_HXX

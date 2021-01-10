// file      : examples/cxx/serializer/polymorphism/library-simpl-mixin.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef SUPERMEN_SIMPL_HXX
#define SUPERMEN_SIMPL_HXX

#include "supermen.hxx"
#include "supermen-sskel.hxx"

struct person_simpl: virtual person_sskel
{
  virtual void
  pre (const person&);

  virtual std::string
  name ();

protected:
  const person* person_;
};

struct superman_simpl: virtual superman_sskel, person_simpl
{
  virtual bool
  can_fly ();
};

struct batman_simpl: virtual batman_sskel, superman_simpl
{
  virtual unsigned int
  wing_span ();
};

struct supermen_simpl: virtual supermen_sskel
{
  virtual void
  pre (const supermen&);

  virtual bool
  person_next ();

  virtual const ::person&
  person ();

private:
  const supermen* supermen_;
  supermen::const_iterator i_;
};

#endif // SUPERMEN_SIMPL_HXX

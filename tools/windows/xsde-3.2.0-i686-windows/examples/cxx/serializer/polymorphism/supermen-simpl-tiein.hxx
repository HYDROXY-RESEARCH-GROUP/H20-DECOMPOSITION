// file      : examples/cxx/serializer/polymorphism/supermen-simpl-tiein.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef SUPERMEN_SIMPL_HXX
#define SUPERMEN_SIMPL_HXX

#include "supermen.hxx"
#include "supermen-sskel.hxx"

struct person_simpl: person_sskel
{
  virtual void
  pre (const person&);

  virtual std::string
  name ();

  // Derived serializers need access to this variable.
  //
public:
  const person* person_;
};

struct superman_simpl: superman_sskel
{
  superman_simpl ();

  virtual bool
  can_fly ();

  const superman&
  superman_ ();

private:
  person_simpl base_impl_;
};

struct batman_simpl: batman_sskel
{
  batman_simpl ();

  virtual unsigned int
  wing_span ();

  const batman&
  batman_ ();

private:
  superman_simpl base_impl_;
};

struct supermen_simpl: supermen_sskel
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

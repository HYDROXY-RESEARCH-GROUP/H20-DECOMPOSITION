// file      : examples/cxx/serializer/polymorphism/supermen.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef SUPERMEN_HXX
#define SUPERMEN_HXX

#include <string>
#include <vector>

// Custom type id. We could also use standard C++ typeid/type_info
// if it is available.
//
enum type_id
{
  person_type,
  superman_type,
  batman_type
};

//
//
struct person
{
  virtual
  ~person ()
  {
  }

  person (const std::string& name)
      : name_ (name)
  {
  }

  const std::string&
  name () const
  {
    return name_;
  }

  void
  name (const std::string& n)
  {
    name_ = n;
  }

  virtual type_id
  type () const
  {
    return person_type;
  }

private:
  std::string name_;
};

//
//
struct superman: person
{
  superman (const std::string& name, bool can_fly)
      : person (name), can_fly_ (can_fly)
  {
  }

  bool
  can_fly () const
  {
    return can_fly_;
  }

  void
  can_fly (bool cf)
  {
    can_fly_ = cf;
  }

  virtual type_id
  type () const
  {
    return superman_type;
  }

private:
  bool can_fly_;
};

struct batman: superman
{
  batman (const std::string& name, unsigned int wing_span)
      : superman (name, true), wing_span_ (wing_span)
  {
  }

  unsigned int
  wing_span () const
  {
    return wing_span_;
  }

  void
  wing_span (unsigned int ws)
  {
    wing_span_ = ws;
  }

  virtual type_id
  type () const
  {
    return batman_type;
  }

private:
  unsigned int wing_span_;
};

// Poor man's polymorphic sequence which also assumes ownership of the
// elements.
//
struct supermen: std::vector<person*>
{
  ~supermen ()
  {
    for (iterator i = begin (); i != end (); ++i)
      delete *i;
  }
};

#endif // SUPERMEN_HXX

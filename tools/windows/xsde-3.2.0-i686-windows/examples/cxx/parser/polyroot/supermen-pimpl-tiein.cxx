// file      : examples/cxx/parser/polyroot/supermen-pimpl-tiein.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain
//

#include <iostream>

#include "supermen-pimpl-tiein.hxx"

using std::cout;
using std::endl;

// person_pimpl
//
void person_pimpl::
pre ()
{
  cout << "starting to parse person" << endl;
}

void person_pimpl::
name (const std::string& v)
{
  cout << "name: " << v << endl;
}

void person_pimpl::
post_person ()
{
  cout << "finished parsing person" << endl;
}

// superman_pimpl
//
superman_pimpl::
superman_pimpl ()
    : superman_pskel (&base_impl_)
{
}

void superman_pimpl::
pre ()
{
  cout << "starting to parse superman" << endl;
}

void superman_pimpl::
can_fly (bool v)
{
  cout << "can-fly: " << v << endl;
}

void superman_pimpl::
post_person ()
{
  post_superman ();
}

void superman_pimpl::
post_superman ()
{
  cout << "finished parsing superman" << endl;
}

// batman_pimpl
//
batman_pimpl::
batman_pimpl ()
    : batman_pskel (&base_impl_)
{
}

void batman_pimpl::
pre ()
{
  cout << "starting to parse batman" << endl;
}

void batman_pimpl::
wing_span (unsigned int v)
{
  cout << "wing-span: " << v << endl;
}

void batman_pimpl::
post_person ()
{
  post_superman ();
}

void batman_pimpl::
post_superman ()
{
  post_batman ();
}

void batman_pimpl::
post_batman ()
{
  cout << "finished parsing batman" << endl;
}

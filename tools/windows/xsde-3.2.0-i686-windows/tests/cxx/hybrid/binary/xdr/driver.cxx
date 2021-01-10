// file      : tests/cxx/hybrid/binary/xdr/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test XDR insertion and extraction.
//

#include <stddef.h>  // size_t
#include <string.h>  // memcpy

#include <rpc/types.h>
#include <rpc/xdr.h>

#include <memory>
#include <iostream>

#include "test.hxx"
#include "test-pimpl.hxx"
#include "test-simpl.hxx"

using std::cerr;
using std::endl;

extern "C" int
overflow (char* p, char* buf, int n)
{
  xml_schema::buffer* dst (reinterpret_cast<xml_schema::buffer*> (p));

  size_t size (dst->size ());
  dst->size (size + n);
  memcpy (dst->data () + size, buf, n);

  return n;
}

struct underflow_info
{
  xml_schema::buffer* buf;
  std::size_t pos;
};

extern "C" int
underflow (char* p, char* buf, int n_)
{
  underflow_info* ui (reinterpret_cast<underflow_info*> (p));
  size_t n (static_cast<size_t> (n_));

  size_t size (ui->buf->size () - ui->pos);
  n = size > n ? n : size;

  memcpy (buf, ui->buf->data () + ui->pos, n);
  ui->pos += n;

  return n;
}

using namespace test;

int
main (int argc, char* argv[])
{
  /*
  try
  {
  */

  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " test.xml" << endl;
    return 1;
  }

  // Parse.
  //
  root_paggr root_p;

  xml_schema::document_pimpl doc_p (
    root_p.root_parser (),
    root_p.root_namespace (),
    root_p.root_name ());

  root_p.pre ();
  doc_p.parse (argv[1]);
  std::auto_ptr<type> r (root_p.post ());

  // Save to an XDR stream.
  //
  XDR xdr;
  xml_schema::buffer buf;
  xdrrec_create (&xdr, 0, 0, reinterpret_cast<char*> (&buf), 0, &overflow);
  xdr.x_op = XDR_ENCODE;
  xml_schema::oxdrstream oxdr (xdr);
  oxdr << *r;
  xdrrec_endofrecord (&xdr, true); // flush the data
  xdr_destroy (&xdr);

  // Load from an XDR stream.
  //
  underflow_info ui;
  ui.buf = &buf;
  ui.pos = 0;
  xdrrec_create (&xdr, 0, 0, reinterpret_cast<char*> (&ui), &underflow, 0);
  xdr.x_op = XDR_DECODE;
  xdrrec_skiprecord (&xdr);
  xml_schema::ixdrstream ixdr (xdr);
  std::auto_ptr<type> c (new type);
  ixdr >> *c;
  xdr_destroy (&xdr);

  // Serialize.
  //
  root_saggr root_s;

  xml_schema::document_simpl doc_s (
    root_s.root_serializer (),
    root_s.root_namespace (),
    root_s.root_name ());

  doc_s.add_prefix ("t", "test");

  root_s.pre (*c);
  doc_s.serialize (std::cout);
  root_s.post ();

  /*
  }
  catch (const xml_schema::xdr_exception&)
  {
    cerr << "XDR operation filed" << endl;
    return 1;
  }
  catch (const xml_schema::parser_exception& e)
  {
    cerr << argv[0] << ":" << e.line () << ":" << e.column () << ": "
         << e.text () << endl;
    return 1;
  }
  catch (const xml_schema::serializer_exception& e)
  {
    cerr << "error: " << e.text () << endl;
    return 1;
  }
  catch (const std::ios_base::failure&)
  {
    cerr << argv[0] << ": unable to open or read/write failure" << endl;
    return 1;
  }
  */
  
  return 0;
}

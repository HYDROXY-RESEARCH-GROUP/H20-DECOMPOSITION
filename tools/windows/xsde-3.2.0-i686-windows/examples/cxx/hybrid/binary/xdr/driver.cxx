// file      : examples/cxx/hybrid/binary/xdr/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <stddef.h>  // size_t
#include <string.h>  // memcpy

#include <rpc/types.h>
#include <rpc/xdr.h>

#include <memory>    // std::auto_ptr
#include <iostream>

#include "library.hxx"
#include "library-pimpl.hxx"
#include "library-simpl.hxx"

using std::cerr;
using std::endl;

// XDR output functions. Their implementations are provided after main().
//
struct underflow_info
{
  xml_schema::buffer* buf;
  size_t pos;
};

extern "C" int
overflow (void* user_data, char* buf, int n);

extern "C" int
underflow (void* user_data, char* buf, int n);

// The xdrrec_create function (used below) has slightly different
// prototypes on different platforms. To make this example portable
// we will need to cast the actual function to the following common
// prototype.
//
extern "C"
typedef  void (*xdrrec_create_p) (
  XDR*,
  unsigned int write_size,
  unsigned int read_size,
  void* user_data,
  int (*read) (void* user_data, char* buf, int n),
  int (*write) (void* user_data, char* buf, int n));

int
main (int argc, char* argv[])
{
  const char* input;

  if (argc < 2)
  {
    input = "STDIN";
    cerr << "XML file not specified, reading from STDIN" << endl;
  }
  else
    input = argv[1];

  try
  {
    using namespace library;

    // Parse.
    //
    catalog_paggr catalog_p;

    xml_schema::document_pimpl doc_p (
      catalog_p.root_parser (),
      catalog_p.root_namespace (),
      catalog_p.root_name ());

    catalog_p.pre ();

    if (argc < 2)
      doc_p.parse (std::cin);
    else
      doc_p.parse (argv[1]);

    std::auto_ptr<catalog> c (catalog_p.post ());

    // Save the object model to an XDR stream.
    //
    xdrrec_create_p xdrrec_create_ =
      reinterpret_cast<xdrrec_create_p> (::xdrrec_create);

    XDR xdr;
    xml_schema::buffer buf;

    xdrrec_create_ (&xdr, 0, 0, reinterpret_cast<char*> (&buf), 0, &overflow);
    xdr.x_op = XDR_ENCODE;
    xml_schema::oxdrstream oxdr (xdr);

    oxdr << *c;

    xdrrec_endofrecord (&xdr, true); // Flush the data.
    xdr_destroy (&xdr);

    // The binary representation is now in the memory buffer 'buf'.
    // To get to the raw data use buf.data() and buf.size().
    //
    cerr << "binary representation size: " << buf.size () << endl
         << endl;

    // Load the object model from an XDR stream.
    //
    underflow_info ui;
    ui.buf = &buf;
    ui.pos = 0;

    xdrrec_create_ (&xdr, 0, 0, reinterpret_cast<char*> (&ui), &underflow, 0);
    xdr.x_op = XDR_DECODE;
    xdrrec_skiprecord (&xdr);
    xml_schema::ixdrstream ixdr (xdr);

    std::auto_ptr<catalog> copy (new catalog);
    ixdr >> *copy;

    xdr_destroy (&xdr);

    // Serialize the copy back to XML.
    //
    catalog_saggr catalog_s;

    xml_schema::document_simpl doc_s (
      catalog_s.root_serializer (),
      catalog_s.root_namespace (),
      catalog_s.root_name ());

    doc_s.add_prefix ("lib", "http://www.codesynthesis.com/library");
    doc_s.add_schema ("http://www.codesynthesis.com/library", "library.xsd");

    catalog_s.pre (*copy);
    doc_s.serialize (std::cout, xml_schema::document_simpl::pretty_print);
    catalog_s.post ();
  }
  catch (const xml_schema::xdr_exception&)
  {
    cerr << "XDR operation failed" << endl;
    return 1;
  }
  catch (const xml_schema::parser_exception& e)
  {
    cerr << input << ":" << e.line () << ":" << e.column () << ": "
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
    cerr << input << ": unable to open or read/write failure" << endl;
    return 1;
  }

  return 0;
}

extern "C" int
overflow (void* p, char* buf, int n_)
{
  xml_schema::buffer* dst (reinterpret_cast<xml_schema::buffer*> (p));
  size_t n (static_cast<size_t> (n_));

  size_t size (dst->size ());
  size_t capacity (dst->capacity ());

  // Implement exponential growth.
  //
  if (size + n > capacity && size + n < capacity * 2)
    dst->capacity (capacity * 2);

  dst->size (size + n);
  memcpy (dst->data () + size, buf, n);

  return n;
}

extern "C" int
underflow (void* p, char* buf, int n_)
{
  underflow_info* ui (reinterpret_cast<underflow_info*> (p));
  size_t n (static_cast<size_t> (n_));

  size_t size (ui->buf->size () - ui->pos);
  n = size > n ? n : size;

  memcpy (buf, ui->buf->data () + ui->pos, n);
  ui->pos += n;

  return n;
}

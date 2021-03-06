This example shows how to handle the xsi:type attributes and substitution
groups when they are used on root elements. For general coverage of XML
Schema polymorphism handling in the Embedded C++/Serializer mapping see
the polymorphism example.

The example consists of the following files:

supermen.xsd
  XML Schema which describes supermen instance documents.

supermen.hxx
  Types that describe the supermen object model in C++. These
  are hand-written.

supermen.map
  Type map. It maps XML Schema types defined in supermen.xsd to
  C++ types defined in supermen.hxx.

supermen-sskel.hxx
supermen-sskel.cxx
  Serializer skeletons generated by XSD/e from supermen.xsd and
  supermen.map.

supermen-simpl-mixin.hxx
supermen-simpl-mixin.cxx

supermen-simpl-tiein.hxx
supermen-simpl-tiein.cxx
  Serializer implementations (using either mixin or tiein parser
  reuse style) that serialize the custom in-memory object model to
  XML. These are hand-written implementations of the serializer
  skeletons defined in supermen-sskel.hxx.

driver.cxx
  Driver for the example. It first constructs a sample object model
  using the types from supermen.hxx. It then creates a serializer
  instance using all the individual serializers found in one of
  supermen-simpl-*.hxx. Finally, it iterates over the object model
  and based on the type of the item being serialized, it creates
  the corresponding document serializer that is then invoked to
  serialize the object model item to an XML document which is
  printed to STDOUT.

To run the example simply execute:

$ ./driver

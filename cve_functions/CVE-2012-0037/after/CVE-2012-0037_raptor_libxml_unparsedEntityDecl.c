raptor_libxml_unparsedEntityDecl(void* user_data, const xmlChar *name,
                                 const xmlChar *publicId, const xmlChar *systemId,
                                 const xmlChar *notationName) {
  raptor_sax2* sax2 = (raptor_sax2*)user_data;
  libxml2_unparsedEntityDecl(sax2->xc, name, publicId, systemId, notationName);
}

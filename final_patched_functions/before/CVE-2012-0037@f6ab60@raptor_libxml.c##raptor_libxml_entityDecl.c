raptor_libxml_entityDecl(void* user_data, const xmlChar *name, int type,
                         const xmlChar *publicId, const xmlChar *systemId, 
                         xmlChar *content) {
  raptor_sax2* sax2 = (raptor_sax2*)user_data;
  libxml2_entityDecl(sax2->xc, name, type, publicId, systemId, content);
}

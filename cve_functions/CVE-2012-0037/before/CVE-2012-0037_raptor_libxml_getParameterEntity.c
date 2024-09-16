raptor_libxml_getParameterEntity(void* user_data, const xmlChar *name) {
  raptor_sax2* sax2 = (raptor_sax2*)user_data;
  return libxml2_getParameterEntity(sax2->xc, name);
}

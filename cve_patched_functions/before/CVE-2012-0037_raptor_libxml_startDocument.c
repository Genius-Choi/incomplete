raptor_libxml_startDocument(void* user_data) {
  raptor_sax2* sax2 = (raptor_sax2*)user_data;
  libxml2_startDocument(sax2->xc);
}

raptor_libxml_endDocument(void* user_data) {
  raptor_sax2* sax2 = (raptor_sax2*)user_data;
  xmlParserCtxtPtr xc = sax2->xc;

  libxml2_endDocument(sax2->xc);

  if(xc->myDoc) {
    xmlFreeDoc(xc->myDoc);
    xc->myDoc = NULL;
  }
}

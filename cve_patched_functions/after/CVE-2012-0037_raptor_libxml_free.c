raptor_libxml_free(xmlParserCtxtPtr xc) {
  libxml2_endDocument(xc);

  if(xc->myDoc) {
    xmlFreeDoc(xc->myDoc);
    xc->myDoc = NULL;
  }

  xmlFreeParserCtxt(xc);
}

raptor_libxml_set_document_locator(void* user_data, xmlSAXLocatorPtr loc)
{
  raptor_sax2* sax2 = (raptor_sax2*)user_data;
  sax2->loc = loc;
}

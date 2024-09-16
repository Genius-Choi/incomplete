raptor_libxml_isStandalone (void* user_data) 
{
  raptor_sax2* sax2 = (raptor_sax2*)user_data;
  return libxml2_isStandalone(sax2->xc);
}

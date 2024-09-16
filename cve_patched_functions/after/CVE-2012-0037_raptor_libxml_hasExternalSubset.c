raptor_libxml_hasExternalSubset (void* user_data) 
{
  raptor_sax2* sax2 = (raptor_sax2*)user_data;
  return libxml2_hasExternalSubset(sax2->xc);
}

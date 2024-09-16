raptor_rdfxml_check_propertyAttribute_name(const char *name) 
{
  int i;

  if(*name == '_')
    return 1;
  
  for(i = 0; raptor_rdf_ns_terms_info[i].name; i++)
    if(!strcmp(raptor_rdf_ns_terms_info[i].name, (const char*)name))
      return raptor_rdf_ns_terms_info[i].allowed_as_propertyAttribute;

  return -1;
}

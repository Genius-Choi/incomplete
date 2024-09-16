raptor_rdfxml_element_content_type_as_string(raptor_rdfxml_element_content_type type) 
{
  if(type > RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_LAST)
    return "INVALID";
  return rdf_content_type_info[type].name;
}

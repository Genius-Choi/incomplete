static void raptor_rdfa_start_element(void *user_data,
                                      raptor_xml_element *xml_element)
{
  raptor_qname* qname=raptor_xml_element_get_name(xml_element);
  int attr_count=raptor_xml_element_get_attributes_count(xml_element);
  raptor_qname** attrs=raptor_xml_element_get_attributes(xml_element);
  unsigned char* qname_string=raptor_qname_to_counted_name(qname, NULL);
  char** attr=NULL;
  int i;

  if(attr_count > 0) {
    attr=(char**)malloc(sizeof(char*) * (1+(attr_count*2)));
    for(i=0; i<attr_count; i++) {
      attr[2*i]=(char*)raptor_qname_to_counted_name(attrs[i], NULL);
      attr[1+(2*i)]=(char*)raptor_qname_get_value(attrs[i]);
    }
    attr[2*i]=NULL;
  }
  start_element(user_data, (char*)qname_string, (const char**)attr);
  raptor_free_memory(qname_string);
  if(attr) {
    for(i=0; i<attr_count; i++)
      raptor_free_memory(attr[2*i]);
    free(attr);
  }
}

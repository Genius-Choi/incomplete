static void raptor_rdfa_end_element(void *user_data,
                                    raptor_xml_element* xml_element)
{
  raptor_qname* qname=raptor_xml_element_get_name(xml_element);
  unsigned char* qname_string=raptor_qname_to_counted_name(qname, NULL);

  end_element(user_data, (const char*)qname_string);
  raptor_free_memory(qname_string);
}

raptor_rss_cdata_handler(void *user_data, raptor_xml_element* xml_element,
                         const unsigned char *s, int len)
{      
  raptor_rss_element* rss_element;

  rss_element = (raptor_rss_element*)xml_element->user_data;

  if(rss_element->xml_writer) {
    raptor_xml_writer_cdata_counted(rss_element->xml_writer, s, len);
    return;
  }

  raptor_stringbuffer_append_counted_string(rss_element->sb, s, len, 1);
}      

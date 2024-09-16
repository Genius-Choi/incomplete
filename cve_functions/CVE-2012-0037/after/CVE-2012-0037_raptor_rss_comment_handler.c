raptor_rss_comment_handler(void *user_data, raptor_xml_element* xml_element,
                           const unsigned char *s)
{
  raptor_rss_element* rss_element;

  if(!xml_element)
    return;
  
  rss_element = (raptor_rss_element*)xml_element->user_data;

  if(rss_element->xml_writer) {
    raptor_xml_writer_comment(rss_element->xml_writer, s);
    return;
  }
}

raptor_free_rss_element(raptor_rss_element *rss_element)
{
  if(rss_element->uri)
    raptor_free_uri(rss_element->uri);
  if(rss_element->type == RAPTOR_RSS_CONTENT_TYPE_XML) {
    if(rss_element->xml_writer)
      raptor_free_xml_writer(rss_element->xml_writer);
    if(rss_element->iostream)
      raptor_free_iostream(rss_element->iostream);
    if(rss_element->xml_content)
      raptor_free_memory(rss_element->xml_content);
  }
  if(rss_element->sb)
    raptor_free_stringbuffer(rss_element->sb);

  RAPTOR_FREE(raptor_rss_element, rss_element);
}

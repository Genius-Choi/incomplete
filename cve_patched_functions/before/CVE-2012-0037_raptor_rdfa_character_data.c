static void raptor_rdfa_character_data(void *user_data,
                                       raptor_xml_element* xml_element,
                                       const unsigned char *s, int len)
{
  character_data(user_data, (const char *)s, len);
}

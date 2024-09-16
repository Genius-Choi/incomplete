raptor_libxml_error(void* user_data, const char *msg, ...) 
{
  va_list args;

  va_start(args, msg);
  raptor_libxml_error_common(user_data, msg, args, xml_error_prefix, 0);
  va_end(args);
}

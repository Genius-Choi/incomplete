raptor_libxml_fatal_error(void* user_data, const char *msg, ...) 
{
  va_list args;

  va_start(args, msg);
  raptor_libxml_error_common(user_data, msg, args, xml_fatal_error_prefix, 1);
  va_end(args);
}

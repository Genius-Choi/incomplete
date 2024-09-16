static void eexec_string(const char *string)
{
  while (*string)
    eexec_byte(*string++);
}

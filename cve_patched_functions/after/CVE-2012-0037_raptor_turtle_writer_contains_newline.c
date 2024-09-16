raptor_turtle_writer_contains_newline(const unsigned char *s)
{
  size_t i = 0;

  for( ; i < strlen((char*)s); i++)
    if(s[i] == '\n')
      return 1;

  return 0;
}

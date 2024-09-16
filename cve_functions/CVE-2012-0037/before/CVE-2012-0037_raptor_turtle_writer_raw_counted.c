raptor_turtle_writer_raw_counted(raptor_turtle_writer* turtle_writer,
                                 const unsigned char *s, unsigned int len)
{
  raptor_iostream_counted_string_write(s, len, turtle_writer->iostr);
}

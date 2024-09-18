raptor_turtle_writer_raw(raptor_turtle_writer* turtle_writer,
                         const unsigned char *s)
{
  raptor_iostream_string_write(s, turtle_writer->iostr);
}

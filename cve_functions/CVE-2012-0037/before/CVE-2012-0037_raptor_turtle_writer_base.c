raptor_turtle_writer_base(raptor_turtle_writer* turtle_writer,
                          raptor_uri* base_uri)
{
  if(base_uri) {
    raptor_iostream_counted_string_write("@base ", 6, turtle_writer->iostr);
    raptor_turtle_writer_reference(turtle_writer, base_uri);
    raptor_iostream_counted_string_write(" .\n", 3, turtle_writer->iostr);
  }
}

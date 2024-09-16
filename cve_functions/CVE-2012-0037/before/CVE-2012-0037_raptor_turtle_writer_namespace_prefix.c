raptor_turtle_writer_namespace_prefix(raptor_turtle_writer* turtle_writer,
                                      raptor_namespace* ns)
{
  raptor_iostream_string_write("@prefix ", turtle_writer->iostr);
  if(ns->prefix)
    raptor_iostream_string_write(raptor_namespace_get_prefix(ns),
                                 turtle_writer->iostr);
  raptor_iostream_counted_string_write(": ", 2, turtle_writer->iostr);
  raptor_turtle_writer_reference(turtle_writer, raptor_namespace_get_uri(ns));
  raptor_iostream_counted_string_write(" .\n", 3, turtle_writer->iostr);
}

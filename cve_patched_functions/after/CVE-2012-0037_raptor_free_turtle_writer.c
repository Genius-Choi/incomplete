raptor_free_turtle_writer(raptor_turtle_writer* turtle_writer)
{
  if(!turtle_writer)
    return;

  if(turtle_writer->nstack && turtle_writer->my_nstack)
    raptor_free_namespaces(turtle_writer->nstack);

  if(turtle_writer->xsd_boolean_uri)
    raptor_free_uri(turtle_writer->xsd_boolean_uri);
  if(turtle_writer->xsd_decimal_uri)
    raptor_free_uri(turtle_writer->xsd_decimal_uri);
  if(turtle_writer->xsd_double_uri)
    raptor_free_uri(turtle_writer->xsd_double_uri);
  if(turtle_writer->xsd_integer_uri)
    raptor_free_uri(turtle_writer->xsd_integer_uri);

  RAPTOR_FREE(raptor_turtle_writer, turtle_writer);
}

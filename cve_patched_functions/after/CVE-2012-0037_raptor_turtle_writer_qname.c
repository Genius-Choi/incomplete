raptor_turtle_writer_qname(raptor_turtle_writer* turtle_writer,
                           raptor_qname* qname)
{
  raptor_iostream* iostr = turtle_writer->iostr;
  
  if(qname->nspace && qname->nspace->prefix_length > 0)
    raptor_iostream_counted_string_write(qname->nspace->prefix,
                                         qname->nspace->prefix_length,
                                         iostr);
  raptor_iostream_write_byte(':', iostr);
  
  raptor_iostream_counted_string_write(qname->local_name,
                                       qname->local_name_length,
                                       iostr);
  return;
}

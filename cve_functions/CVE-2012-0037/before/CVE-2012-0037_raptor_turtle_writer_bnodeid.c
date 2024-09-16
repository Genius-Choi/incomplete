raptor_turtle_writer_bnodeid(raptor_turtle_writer* turtle_writer,
                             const unsigned char *bnodeid, size_t len)
{
  raptor_bnodeid_ntriples_write(bnodeid, len,
                                turtle_writer->iostr);
}

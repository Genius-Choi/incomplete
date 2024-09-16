int rdfa_parse_buffer(rdfacontext* context, size_t bytes)
{
   int rval;
   int done;
   done = (bytes == 0);
   rval = rdfa_parse_chunk(context, context->working_buffer, bytes, done);
   context->done = done;
   return rval;
}

char* rdfa_get_buffer(rdfacontext* context, size_t* blen)
{
   *blen = context->wb_allocated;
   return context->working_buffer;
}

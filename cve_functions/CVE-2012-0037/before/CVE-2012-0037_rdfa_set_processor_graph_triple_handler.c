void rdfa_set_processor_graph_triple_handler(
   rdfacontext* context, triple_handler_fp th)
{
   context->processor_graph_triple_callback = th;
}

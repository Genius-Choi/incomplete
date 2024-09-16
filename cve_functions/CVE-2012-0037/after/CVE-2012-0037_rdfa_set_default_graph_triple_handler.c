void rdfa_set_default_graph_triple_handler(
   rdfacontext* context, triple_handler_fp th)
{
   context->default_graph_triple_callback = th;
}

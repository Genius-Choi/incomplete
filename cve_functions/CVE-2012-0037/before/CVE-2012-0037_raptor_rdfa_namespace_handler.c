static void raptor_rdfa_namespace_handler(void *user_data,
                                          raptor_namespace* nspace)
{
  rdfalist* context_stack = (rdfalist*)user_data;
  rdfacontext* context = (rdfacontext*)
    context_stack->items[context_stack->num_items - 1]->data;

  if(context->namespace_handler)
    (*context->namespace_handler)(context->namespace_handler_user_data,
                                  nspace);
}

raptor_libxml_finish(raptor_world* world)
{
  if(world->libxml_flags & RAPTOR_WORLD_FLAG_LIBXML_STRUCTURED_ERROR_SAVE)
    xmlSetStructuredErrorFunc(world->libxml_saved_structured_error_context,
                              world->libxml_saved_structured_error_handler);

  if(world->libxml_flags & RAPTOR_WORLD_FLAG_LIBXML_GENERIC_ERROR_SAVE)
    xmlSetGenericErrorFunc(world->libxml_saved_generic_error_context,
                           world->libxml_saved_generic_error_handler);

  xmlCleanupParser();
}

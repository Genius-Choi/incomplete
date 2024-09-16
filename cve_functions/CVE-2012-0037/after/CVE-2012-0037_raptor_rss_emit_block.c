raptor_rss_emit_block(raptor_parser* rdf_parser,
                      raptor_term *resource,
                      raptor_rss_block *block)
{
  raptor_rss_parser* rss_parser = (raptor_rss_parser*)rdf_parser->context;
  raptor_rss_type block_type = block->rss_type;
  raptor_uri *predicate_uri;
  raptor_term *predicate_term = NULL;
  const raptor_rss_block_field_info *bfi;
  raptor_rss_fields_type predicate_field;

  if(!block->identifier) {
    raptor_parser_error(rdf_parser, "Block has no identifier");
    return 1;
  }

  predicate_field = raptor_rss_items_info[block_type].predicate;
  predicate_uri = rdf_parser->world->rss_fields_info_uris[predicate_field];
  predicate_term = raptor_new_term_from_uri(rdf_parser->world,
                                            predicate_uri);

  rss_parser->statement.subject = resource;
  rss_parser->statement.predicate = predicate_term;
  rss_parser->statement.object = block->identifier;
  (*rdf_parser->statement_handler)(rdf_parser->user_data,
                                   &rss_parser->statement);

  raptor_free_term(predicate_term); predicate_term = NULL;

  if(raptor_rss_emit_type_triple(rdf_parser, block->identifier,
                                 block->node_type))
    return 1;


  for(bfi = &raptor_rss_block_fields_info[0];
      bfi->type != RAPTOR_RSS_NONE;
      bfi++) {
    int attribute_type;
    int offset;
    
    if(bfi->type != block_type || !bfi->attribute)
      continue;

    attribute_type = bfi->attribute_type;
    offset = bfi->offset;
    predicate_uri = rdf_parser->world->rss_fields_info_uris[bfi->field];

    predicate_term = raptor_new_term_from_uri(rdf_parser->world,
                                              predicate_uri);
    rss_parser->statement.predicate = predicate_term;

    if(attribute_type == RSS_BLOCK_FIELD_TYPE_URL) {
      raptor_uri *uri = block->urls[offset];
      if(uri) {
        raptor_term* object_term;
        
        object_term = raptor_new_term_from_uri(rdf_parser->world, uri);
        rss_parser->statement.object = object_term;
        (*rdf_parser->statement_handler)(rdf_parser->user_data,
                                         &rss_parser->statement);
        raptor_free_term(object_term);
      }
    } else if(attribute_type == RSS_BLOCK_FIELD_TYPE_STRING) {
      const char *str = block->strings[offset];
      if(str) {
        raptor_term* object_term;
        
        object_term = raptor_new_term_from_literal(rdf_parser->world,
                                                   (const unsigned char*)str,
                                                   NULL, NULL);
        rss_parser->statement.object = object_term;
        (*rdf_parser->statement_handler)(rdf_parser->user_data,
                                         &rss_parser->statement);
        raptor_free_term(object_term);
      }
    } else {
#ifdef RAPTOR_DEBUG
      RAPTOR_FATAL2("Found unknown attribute_type %d\n", attribute_type);
#endif
    }

    raptor_free_term(predicate_term); predicate_term = NULL;
  }

  return 0;
}

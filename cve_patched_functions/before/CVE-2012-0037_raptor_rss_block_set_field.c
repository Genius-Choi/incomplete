raptor_rss_block_set_field(raptor_world *world, raptor_uri *base_uri,
                           raptor_rss_block *block,
                           const raptor_rss_block_field_info *bfi,
                           const char *string)
{
  int attribute_type = bfi->attribute_type;
  int offset = bfi->offset;
  if(attribute_type == RSS_BLOCK_FIELD_TYPE_URL) {
    raptor_uri* uri;
    uri = raptor_new_uri_relative_to_base(world, base_uri,
                                             (const unsigned char*)string);
    if(!uri)
      return 1;
    
    block->urls[offset] = uri;
  } else if(attribute_type == RSS_BLOCK_FIELD_TYPE_STRING) {
    size_t len = strlen(string);
    block->strings[offset] = RAPTOR_MALLOC(char*, len + 1);
    if(!block->strings[offset])
      return 1;

    memcpy(block->strings[offset], string, len+1);
  } else {
#ifdef RAPTOR_DEBUG
    RAPTOR_FATAL2("Found unknown attribute_type %d\n", attribute_type);
#endif
    return 1;
  }

  return 0;
}

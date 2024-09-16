raptor_rss_get_current_item(raptor_rss_parser *rss_parser)
{
  raptor_rss_item* item;
  
  if(rss_parser->current_type == RAPTOR_RSS_ITEM)
    item = rss_parser->model.last;
  else
    item = raptor_rss_model_get_common(&rss_parser->model,
                                       rss_parser->current_type);
  return item;
}

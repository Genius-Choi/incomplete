raptor_rss_uplift_items(raptor_parser* rdf_parser)
{
  raptor_rss_parser* rss_parser = (raptor_rss_parser*)rdf_parser->context;
  int i;
  raptor_rss_item* item;
  
  for(i = 0; i< RAPTOR_RSS_COMMON_SIZE; i++) {
    for(item = rss_parser->model.common[i]; item; item = item->next) {
      raptor_rss_uplift_fields(rss_parser, item);
    }
  }

  for(item = rss_parser->model.items; item; item = item->next) {
    raptor_rss_uplift_fields(rss_parser, item);
  }
  
}

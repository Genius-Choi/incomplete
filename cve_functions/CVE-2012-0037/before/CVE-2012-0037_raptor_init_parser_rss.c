raptor_init_parser_rss(raptor_world* world)
{
  return !raptor_world_register_parser_factory(world,
                                               &raptor_rss_parser_register_factory);
}

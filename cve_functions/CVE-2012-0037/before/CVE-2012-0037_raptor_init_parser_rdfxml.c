raptor_init_parser_rdfxml(raptor_world* world)
{
  return !raptor_world_register_parser_factory(world,
                                               &raptor_rdfxml_parser_register_factory);
}

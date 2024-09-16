raptor_world_get_option_description(raptor_world* world,
                                    const raptor_domain domain,
                                    const raptor_option option)
{
  raptor_option_area area;
  raptor_option_description *option_description = NULL;
  raptor_uri *base_uri = NULL;
  int i;

  RAPTOR_ASSERT_OBJECT_POINTER_RETURN_VALUE(world, raptor_world, NULL);

  raptor_world_open(world);
  
  area = raptor_option_get_option_area_for_domain(domain);
  if(area == RAPTOR_OPTION_AREA_NONE)
    return NULL;
  
  for(i = 0; i <= RAPTOR_OPTION_LAST; i++) {
    if(raptor_options_list[i].option == option &&
       (raptor_options_list[i].area & area))
      break;
  }

  if(i > RAPTOR_OPTION_LAST)
    return NULL;
  
  option_description = RAPTOR_CALLOC(raptor_option_description*, 1,
                                     sizeof(*option_description));
  if(!option_description)
    return NULL;

  option_description->domain = domain;
  option_description->option = option;
  option_description->value_type = raptor_options_list[i].value_type;
  option_description->name = raptor_options_list[i].name;
  option_description->name_len = strlen(option_description->name);
  option_description->label = raptor_options_list[i].label;

  base_uri = raptor_new_uri_from_counted_string(world,
                                                (const unsigned char*)raptor_option_uri_prefix,
                                                raptor_option_uri_prefix_len);
  if(!base_uri) {
    raptor_free_option_description(option_description);
    return NULL;
  }
  
  option_description->uri = raptor_new_uri_from_uri_local_name(world,
                                                               base_uri,
                                                               (const unsigned char*)raptor_options_list[i].name);
  raptor_free_uri(base_uri);
  if(!option_description->uri) {
    raptor_free_option_description(option_description);
    return NULL;
  }
  
  return option_description;
}

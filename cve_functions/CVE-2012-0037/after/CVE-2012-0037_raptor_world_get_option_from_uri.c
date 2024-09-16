raptor_world_get_option_from_uri(raptor_world* world, raptor_uri *uri)
{
  unsigned char *uri_string;
  int i;
  raptor_option option = (raptor_option)-1;
  
  if(!uri)
    return option;
  
  RAPTOR_ASSERT_OBJECT_POINTER_RETURN_VALUE(world, raptor_world, (raptor_option)-1);

  raptor_world_open(world);
  
  uri_string = raptor_uri_as_string(uri);
  if(strncmp((const char*)uri_string, raptor_option_uri_prefix,
             raptor_option_uri_prefix_len))
    return option;

  uri_string += raptor_option_uri_prefix_len;

  for(i = 0; i <= RAPTOR_OPTION_LAST; i++)
    if(!strcmp(raptor_options_list[i].name, (const char*)uri_string)) {
      option = (raptor_option)i;
      break;
    }

  return option;
}

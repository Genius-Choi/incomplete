static const char * raptor_rdfxml_state_as_string(raptor_state state) 
{
  if(state < 1 || state > RAPTOR_STATE_PARSETYPE_LAST)
    state = (raptor_state)0;
  return raptor_state_names[(int)state];
}

get_hostname_list ()
{
  if (hostname_list_initialized == 0)
    initialize_hostname_list ();
  return (hostname_list);
}

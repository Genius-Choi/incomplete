initialize_hostname_list ()
{
  char *temp;

  temp = get_string_value ("HOSTFILE");
  if (temp == 0)
    temp = get_string_value ("hostname_completion_file");
  if (temp == 0)
    temp = DEFAULT_HOSTS_FILE;

  snarf_hosts_from_file (temp);

  if (hostname_list)
    hostname_list_initialized++;
}

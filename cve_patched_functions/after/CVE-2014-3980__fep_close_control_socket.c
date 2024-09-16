_fep_close_control_socket (Fep *fep)
{
  if (fep->server >= 0)
    close (fep->server);
  remove_control_socket (fep->control_socket_path);
  free (fep->control_socket_path);
}

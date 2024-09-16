_fep_read_control_message_from_fd (Fep               *fep,
                                   int                fd,
                                   FepControlMessage *message)
{
  int i;

  if (_fep_read_control_message (fd, message) < 0)
    {
      for (i = 0; i < fep->n_clients; i++)
	if (fep->clients[i] == fd)
	  {
	    close (fd);
	    if (i + 1 < fep->n_clients)
	      memmove (&fep->clients[i],
		       &fep->clients[i + 1],
		       fep->n_clients - (i + 1));
	    fep->clients[--fep->n_clients] = -1;
	    break;
	  }
      return -1;
    }

  return 0;
}

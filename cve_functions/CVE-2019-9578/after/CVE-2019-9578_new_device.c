new_device (u2fh_devs * devs)
{
  struct u2fdevice *new = malloc (sizeof (struct u2fdevice));
  if (new == NULL)
    {
      return NULL;
    }
  memset (new, 0, sizeof (struct u2fdevice));
  new->id = devs->max_id++;
  if (devs->first == NULL)
    {
      devs->first = new;
    }
  else
    {
      struct u2fdevice *dev;
      for (dev = devs->first; dev != NULL; dev = dev->next)
	{
	  if (dev->next == NULL)
	    {
	      break;
	    }
	}
      dev->next = new;
    }
  return new;
}

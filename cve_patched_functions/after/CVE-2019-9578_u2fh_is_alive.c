u2fh_is_alive (u2fh_devs * devs, unsigned index)
{
  if (!get_device (devs, index))
    return 0;
  return 1;
}

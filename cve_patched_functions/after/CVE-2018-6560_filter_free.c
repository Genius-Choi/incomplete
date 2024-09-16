filter_free (Filter *filter)
{
  g_free (filter->path);
  g_free (filter->interface);
  g_free (filter->member);
  g_free (filter);
}

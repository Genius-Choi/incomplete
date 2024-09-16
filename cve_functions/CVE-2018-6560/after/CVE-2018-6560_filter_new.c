filter_new (const char *rule)
{
  Filter *filter = g_new0 (Filter, 1);
  const char *obj_path_start = NULL;
  const char *method_end = NULL;

  obj_path_start = strchr (rule, '@');
  if (obj_path_start && obj_path_start[1] != 0)
    filter->path = g_strdup (obj_path_start + 1);

  if (obj_path_start != NULL)
    method_end = obj_path_start;
  else
    method_end = rule + strlen(rule);

  if (rule[0] != '@')
    {
      filter->interface = g_strndup (rule, method_end - rule);
      char *dot = strrchr (filter->interface, '.');
      if (dot != NULL)
        {
          *dot = 0;
          if (strcmp (dot+1, "*") != 0)
            filter->member = g_strdup (dot + 1);
         }
    }

  return filter;
}

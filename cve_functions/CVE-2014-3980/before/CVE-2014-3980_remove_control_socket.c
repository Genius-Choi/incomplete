remove_control_socket (const char *path)
{
  char *_path = xstrdup (path), *p;
  unlink (_path);
  p = strrchr (_path, '/');
  assert (p != NULL);
  *p = '\0';

  rmdir (_path);
  free (_path);
}

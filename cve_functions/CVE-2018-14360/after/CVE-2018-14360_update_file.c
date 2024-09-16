static int update_file(char *filename, char *buf)
{
  FILE *fp = NULL;
  char tmpfile[PATH_MAX];
  int rc = -1;

  while (true)
  {
    snprintf(tmpfile, sizeof(tmpfile), "%s.tmp", filename);
    fp = mutt_file_fopen(tmpfile, "w");
    if (!fp)
    {
      mutt_perror(tmpfile);
      *tmpfile = '\0';
      break;
    }
    if (fputs(buf, fp) == EOF)
    {
      mutt_perror(tmpfile);
      break;
    }
    if (mutt_file_fclose(&fp) == EOF)
    {
      mutt_perror(tmpfile);
      fp = NULL;
      break;
    }
    fp = NULL;
    if (rename(tmpfile, filename) < 0)
    {
      mutt_perror(filename);
      break;
    }
    *tmpfile = '\0';
    rc = 0;
    break;
  }
  if (fp)
    mutt_file_fclose(&fp);
  if (*tmpfile)
    unlink(tmpfile);
  return rc;
}

changes_compar(const struct dirent **d1, const struct dirent **d2)
{
    struct stat st1, st2;

    stat((*d1)->d_name, &st1);

    stat((*d2)->d_name, &st2);

    if (st1.st_mtime > st2.st_mtime)
      return 1;
    else
      return -1;
}

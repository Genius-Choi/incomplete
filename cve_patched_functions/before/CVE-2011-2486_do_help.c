static int do_help(const char *prog)
{
  printf("%s, NPAPI plugin viewer. Version %s\n", NPW_VIEWER, NPW_VERSION);
  printf("\n");
  printf("usage: %s [GTK flags] [flags]\n", prog);
  printf("   -h --help               print this message\n");
  printf("   -t --test               check plugin is compatible\n");
  printf("   -i --info               print plugin information\n");
  printf("   -p --plugin             set plugin path\n");
  printf("   -c --connection         set connection path\n");
  return 0;
}

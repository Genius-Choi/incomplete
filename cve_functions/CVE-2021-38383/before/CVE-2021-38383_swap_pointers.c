swap_pointers(char **a, char **b)
{
  char *t = *a;
  *a = *b;
  *b = t;
}

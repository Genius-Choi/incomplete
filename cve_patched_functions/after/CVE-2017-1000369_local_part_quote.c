local_part_quote(uschar *lpart)
{
BOOL needs_quote = FALSE;
int size, ptr;
uschar *yield;
uschar *t;

for (t = lpart; !needs_quote && *t != 0; t++)
  {
  needs_quote = !isalnum(*t) && strchr("!#$%&'*+-/=?^_`{|}~", *t) == NULL &&
    (*t != '.' || t == lpart || t[1] == 0);
  }

if (!needs_quote) return lpart;

size = ptr = 0;
yield = string_catn(NULL, &size, &ptr, US"\"", 1);

for (;;)
  {
  uschar *nq = US Ustrpbrk(lpart, "\\\"");
  if (nq == NULL)
    {
    yield = string_cat(yield, &size, &ptr, lpart);
    break;
    }
  yield = string_catn(yield, &size, &ptr, lpart, nq - lpart);
  yield = string_catn(yield, &size, &ptr, US"\\", 1);
  yield = string_catn(yield, &size, &ptr, nq, 1);
  lpart = nq + 1;
  }

yield = string_catn(yield, &size, &ptr, US"\"", 1);
yield[ptr] = 0;
return yield;
}

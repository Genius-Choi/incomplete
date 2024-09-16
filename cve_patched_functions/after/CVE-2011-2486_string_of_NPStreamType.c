const char *string_of_NPStreamType(int stype)
{
  const char *str;

  switch (stype) {
#define _(VAL) case VAL: str = #VAL; break;
    _(NP_NORMAL);
    _(NP_SEEK);
    _(NP_ASFILE);
    _(NP_ASFILEONLY);
#undef _
  default:
	str = "<unknown stream type>";
	break;
  }

  return str;
}

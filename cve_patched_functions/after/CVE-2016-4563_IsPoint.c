static inline MagickBooleanType IsPoint(const char *point)
{
  char
    *p;

  double
    value;

  value=StringToDouble(point,&p);
  return((value == 0.0) && (p == point) ? MagickFalse : MagickTrue);
}

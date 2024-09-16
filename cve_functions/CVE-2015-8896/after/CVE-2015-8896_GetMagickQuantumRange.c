MagickExport const char *GetMagickQuantumRange(size_t *range)
{
  if (range != (size_t *) NULL)
    *range=(size_t) QuantumRange;
  return(MagickQuantumRange);
}

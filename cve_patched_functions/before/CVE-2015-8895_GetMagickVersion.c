MagickExport const char *GetMagickVersion(size_t *version)
{
  if (version != (size_t *) NULL)
    *version=MagickLibVersion;
  return(MagickVersion);
}

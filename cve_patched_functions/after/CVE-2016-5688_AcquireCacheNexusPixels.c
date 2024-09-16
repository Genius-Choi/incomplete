static inline MagickBooleanType AcquireCacheNexusPixels(
  const CacheInfo *magick_restrict cache_info,NexusInfo *nexus_info,
  ExceptionInfo *exception)
{
  if (nexus_info->length != (MagickSizeType) ((size_t) nexus_info->length))
    return(MagickFalse);
  nexus_info->mapped=MagickFalse;
  nexus_info->cache=(Quantum *) MagickAssumeAligned(AcquireAlignedMemory(1,
    (size_t) nexus_info->length));
  if (nexus_info->cache == (Quantum *) NULL)
    {
      nexus_info->mapped=MagickTrue;
      nexus_info->cache=(Quantum *) MapBlob(-1,IOMode,0,(size_t)
        nexus_info->length);
    }
  if (nexus_info->cache == (Quantum *) NULL)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),
        ResourceLimitError,"MemoryAllocationFailed","`%s'",
        cache_info->filename);
      return(MagickFalse);
    }
  return(MagickTrue);
}

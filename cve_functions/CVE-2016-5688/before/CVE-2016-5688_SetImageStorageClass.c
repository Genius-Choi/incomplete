MagickExport MagickBooleanType SetImageStorageClass(Image *image,
  const ClassType storage_class,ExceptionInfo *exception)
{
  image->storage_class=storage_class;
  return(SyncImagePixelCache(image,exception));
}

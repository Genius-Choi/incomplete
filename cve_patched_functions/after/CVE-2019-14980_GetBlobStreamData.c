MagickExport void *GetBlobStreamData(const Image *image)
{
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  return(image->blob->data);
}

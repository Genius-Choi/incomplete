MagickExport void AttachBlob(BlobInfo *blob_info,const void *blob,
  const size_t length)
{
  assert(blob_info != (BlobInfo *) NULL);
  if (blob_info->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"...");
  blob_info->length=length;
  blob_info->extent=length;
  blob_info->quantum=(size_t) MagickMaxBlobExtent;
  blob_info->offset=0;
  blob_info->type=BlobStream;
  blob_info->file_info.file=(FILE *) NULL;
  blob_info->data=(unsigned char *) blob;
  blob_info->mapped=MagickFalse;
}

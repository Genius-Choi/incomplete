MagickExport void AttachCustomStream(BlobInfo *blob_info,
  CustomStreamInfo *custom_stream)
{
  assert(blob_info != (BlobInfo *) NULL);
  assert(custom_stream != (CustomStreamInfo *) NULL);
  assert(custom_stream->signature == MagickCoreSignature);
  if (blob_info->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"...");
  blob_info->type=CustomStream;
  blob_info->custom_stream=custom_stream;
}

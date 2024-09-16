MagickExport void SetCustomStreamData(CustomStreamInfo *custom_stream,
  void *data)
{
  assert(custom_stream != (CustomStreamInfo *) NULL);
  assert(custom_stream->signature == MagickCoreSignature);
  custom_stream->data=data;
}

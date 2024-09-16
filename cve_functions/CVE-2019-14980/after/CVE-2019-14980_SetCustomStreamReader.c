MagickExport void SetCustomStreamReader(CustomStreamInfo *custom_stream,
  CustomStreamHandler reader)
{
  assert(custom_stream != (CustomStreamInfo *) NULL);
  assert(custom_stream->signature == MagickCoreSignature);
  custom_stream->reader=reader;
}

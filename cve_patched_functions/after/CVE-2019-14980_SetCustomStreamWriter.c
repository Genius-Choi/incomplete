MagickExport void SetCustomStreamWriter(CustomStreamInfo *custom_stream,
  CustomStreamHandler writer)
{
  assert(custom_stream != (CustomStreamInfo *) NULL);
  assert(custom_stream->signature == MagickCoreSignature);
  custom_stream->writer=writer;
}

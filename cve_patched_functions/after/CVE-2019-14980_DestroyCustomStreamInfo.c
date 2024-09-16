MagickExport CustomStreamInfo *DestroyCustomStreamInfo(
  CustomStreamInfo *custom_stream)
{
  (void) LogMagickEvent(TraceEvent,GetMagickModule(),"...");
  assert(custom_stream != (CustomStreamInfo *) NULL);
  assert(custom_stream->signature == MagickCoreSignature);
  custom_stream->signature=(~MagickCoreSignature);
  custom_stream=(CustomStreamInfo *) RelinquishMagickMemory(custom_stream);
  return(custom_stream);
}

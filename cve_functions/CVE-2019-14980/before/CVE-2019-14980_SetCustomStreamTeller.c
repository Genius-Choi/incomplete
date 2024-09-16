MagickExport void SetCustomStreamTeller(CustomStreamInfo *custom_stream,
  CustomStreamTeller teller)
{
  assert(custom_stream != (CustomStreamInfo *) NULL);
  assert(custom_stream->signature == MagickCoreSignature);
  custom_stream->teller=teller;
}

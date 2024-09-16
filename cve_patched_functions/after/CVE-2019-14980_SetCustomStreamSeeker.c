MagickExport void SetCustomStreamSeeker(CustomStreamInfo *custom_stream,
  CustomStreamSeeker seeker)
{
  assert(custom_stream != (CustomStreamInfo *) NULL);
  assert(custom_stream->signature == MagickCoreSignature);
  custom_stream->seeker=seeker;
}

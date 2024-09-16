MagickExport MagickBooleanType SetQuantumFormat(const Image *image,
  QuantumInfo *quantum_info,const QuantumFormatType format)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  assert(quantum_info != (QuantumInfo *) NULL);
  assert(quantum_info->signature == MagickCoreSignature);
  quantum_info->format=format;
  return(SetQuantumDepth(image,quantum_info,quantum_info->depth));
}

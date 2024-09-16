MagickExport MagickBooleanType SetQuantumEndian(const Image *image,
  QuantumInfo *quantum_info,const EndianType endian)
{
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  assert(quantum_info != (QuantumInfo *) NULL);
  assert(quantum_info->signature == MagickCoreSignature);
  quantum_info->endian=endian;
  return(SetQuantumDepth(image,quantum_info,quantum_info->depth));
}

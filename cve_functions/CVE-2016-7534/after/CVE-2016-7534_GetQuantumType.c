MagickExport QuantumType GetQuantumType(Image *image,ExceptionInfo *exception)
{
  QuantumType
    quantum_type;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  (void) exception;
  quantum_type=RGBQuantum;
  if (image->alpha_trait != UndefinedPixelTrait)
    quantum_type=RGBAQuantum;
  if (image->colorspace == CMYKColorspace)
    {
      quantum_type=CMYKQuantum;
      if (image->alpha_trait != UndefinedPixelTrait)
        quantum_type=CMYKAQuantum;
    }
  if (IsGrayColorspace(image->colorspace) != MagickFalse)
    {
      quantum_type=GrayQuantum;
      if (image->alpha_trait != UndefinedPixelTrait)
        quantum_type=GrayAlphaQuantum;
    }
  if (image->storage_class == PseudoClass)
    {
      quantum_type=IndexQuantum;
      if (image->alpha_trait != UndefinedPixelTrait)
        quantum_type=IndexAlphaQuantum;
    }
  return(quantum_type);
}

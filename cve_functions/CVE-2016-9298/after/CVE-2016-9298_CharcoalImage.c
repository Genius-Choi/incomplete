MagickExport Image *CharcoalImage(const Image *image,const double radius,
  const double sigma,ExceptionInfo *exception)
{
  Image
    *charcoal_image,
    *clone_image,
    *edge_image;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  clone_image=CloneImage(image,0,0,MagickTrue,exception);
  if (clone_image == (Image *) NULL)
    return((Image *) NULL);
  edge_image=EdgeImage(clone_image,radius,exception);
  clone_image=DestroyImage(clone_image);
  if (edge_image == (Image *) NULL)
    return((Image *) NULL);
  charcoal_image=BlurImage(edge_image,radius,sigma,exception);
  edge_image=DestroyImage(edge_image);
  if (charcoal_image == (Image *) NULL)
    return((Image *) NULL);
  (void) NormalizeImage(charcoal_image,exception);
  (void) NegateImage(charcoal_image,MagickFalse,exception);
  (void) GrayscaleImage(charcoal_image,image->intensity,exception);
  return(charcoal_image);
}

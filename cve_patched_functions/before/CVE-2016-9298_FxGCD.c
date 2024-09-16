static MagickOffsetType FxGCD(MagickOffsetType alpha,MagickOffsetType beta)
{
  if (beta != 0)
    return(FxGCD(beta,alpha % beta));
  return(alpha);
}

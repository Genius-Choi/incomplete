static double FxChannelStatistics(FxInfo *fx_info,Image *image,
  PixelChannel channel,const char *symbol,ExceptionInfo *exception)
{
  ChannelType
    channel_mask;

  char
    key[MagickPathExtent],
    statistic[MagickPathExtent];

  const char
    *value;

  register const char
    *p;

  channel_mask=UndefinedChannel;
  for (p=symbol; (*p != '.') && (*p != '\0'); p++) ;
  if (*p == '.')
    {
      ssize_t
        option;

      option=ParseCommandOption(MagickPixelChannelOptions,MagickTrue,p+1);
      if (option >= 0)
        {
          channel=(PixelChannel) option;
          channel_mask=(ChannelType) (channel_mask | (1 << channel));
          (void) SetPixelChannelMask(image,channel_mask);
        }
    }
  (void) FormatLocaleString(key,MagickPathExtent,"%p.%.20g.%s",(void *) image,
    (double) channel,symbol);
  value=(const char *) GetValueFromSplayTree(fx_info->symbols,key);
  if (value != (const char *) NULL)
    {
      if (channel_mask != UndefinedChannel)
        (void) SetPixelChannelMask(image,channel_mask);
      return(QuantumScale*StringToDouble(value,(char **) NULL));
    }
  (void) DeleteNodeFromSplayTree(fx_info->symbols,key);
  if (LocaleNCompare(symbol,"depth",5) == 0)
    {
      size_t
        depth;

      depth=GetImageDepth(image,exception);
      (void) FormatLocaleString(statistic,MagickPathExtent,"%.20g",(double)
        depth);
    }
  if (LocaleNCompare(symbol,"kurtosis",8) == 0)
    {
      double
        kurtosis,
        skewness;

      (void) GetImageKurtosis(image,&kurtosis,&skewness,exception);
      (void) FormatLocaleString(statistic,MagickPathExtent,"%g",kurtosis);
    }
  if (LocaleNCompare(symbol,"maxima",6) == 0)
    {
      double
        maxima,
        minima;

      (void) GetImageRange(image,&minima,&maxima,exception);
      (void) FormatLocaleString(statistic,MagickPathExtent,"%g",maxima);
    }
  if (LocaleNCompare(symbol,"mean",4) == 0)
    {
      double
        mean,
        standard_deviation;

      (void) GetImageMean(image,&mean,&standard_deviation,exception);
      (void) FormatLocaleString(statistic,MagickPathExtent,"%g",mean);
    }
  if (LocaleNCompare(symbol,"minima",6) == 0)
    {
      double
        maxima,
        minima;

      (void) GetImageRange(image,&minima,&maxima,exception);
      (void) FormatLocaleString(statistic,MagickPathExtent,"%g",minima);
    }
  if (LocaleNCompare(symbol,"skewness",8) == 0)
    {
      double
        kurtosis,
        skewness;

      (void) GetImageKurtosis(image,&kurtosis,&skewness,exception);
      (void) FormatLocaleString(statistic,MagickPathExtent,"%g",skewness);
    }
  if (LocaleNCompare(symbol,"standard_deviation",18) == 0)
    {
      double
        mean,
        standard_deviation;

      (void) GetImageMean(image,&mean,&standard_deviation,exception);
      (void) FormatLocaleString(statistic,MagickPathExtent,"%g",
        standard_deviation);
    }
  if (channel_mask != UndefinedChannel)
    (void) SetPixelChannelMask(image,channel_mask);
  (void) AddValueToSplayTree(fx_info->symbols,ConstantString(key),
    ConstantString(statistic));
  return(QuantumScale*StringToDouble(statistic,(char **) NULL));
}

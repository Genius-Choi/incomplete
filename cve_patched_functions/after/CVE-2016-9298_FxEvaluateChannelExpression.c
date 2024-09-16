MagickPrivate MagickBooleanType FxEvaluateChannelExpression(FxInfo *fx_info,
  const PixelChannel channel,const ssize_t x,const ssize_t y,
  double *alpha,ExceptionInfo *exception)
{
  double
    beta;

  size_t
    depth;

  depth=0;
  beta=0.0;
  *alpha=FxEvaluateSubexpression(fx_info,channel,x,y,fx_info->expression,&depth,
    &beta,exception);
  return(exception->severity == OptionError ? MagickFalse : MagickTrue);
}

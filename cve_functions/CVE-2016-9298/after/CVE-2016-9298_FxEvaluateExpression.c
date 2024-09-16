MagickPrivate MagickBooleanType FxEvaluateExpression(FxInfo *fx_info,
  double *alpha,ExceptionInfo *exception)
{
  MagickBooleanType
    status;

  status=FxEvaluateChannelExpression(fx_info,GrayPixelChannel,0,0,alpha,
    exception);
  return(status);
}

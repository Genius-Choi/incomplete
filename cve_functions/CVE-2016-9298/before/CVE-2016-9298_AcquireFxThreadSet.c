static FxInfo **AcquireFxThreadSet(const Image *image,const char *expression,
  ExceptionInfo *exception)
{
  char
    *fx_expression;

  FxInfo
    **fx_info;

  double
    alpha;

  register ssize_t
    i;

  size_t
    number_threads;

  number_threads=(size_t) GetMagickResourceLimit(ThreadResource);
  fx_info=(FxInfo **) AcquireQuantumMemory(number_threads,sizeof(*fx_info));
  if (fx_info == (FxInfo **) NULL)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),
        ResourceLimitError,"MemoryAllocationFailed","`%s'",image->filename);
      return((FxInfo **) NULL);
    }
  (void) ResetMagickMemory(fx_info,0,number_threads*sizeof(*fx_info));
  if (*expression != '@')
    fx_expression=ConstantString(expression);
  else
    fx_expression=FileToString(expression+1,~0UL,exception);
  for (i=0; i < (ssize_t) number_threads; i++)
  {
    MagickBooleanType
      status;

    fx_info[i]=AcquireFxInfo(image,fx_expression,exception);
    if (fx_info[i] == (FxInfo *) NULL)
      break;
    status=FxPreprocessExpression(fx_info[i],&alpha,exception);
    if (status == MagickFalse)
      break;
  }
  fx_expression=DestroyString(fx_expression);
  if (i < (ssize_t) number_threads)
    fx_info=DestroyFxThreadSet(fx_info);
  return(fx_info);
}

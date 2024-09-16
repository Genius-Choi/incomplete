MagickPrivate FxInfo *DestroyFxInfo(FxInfo *fx_info)
{
  register ssize_t
    i;

  fx_info->exception=DestroyExceptionInfo(fx_info->exception);
  fx_info->expression=DestroyString(fx_info->expression);
  fx_info->symbols=DestroySplayTree(fx_info->symbols);
  fx_info->colors=DestroySplayTree(fx_info->colors);
  for (i=(ssize_t) GetImageListLength(fx_info->images)-1; i >= 0; i--)
    fx_info->view[i]=DestroyCacheView(fx_info->view[i]);
  fx_info->view=(CacheView **) RelinquishMagickMemory(fx_info->view);
  fx_info->random_info=DestroyRandomInfo(fx_info->random_info);
  fx_info=(FxInfo *) RelinquishMagickMemory(fx_info);
  return(fx_info);
}

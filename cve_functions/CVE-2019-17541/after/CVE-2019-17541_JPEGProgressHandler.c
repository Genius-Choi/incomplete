static void JPEGProgressHandler(j_common_ptr jpeg_info)
{
  ErrorManager
    *error_manager;

  ExceptionInfo
    *exception;

  Image
    *image;

  error_manager=(ErrorManager *) jpeg_info->client_data;
  image=error_manager->image;
  exception=error_manager->exception;
  if (jpeg_info->is_decompressor == 0)
    return;
  if (((j_decompress_ptr) jpeg_info)->input_scan_number < MaxJPEGScans)
    return;
  (void) ThrowMagickException(exception,GetMagickModule(),CorruptImageError,
    "too many scans","`%s'",image->filename);
  longjmp(error_manager->error_recovery,1);
}

ModuleExport size_t RegisterJPEGImage(void)
{
#define JPEGDescription "Joint Photographic Experts Group JFIF format"
#define JPEGStringify(macro_or_string)  JPEGStringifyArg(macro_or_string)
#define JPEGStringifyArg(contents)  #contents

  char
    version[MagickPathExtent];

  MagickInfo
    *entry;

  *version='\0';
#if defined(LIBJPEG_TURBO_VERSION)
  (void) CopyMagickString(version,"libjpeg-turbo " JPEGStringify(
    LIBJPEG_TURBO_VERSION),MagickPathExtent);
#elif defined(JPEG_LIB_VERSION)
  (void) FormatLocaleString(version,MagickPathExtent,"libjpeg %d",
    JPEG_LIB_VERSION);
#endif
  entry=AcquireMagickInfo("JPEG","JPE",JPEGDescription);
#if (JPEG_LIB_VERSION < 80) && !defined(LIBJPEG_TURBO_VERSION)
  entry->flags^=CoderDecoderThreadSupportFlag;
#endif
#if defined(MAGICKCORE_JPEG_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadJPEGImage;
  entry->encoder=(EncodeImageHandler *) WriteJPEGImage;
#endif
  entry->magick=(IsImageFormatHandler *) IsJPEG;
  entry->flags|=CoderDecoderSeekableStreamFlag;
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderUseExtensionFlag;
  if (*version != '\0')
    entry->version=ConstantString(version);
  entry->mime_type=ConstantString("image/jpeg");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("JPEG","JPEG",JPEGDescription);
#if (JPEG_LIB_VERSION < 80) && !defined(LIBJPEG_TURBO_VERSION)
  entry->flags^=CoderDecoderThreadSupportFlag;
#endif
#if defined(MAGICKCORE_JPEG_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadJPEGImage;
  entry->encoder=(EncodeImageHandler *) WriteJPEGImage;
#endif
  entry->magick=(IsImageFormatHandler *) IsJPEG;
  entry->flags|=CoderDecoderSeekableStreamFlag;
  entry->flags^=CoderAdjoinFlag;
  if (*version != '\0')
    entry->version=ConstantString(version);
  entry->mime_type=ConstantString("image/jpeg");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("JPEG","JPG",JPEGDescription);
#if (JPEG_LIB_VERSION < 80) && !defined(LIBJPEG_TURBO_VERSION)
  entry->flags^=CoderDecoderThreadSupportFlag;
#endif
#if defined(MAGICKCORE_JPEG_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadJPEGImage;
  entry->encoder=(EncodeImageHandler *) WriteJPEGImage;
#endif
  entry->flags|=CoderDecoderSeekableStreamFlag;
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderUseExtensionFlag;
  if (*version != '\0')
    entry->version=ConstantString(version);
  entry->mime_type=ConstantString("image/jpeg");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("JPEG","JPS",JPEGDescription);
#if (JPEG_LIB_VERSION < 80) && !defined(LIBJPEG_TURBO_VERSION)
  entry->flags^=CoderDecoderThreadSupportFlag;
#endif
#if defined(MAGICKCORE_JPEG_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadJPEGImage;
  entry->encoder=(EncodeImageHandler *) WriteJPEGImage;
#endif
  entry->flags|=CoderDecoderSeekableStreamFlag;
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderUseExtensionFlag;
  if (*version != '\0')
    entry->version=ConstantString(version);
  entry->mime_type=ConstantString("image/jpeg");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("JPEG","PJPEG",JPEGDescription);
#if (JPEG_LIB_VERSION < 80) && !defined(LIBJPEG_TURBO_VERSION)
  entry->flags^=CoderDecoderThreadSupportFlag;
#endif
#if defined(MAGICKCORE_JPEG_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadJPEGImage;
  entry->encoder=(EncodeImageHandler *) WriteJPEGImage;
#endif
  entry->flags|=CoderDecoderSeekableStreamFlag;
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderUseExtensionFlag;
  if (*version != '\0')
    entry->version=ConstantString(version);
  entry->mime_type=ConstantString("image/jpeg");
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}

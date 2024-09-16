IW_IMPL(int) iw_is_output_fmt_supported(int fmt)
{
	switch(fmt) {
#if IW_SUPPORT_PNG == 1
	case IW_FORMAT_PNG:
#endif
#if IW_SUPPORT_JPEG == 1
	case IW_FORMAT_JPEG:
#endif
#if IW_SUPPORT_WEBP == 1
	case IW_FORMAT_WEBP:
#endif
	case IW_FORMAT_BMP:
	case IW_FORMAT_TIFF:
	case IW_FORMAT_MIFF:
	case IW_FORMAT_PNM:
	case IW_FORMAT_PPM:
	case IW_FORMAT_PGM:
	case IW_FORMAT_PBM:
	case IW_FORMAT_PAM:
		return 1;
	}
	return 0;
}

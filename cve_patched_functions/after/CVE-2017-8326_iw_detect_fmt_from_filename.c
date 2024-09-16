IW_IMPL(int) iw_detect_fmt_from_filename(const char *fn)
{
	char *s;
	int i;
	struct fmttable_struct {
		const char *ext;
		int fmt;
	};
	static const struct fmttable_struct fmttable[] = {
	 {"png", IW_FORMAT_PNG},
	 {"jpg", IW_FORMAT_JPEG},
	 {"jpeg", IW_FORMAT_JPEG},
	 {"bmp", IW_FORMAT_BMP},
	 {"tif", IW_FORMAT_TIFF},
	 {"tiff", IW_FORMAT_TIFF},
	 {"miff", IW_FORMAT_MIFF},
	 {"webp", IW_FORMAT_WEBP},
	 {"gif", IW_FORMAT_GIF},
	 {"pnm", IW_FORMAT_PNM},
	 {"pbm", IW_FORMAT_PBM},
	 {"pgm", IW_FORMAT_PGM},
	 {"ppm", IW_FORMAT_PPM},
	 {"pam", IW_FORMAT_PAM},
	 {NULL, 0}
	};

	s=strrchr(fn,'.');
	if(!s) return IW_FORMAT_UNKNOWN;
	s++;

	for(i=0;fmttable[i].ext;i++) {
		if(!iw_stricmp(s,fmttable[i].ext)) return fmttable[i].fmt;
	}
	
	return IW_FORMAT_UNKNOWN;
}

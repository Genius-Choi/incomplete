IW_IMPL(int) iw_detect_fmt_of_file(const iw_byte *buf, size_t n)
{
	int fmt = IW_FORMAT_UNKNOWN;

	if(n<2) return fmt;

	if(buf[0]==0x89 && buf[1]==0x50) {
		fmt=IW_FORMAT_PNG;
	}
	else if(n>=3 && buf[0]=='G' && buf[1]=='I' && buf[2]=='F') {
		fmt=IW_FORMAT_GIF;
	}
	else if(buf[0]==0xff && buf[1]==0xd8) {
		fmt=IW_FORMAT_JPEG;
	}
	else if(buf[0]=='B' && buf[1]=='M') {
		fmt=IW_FORMAT_BMP;
	}
	else if(buf[0]=='B' && buf[1]=='A') {
		fmt=IW_FORMAT_BMP;
	}
	else if((buf[0]==0x49 || buf[0]==0x4d) && buf[1]==buf[0]) {
		fmt=IW_FORMAT_TIFF;
	}
	else if(buf[0]==0x69 && buf[1]==0x64) {
		fmt=IW_FORMAT_MIFF;
	}
	else if(n>=12 && buf[0]==0x52 && buf[1]==0x49 && buf[2]==0x46 && buf[3]==0x46 &&
	   buf[8]==0x57 && buf[9]==0x45 && buf[10]==0x42 && buf[11]==0x50)
	{
		fmt=IW_FORMAT_WEBP;
	}
	else if(buf[0]=='P' && (buf[1]>='1' && buf[1]<='6')) {
		return IW_FORMAT_PNM;
	}
	else if(buf[0]=='P' && (buf[1]=='7' && buf[2]==0x0a)) {
		return IW_FORMAT_PAM;
	}

	return fmt;
}

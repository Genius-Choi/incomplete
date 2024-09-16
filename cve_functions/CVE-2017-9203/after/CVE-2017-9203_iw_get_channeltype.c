static int iw_get_channeltype(int imgtype, int channel)
{
	switch(imgtype) {
	case IW_IMGTYPE_GRAY:
		if(channel==0) return IW_CHANNELTYPE_GRAY;
		break;
	case IW_IMGTYPE_GRAYA:
		if(channel==0) return IW_CHANNELTYPE_GRAY;
		if(channel==1) return IW_CHANNELTYPE_ALPHA;
		break;
	case IW_IMGTYPE_RGB:
		if(channel==0) return IW_CHANNELTYPE_RED;
		if(channel==1) return IW_CHANNELTYPE_GREEN;
		if(channel==2) return IW_CHANNELTYPE_BLUE;
		break;
	case IW_IMGTYPE_RGBA:
		if(channel==0) return IW_CHANNELTYPE_RED;
		if(channel==1) return IW_CHANNELTYPE_GREEN;
		if(channel==2) return IW_CHANNELTYPE_BLUE;
		if(channel==3) return IW_CHANNELTYPE_ALPHA;
		break;
	}
	return 0;
}

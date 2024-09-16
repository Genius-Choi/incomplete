static int iw_imgtype_alpha_channel_index(int t)
{
	switch(t) {
	case IW_IMGTYPE_RGBA:
		return 3;
	case IW_IMGTYPE_GRAYA:
		return 1;
	}
	return 0;
}

int hns_rcb_buf_size2type(u32 buf_size)
{
	int bd_size_type;

	switch (buf_size) {
	case 512:
		bd_size_type = HNS_BD_SIZE_512_TYPE;
		break;
	case 1024:
		bd_size_type = HNS_BD_SIZE_1024_TYPE;
		break;
	case 2048:
		bd_size_type = HNS_BD_SIZE_2048_TYPE;
		break;
	case 4096:
		bd_size_type = HNS_BD_SIZE_4096_TYPE;
		break;
	default:
		bd_size_type = -EINVAL;
	}

	return bd_size_type;
}

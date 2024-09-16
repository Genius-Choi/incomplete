nfsd4_decode_getdeviceinfo(struct nfsd4_compoundargs *argp,
		struct nfsd4_getdeviceinfo *gdev)
{
	DECODE_HEAD;
	u32 num, i;

	READ_BUF(sizeof(struct nfsd4_deviceid) + 3 * 4);
	COPYMEM(&gdev->gd_devid, sizeof(struct nfsd4_deviceid));
	gdev->gd_layout_type = be32_to_cpup(p++);
	gdev->gd_maxcount = be32_to_cpup(p++);
	num = be32_to_cpup(p++);
	if (num) {
		READ_BUF(4 * num);
		gdev->gd_notify_types = be32_to_cpup(p++);
		for (i = 1; i < num; i++) {
			if (be32_to_cpup(p++)) {
				status = nfserr_inval;
				goto out;
			}
		}
	}
	DECODE_TAIL;
}

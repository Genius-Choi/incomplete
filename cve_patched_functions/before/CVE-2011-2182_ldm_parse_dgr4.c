static bool ldm_parse_dgr4 (const u8 *buffer, int buflen, struct vblk *vb)
{
	char buf[64];
	int r_objid, r_name, r_id1, r_id2, len;
	struct vblk_dgrp *dgrp;

	BUG_ON (!buffer || !vb);

	r_objid  = ldm_relative (buffer, buflen, 0x18, 0);
	r_name   = ldm_relative (buffer, buflen, 0x18, r_objid);

	if (buffer[0x12] & VBLK_FLAG_DGR4_IDS) {
		r_id1 = ldm_relative (buffer, buflen, 0x44, r_name);
		r_id2 = ldm_relative (buffer, buflen, 0x44, r_id1);
		len = r_id2;
	} else {
		r_id1 = 0;
		r_id2 = 0;
		len = r_name;
	}
	if (len < 0)
		return false;

	len += VBLK_SIZE_DGR4;
	if (len != get_unaligned_be32(buffer + 0x14))
		return false;

	dgrp = &vb->vblk.dgrp;

	ldm_get_vstr (buffer + 0x18 + r_objid, buf, sizeof (buf));
	return true;
}

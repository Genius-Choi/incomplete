static bool ldm_parse_dsk4 (const u8 *buffer, int buflen, struct vblk *vb)
{
	int r_objid, r_name, len;
	struct vblk_disk *disk;

	BUG_ON (!buffer || !vb);

	r_objid = ldm_relative (buffer, buflen, 0x18, 0);
	r_name  = ldm_relative (buffer, buflen, 0x18, r_objid);
	len     = r_name;
	if (len < 0)
		return false;

	len += VBLK_SIZE_DSK4;
	if (len != get_unaligned_be32(buffer + 0x14))
		return false;

	disk = &vb->vblk.disk;
	memcpy (disk->disk_id, buffer + 0x18 + r_name, GUID_SIZE);
	return true;
}

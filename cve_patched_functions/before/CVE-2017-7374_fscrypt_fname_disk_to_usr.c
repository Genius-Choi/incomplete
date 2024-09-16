int fscrypt_fname_disk_to_usr(struct inode *inode,
			u32 hash, u32 minor_hash,
			const struct fscrypt_str *iname,
			struct fscrypt_str *oname)
{
	const struct qstr qname = FSTR_TO_QSTR(iname);
	char buf[24];

	if (fscrypt_is_dot_dotdot(&qname)) {
		oname->name[0] = '.';
		oname->name[iname->len - 1] = '.';
		oname->len = iname->len;
		return 0;
	}

	if (iname->len < FS_CRYPTO_BLOCK_SIZE)
		return -EUCLEAN;

	if (inode->i_crypt_info)
		return fname_decrypt(inode, iname, oname);

	if (iname->len <= FS_FNAME_CRYPTO_DIGEST_SIZE) {
		oname->len = digest_encode(iname->name, iname->len,
					   oname->name);
		return 0;
	}
	if (hash) {
		memcpy(buf, &hash, 4);
		memcpy(buf + 4, &minor_hash, 4);
	} else {
		memset(buf, 0, 8);
	}
	memcpy(buf + 8, iname->name + iname->len - 16, 16);
	oname->name[0] = '_';
	oname->len = 1 + digest_encode(buf, 24, oname->name + 1);
	return 0;
}

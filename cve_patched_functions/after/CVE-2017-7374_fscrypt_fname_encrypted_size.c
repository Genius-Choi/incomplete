u32 fscrypt_fname_encrypted_size(const struct inode *inode, u32 ilen)
{
	int padding = 32;
	struct fscrypt_info *ci = inode->i_crypt_info;

	if (ci)
		padding = 4 << (ci->ci_flags & FS_POLICY_FLAGS_PAD_MASK);
	ilen = max(ilen, (u32)FS_CRYPTO_BLOCK_SIZE);
	return round_up(ilen, padding);
}

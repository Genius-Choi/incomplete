ossl_cipher_update_long(EVP_CIPHER_CTX *ctx, unsigned char *out, long *out_len_ptr,
			const unsigned char *in, long in_len)
{
    int out_part_len;
    int limit = INT_MAX / 2 + 1;
    long out_len = 0;

    do {
	int in_part_len = in_len > limit ? limit : (int)in_len;

	if (!EVP_CipherUpdate(ctx, out ? (out + out_len) : 0,
			      &out_part_len, in, in_part_len))
	    return 0;

	out_len += out_part_len;
	in += in_part_len;
    } while ((in_len -= limit) > 0);

    if (out_len_ptr)
	*out_len_ptr = out_len;

    return 1;
}

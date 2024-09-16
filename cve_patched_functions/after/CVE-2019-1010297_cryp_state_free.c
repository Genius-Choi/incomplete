static void cryp_state_free(struct user_ta_ctx *utc, struct tee_cryp_state *cs)
{
	struct tee_obj *o;

	if (tee_obj_get(utc, cs->key1, &o) == TEE_SUCCESS)
		tee_obj_close(utc, o);
	if (tee_obj_get(utc, cs->key2, &o) == TEE_SUCCESS)
		tee_obj_close(utc, o);

	TAILQ_REMOVE(&utc->cryp_states, cs, link);
	if (cs->ctx_finalize != NULL)
		cs->ctx_finalize(cs->ctx, cs->algo);

	switch (TEE_ALG_GET_CLASS(cs->algo)) {
	case TEE_OPERATION_CIPHER:
		crypto_cipher_free_ctx(cs->ctx, cs->algo);
		break;
	case TEE_OPERATION_AE:
		crypto_authenc_free_ctx(cs->ctx, cs->algo);
		break;
	case TEE_OPERATION_DIGEST:
		crypto_hash_free_ctx(cs->ctx, cs->algo);
		break;
	case TEE_OPERATION_MAC:
		crypto_mac_free_ctx(cs->ctx, cs->algo);
		break;
	default:
		assert(!cs->ctx);
	}

	free(cs);
}

static TEE_Result tee_svc_cryp_check_key_type(const struct tee_obj *o,
					      uint32_t algo,
					      TEE_OperationMode mode)
{
	uint32_t req_key_type;
	uint32_t req_key_type2 = 0;

	switch (TEE_ALG_GET_MAIN_ALG(algo)) {
	case TEE_MAIN_ALGO_MD5:
		req_key_type = TEE_TYPE_HMAC_MD5;
		break;
	case TEE_MAIN_ALGO_SHA1:
		req_key_type = TEE_TYPE_HMAC_SHA1;
		break;
	case TEE_MAIN_ALGO_SHA224:
		req_key_type = TEE_TYPE_HMAC_SHA224;
		break;
	case TEE_MAIN_ALGO_SHA256:
		req_key_type = TEE_TYPE_HMAC_SHA256;
		break;
	case TEE_MAIN_ALGO_SHA384:
		req_key_type = TEE_TYPE_HMAC_SHA384;
		break;
	case TEE_MAIN_ALGO_SHA512:
		req_key_type = TEE_TYPE_HMAC_SHA512;
		break;
	case TEE_MAIN_ALGO_AES:
		req_key_type = TEE_TYPE_AES;
		break;
	case TEE_MAIN_ALGO_DES:
		req_key_type = TEE_TYPE_DES;
		break;
	case TEE_MAIN_ALGO_DES3:
		req_key_type = TEE_TYPE_DES3;
		break;
	case TEE_MAIN_ALGO_RSA:
		req_key_type = TEE_TYPE_RSA_KEYPAIR;
		if (mode == TEE_MODE_ENCRYPT || mode == TEE_MODE_VERIFY)
			req_key_type2 = TEE_TYPE_RSA_PUBLIC_KEY;
		break;
	case TEE_MAIN_ALGO_DSA:
		req_key_type = TEE_TYPE_DSA_KEYPAIR;
		if (mode == TEE_MODE_ENCRYPT || mode == TEE_MODE_VERIFY)
			req_key_type2 = TEE_TYPE_DSA_PUBLIC_KEY;
		break;
	case TEE_MAIN_ALGO_DH:
		req_key_type = TEE_TYPE_DH_KEYPAIR;
		break;
	case TEE_MAIN_ALGO_ECDSA:
		req_key_type = TEE_TYPE_ECDSA_KEYPAIR;
		if (mode == TEE_MODE_VERIFY)
			req_key_type2 = TEE_TYPE_ECDSA_PUBLIC_KEY;
		break;
	case TEE_MAIN_ALGO_ECDH:
		req_key_type = TEE_TYPE_ECDH_KEYPAIR;
		break;
#if defined(CFG_CRYPTO_HKDF)
	case TEE_MAIN_ALGO_HKDF:
		req_key_type = TEE_TYPE_HKDF_IKM;
		break;
#endif
#if defined(CFG_CRYPTO_CONCAT_KDF)
	case TEE_MAIN_ALGO_CONCAT_KDF:
		req_key_type = TEE_TYPE_CONCAT_KDF_Z;
		break;
#endif
#if defined(CFG_CRYPTO_PBKDF2)
	case TEE_MAIN_ALGO_PBKDF2:
		req_key_type = TEE_TYPE_PBKDF2_PASSWORD;
		break;
#endif
	default:
		return TEE_ERROR_BAD_PARAMETERS;
	}

	if (req_key_type != o->info.objectType &&
	    req_key_type2 != o->info.objectType)
		return TEE_ERROR_BAD_PARAMETERS;
	return TEE_SUCCESS;
}

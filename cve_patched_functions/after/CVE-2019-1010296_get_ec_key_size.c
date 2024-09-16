static TEE_Result get_ec_key_size(uint32_t curve, size_t *key_size)
{
	switch (curve) {
	case TEE_ECC_CURVE_NIST_P192:
		*key_size = 192;
		break;
	case TEE_ECC_CURVE_NIST_P224:
		*key_size = 224;
		break;
	case TEE_ECC_CURVE_NIST_P256:
		*key_size = 256;
		break;
	case TEE_ECC_CURVE_NIST_P384:
		*key_size = 384;
		break;
	case TEE_ECC_CURVE_NIST_P521:
		*key_size = 521;
		break;
	default:
		return TEE_ERROR_NOT_SUPPORTED;
	}

	return TEE_SUCCESS;
}

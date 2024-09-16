static TEE_Result tee_svc_update_out_param(
		struct tee_ta_param *param,
		void *tmp_buf_va[TEE_NUM_PARAMS],
		struct utee_params *usr_param)
{
	size_t n;
	uint64_t *vals = usr_param->vals;

	for (n = 0; n < TEE_NUM_PARAMS; n++) {
		switch (TEE_PARAM_TYPE_GET(param->types, n)) {
		case TEE_PARAM_TYPE_MEMREF_OUTPUT:
		case TEE_PARAM_TYPE_MEMREF_INOUT:
			/*
			 * Memory copy is only needed if there's a temporary
			 * buffer involved, tmp_buf_va[n] is only update if
			 * a temporary buffer is used. Otherwise only the
			 * size needs to be updated.
			 */
			if (tmp_buf_va[n] &&
			    param->u[n].mem.size <= vals[n * 2 + 1]) {
				void *src = tmp_buf_va[n];
				void *dst = (void *)(uintptr_t)vals[n * 2];
				TEE_Result res;

				res = tee_svc_copy_to_user(dst, src,
						 param->u[n].mem.size);
				if (res != TEE_SUCCESS)
					return res;

			}
			usr_param->vals[n * 2 + 1] = param->u[n].mem.size;
			break;

		case TEE_PARAM_TYPE_VALUE_OUTPUT:
		case TEE_PARAM_TYPE_VALUE_INOUT:
			vals[n * 2] = param->u[n].val.a;
			vals[n * 2 + 1] = param->u[n].val.b;
			break;

		default:
			continue;
		}
	}

	return TEE_SUCCESS;
}

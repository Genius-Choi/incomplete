static int cm_compare_private_data(u8 *private_data,
				   struct ib_cm_compare_data *dst_data)
{
	u8 src[IB_CM_COMPARE_SIZE];

	if (!dst_data)
		return 0;

	cm_mask_copy(src, private_data, dst_data->mask);
	return memcmp(src, dst_data->data, IB_CM_COMPARE_SIZE);
}

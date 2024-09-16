static int ucm_validate_listen(__be64 service_id, __be64 service_mask)
{
	service_id &= service_mask;

	if (((service_id & IB_CMA_SERVICE_ID_MASK) == IB_CMA_SERVICE_ID) ||
	    ((service_id & IB_SDP_SERVICE_ID_MASK) == IB_SDP_SERVICE_ID))
		return -EINVAL;

	return 0;
}

static void get_prop_set(unsigned long prop_set,
			 const struct tee_props **props,
			 size_t *size,
			 const struct tee_props **vendor_props,
			 size_t *vendor_size)
{
	if ((TEE_PropSetHandle)prop_set == TEE_PROPSET_CURRENT_CLIENT) {
		*props = tee_propset_client;
		*size = ARRAY_SIZE(tee_propset_client);
		*vendor_props = vendor_props_client.props;
		*vendor_size = vendor_props_client.len;
	} else if ((TEE_PropSetHandle)prop_set == TEE_PROPSET_CURRENT_TA) {
		*props = tee_propset_ta;
		*size = ARRAY_SIZE(tee_propset_ta);
		*vendor_props = vendor_props_ta.props;
		*vendor_size = vendor_props_ta.len;
	} else if ((TEE_PropSetHandle)prop_set ==
		   TEE_PROPSET_TEE_IMPLEMENTATION) {
		*props = tee_propset_tee;
		*size = ARRAY_SIZE(tee_propset_tee);
		*vendor_props = vendor_props_tee.props;
		*vendor_size = vendor_props_tee.len;
	} else {
		*props = NULL;
		*size = 0;
		*vendor_props = NULL;
		*vendor_size = 0;
	}
}

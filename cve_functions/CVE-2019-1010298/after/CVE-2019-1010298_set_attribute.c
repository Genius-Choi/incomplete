static void set_attribute(struct tee_obj *o,
			  const struct tee_cryp_obj_type_props *props,
			  uint32_t attr)
{
	int idx = tee_svc_cryp_obj_find_type_attr_idx(attr, props);

	if (idx < 0)
		return;
	o->have_attrs |= BIT(idx);
}

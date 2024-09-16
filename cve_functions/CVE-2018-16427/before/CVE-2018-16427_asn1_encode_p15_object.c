static int asn1_encode_p15_object(sc_context_t *ctx, const struct sc_asn1_pkcs15_object *obj,
				  u8 **buf, size_t *bufsize, int depth)
{
	struct sc_pkcs15_object p15_obj = *obj->p15_obj;
	struct sc_asn1_entry    asn1_c_attr[6], asn1_p15_obj[5];
	struct sc_asn1_entry asn1_ac_rules[SC_PKCS15_MAX_ACCESS_RULES + 1], asn1_ac_rule[SC_PKCS15_MAX_ACCESS_RULES][3];
	size_t label_len = strlen(p15_obj.label);
	size_t flags_len;
	size_t access_mode_len;
	int r, ii;

	sc_debug(ctx, SC_LOG_DEBUG_ASN1, "encode p15 obj(type:0x%X,access_mode:0x%X)", p15_obj.type, p15_obj.access_rules[0].access_mode);
	if (p15_obj.access_rules[0].access_mode)   {
		for (ii=0; ii<SC_PKCS15_MAX_ACCESS_RULES; ii++)   {
			sc_copy_asn1_entry(c_asn1_access_control_rule, asn1_ac_rule[ii]);
			if (p15_obj.access_rules[ii].auth_id.len == 0)   {
				asn1_ac_rule[ii][1].type = SC_ASN1_NULL;
				asn1_ac_rule[ii][1].tag = SC_ASN1_TAG_NULL;
			}
		}
		sc_copy_asn1_entry(c_asn1_access_control_rules, asn1_ac_rules);
	}

	sc_copy_asn1_entry(c_asn1_com_obj_attr, asn1_c_attr);
	sc_copy_asn1_entry(c_asn1_p15_obj, asn1_p15_obj);
	if (label_len != 0)
		sc_format_asn1_entry(asn1_c_attr + 0, (void *) p15_obj.label, &label_len, 1);
	if (p15_obj.flags) {
		flags_len = sizeof(p15_obj.flags);
		sc_format_asn1_entry(asn1_c_attr + 1, (void *) &p15_obj.flags, &flags_len, 1);
	}
	if (p15_obj.auth_id.len)
		sc_format_asn1_entry(asn1_c_attr + 2, (void *) &p15_obj.auth_id, NULL, 1);
	if (p15_obj.user_consent)
		sc_format_asn1_entry(asn1_c_attr + 3, (void *) &p15_obj.user_consent, NULL, 1);

	if (p15_obj.access_rules[0].access_mode)   {
		for (ii=0; p15_obj.access_rules[ii].access_mode; ii++)   {
			access_mode_len = sizeof(p15_obj.access_rules[ii].access_mode);
			sc_format_asn1_entry(asn1_ac_rule[ii] + 0, (void *) &p15_obj.access_rules[ii].access_mode, &access_mode_len, 1);
			sc_format_asn1_entry(asn1_ac_rule[ii] + 1, (void *) &p15_obj.access_rules[ii].auth_id, NULL, 1);
			sc_format_asn1_entry(asn1_ac_rules + ii, asn1_ac_rule[ii], NULL, 1);
		}
		sc_format_asn1_entry(asn1_c_attr + 4, asn1_ac_rules, NULL, 1);
	}

	sc_format_asn1_entry(asn1_p15_obj + 0, asn1_c_attr, NULL, 1);
	sc_format_asn1_entry(asn1_p15_obj + 1, obj->asn1_class_attr, NULL, 1);
	if (obj->asn1_subclass_attr != NULL && obj->asn1_subclass_attr->name)
		sc_format_asn1_entry(asn1_p15_obj + 2, obj->asn1_subclass_attr, NULL, 1);
	sc_format_asn1_entry(asn1_p15_obj + 3, obj->asn1_type_attr, NULL, 1);

	r = asn1_encode(ctx, asn1_p15_obj, buf, bufsize, depth + 1);
	return r;
}

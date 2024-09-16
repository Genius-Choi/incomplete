static void hns_ppe_set_qid(struct ppe_common_cb *ppe_common, u32 qid)
{
	u32 qid_mod = dsaf_read_dev(ppe_common, PPE_COM_CFG_QID_MODE_REG);

	if (!dsaf_get_field(qid_mod, PPE_CFG_QID_MODE_DEF_QID_M,
			    PPE_CFG_QID_MODE_DEF_QID_S)) {
		dsaf_set_field(qid_mod, PPE_CFG_QID_MODE_DEF_QID_M,
			       PPE_CFG_QID_MODE_DEF_QID_S, qid);
		dsaf_write_dev(ppe_common, PPE_COM_CFG_QID_MODE_REG, qid_mod);
	}
}

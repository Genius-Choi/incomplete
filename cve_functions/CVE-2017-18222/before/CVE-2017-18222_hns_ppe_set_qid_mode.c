static void hns_ppe_set_qid_mode(struct ppe_common_cb *ppe_common,
				 enum ppe_qid_mode qid_mdoe)
{
	dsaf_set_dev_field(ppe_common, PPE_COM_CFG_QID_MODE_REG,
			   PPE_CFG_QID_MODE_CF_QID_MODE_M,
			   PPE_CFG_QID_MODE_CF_QID_MODE_S, qid_mdoe);
}

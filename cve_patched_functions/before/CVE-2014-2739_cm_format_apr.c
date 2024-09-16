static void cm_format_apr(struct cm_apr_msg *apr_msg,
			  struct cm_id_private *cm_id_priv,
			  enum ib_cm_apr_status status,
			  void *info,
			  u8 info_length,
			  const void *private_data,
			  u8 private_data_len)
{
	cm_format_mad_hdr(&apr_msg->hdr, CM_APR_ATTR_ID, cm_id_priv->tid);
	apr_msg->local_comm_id = cm_id_priv->id.local_id;
	apr_msg->remote_comm_id = cm_id_priv->id.remote_id;
	apr_msg->ap_status = (u8) status;

	if (info && info_length) {
		apr_msg->info_length = info_length;
		memcpy(apr_msg->info, info, info_length);
	}

	if (private_data && private_data_len)
		memcpy(apr_msg->private_data, private_data, private_data_len);
}

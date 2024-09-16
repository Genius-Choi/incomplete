sess_free_buffer(struct sess_data *sess_data)
{

	free_rsp_buf(sess_data->buf0_type, sess_data->iov[0].iov_base);
	sess_data->buf0_type = CIFS_NO_BUFFER;
	kfree(sess_data->iov[2].iov_base);
}

unix_sck_send_data(hsm_com_client_hdl_t *hdl, int timeout, 
				   hsm_com_datagram_t *send, hsm_com_datagram_t *recv)
{
	hsm_com_msg_t	*msg;
	int total_len;

	msg = (hsm_com_msg_t*)hdl->send_buf;

	msg->common.cmd = HSM_COM_CMD_DATA;
	msg->common.ver = HSM_COM_VER;
	msg->common.trans_id = hdl->trans_id++;
	msg->common.payload_len = send->data_len;

	total_len = sizeof(msg->common) + send->data_len;

	memcpy(&msg->data[0],send->buf,send->data_len);

	if(unix_sck_send_msg(hdl, hdl->send_buf, total_len, hdl->recv_buf, 
						 total_len, timeout) != total_len)
	{

		return HSM_COM_BAD;
	}

	msg = (hsm_com_msg_t*)hdl->recv_buf;
	if(msg->common.resp_code == HSM_COM_RESP_OK){
		memcpy(recv->buf,&msg->data[0],msg->common.payload_len);
		recv->data_len = msg->common.payload_len;
		return HSM_COM_OK;
	}

	return HSM_COM_BAD;

}

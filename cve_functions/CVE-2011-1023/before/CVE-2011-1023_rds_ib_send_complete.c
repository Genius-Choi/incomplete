static void rds_ib_send_complete(struct rds_message *rm,
				 int wc_status,
				 void (*complete)(struct rds_message *rm, int status))
{
	int notify_status;

	switch (wc_status) {
	case IB_WC_WR_FLUSH_ERR:
		return;

	case IB_WC_SUCCESS:
		notify_status = RDS_RDMA_SUCCESS;
		break;

	case IB_WC_REM_ACCESS_ERR:
		notify_status = RDS_RDMA_REMOTE_ERROR;
		break;

	default:
		notify_status = RDS_RDMA_OTHER_ERROR;
		break;
	}
	complete(rm, notify_status);
}

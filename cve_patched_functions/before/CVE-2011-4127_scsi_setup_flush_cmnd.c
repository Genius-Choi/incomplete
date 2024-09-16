static int scsi_setup_flush_cmnd(struct scsi_device *sdp, struct request *rq)
{
	rq->timeout = SD_FLUSH_TIMEOUT;
	rq->retries = SD_MAX_RETRIES;
	rq->cmd[0] = SYNCHRONIZE_CACHE;
	rq->cmd_len = 10;

	return scsi_setup_blk_pc_cmnd(sdp, rq);
}

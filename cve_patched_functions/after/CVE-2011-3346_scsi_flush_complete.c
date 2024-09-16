static void scsi_flush_complete(void * opaque, int ret)
{
    SCSIDiskReq *r = (SCSIDiskReq *)opaque;
    SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, r->req.dev);

    if (r->req.aiocb != NULL) {
        r->req.aiocb = NULL;
        bdrv_acct_done(s->bs, &r->acct);
    }

    if (ret < 0) {
        if (scsi_handle_rw_error(r, -ret, SCSI_REQ_STATUS_RETRY_FLUSH)) {
            return;
        }
    }

    scsi_req_complete(&r->req, GOOD);
}

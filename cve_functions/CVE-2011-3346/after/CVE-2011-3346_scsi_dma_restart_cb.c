static void scsi_dma_restart_cb(void *opaque, int running, int reason)
{
    SCSIDiskState *s = opaque;

    if (!running)
        return;

    if (!s->bh) {
        s->bh = qemu_bh_new(scsi_dma_restart_bh, s);
        qemu_bh_schedule(s->bh);
    }
}

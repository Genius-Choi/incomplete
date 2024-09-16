ar6000_aggr_rcv_delba_req_evt(struct ar6_softc *ar, WMI_DELBA_EVENT *evt)
{
    aggr_recv_delba_req_evt(ar->aggr_cntxt, evt->tid);
}

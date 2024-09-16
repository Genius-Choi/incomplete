dissect_rpcap_heur_tcp (tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data)
{
  if (check_rpcap_heur (tvb, TRUE)) {
    /* This is probably a rpcap tcp package */
    tcp_dissect_pdus (tvb, pinfo, tree, rpcap_desegment, 8,
                      get_rpcap_pdu_len, dissect_rpcap, data);

    return TRUE;
  }

  return FALSE;
}

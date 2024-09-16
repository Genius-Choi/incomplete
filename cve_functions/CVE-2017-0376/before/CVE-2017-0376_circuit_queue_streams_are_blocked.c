circuit_queue_streams_are_blocked(circuit_t *circ)
{
  if (CIRCUIT_IS_ORIGIN(circ)) {
    return circ->streams_blocked_on_n_chan;
  } else {
    return circ->streams_blocked_on_p_chan;
  }
}

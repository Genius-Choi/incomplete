circuit_clear_cell_queue(circuit_t *circ, channel_t *chan)
{
  cell_queue_t *queue;
  cell_direction_t direction;

  if (circ->n_chan == chan) {
    queue = &circ->n_chan_cells;
    direction = CELL_DIRECTION_OUT;
  } else {
    or_circuit_t *orcirc = TO_OR_CIRCUIT(circ);
    tor_assert(orcirc->p_chan == chan);
    queue = &orcirc->p_chan_cells;
    direction = CELL_DIRECTION_IN;
  }

  /* Clear the queue */
  cell_queue_clear(queue);

  /* Update the cell counter in the cmux */
  if (chan->cmux && circuitmux_is_circuit_attached(chan->cmux, circ))
    update_circuit_on_cmux(circ, direction);
}

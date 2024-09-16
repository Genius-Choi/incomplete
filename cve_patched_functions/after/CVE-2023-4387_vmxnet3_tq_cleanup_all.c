vmxnet3_tq_cleanup_all(struct vmxnet3_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_tx_queues; i++)
		vmxnet3_tq_cleanup(&adapter->tx_queue[i], adapter);
}

static int virtcons_freeze(struct virtio_device *vdev)
{
	struct ports_device *portdev;
	struct port *port;

	portdev = vdev->priv;

	vdev->config->reset(vdev);

	virtqueue_disable_cb(portdev->c_ivq);
	cancel_work_sync(&portdev->control_work);
	cancel_work_sync(&portdev->config_work);
	/*
	 * Once more: if control_work_handler() was running, it would
	 * enable the cb as the last step.
	 */
	virtqueue_disable_cb(portdev->c_ivq);
	remove_controlq_data(portdev);

	list_for_each_entry(port, &portdev->ports, list) {
		virtqueue_disable_cb(port->in_vq);
		virtqueue_disable_cb(port->out_vq);
		/*
		 * We'll ask the host later if the new invocation has
		 * the port opened or closed.
		 */
		port->host_connected = false;
		remove_port_data(port);
	}
	remove_vqs(portdev);

	return 0;
}

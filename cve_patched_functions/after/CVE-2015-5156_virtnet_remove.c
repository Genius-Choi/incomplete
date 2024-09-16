static void virtnet_remove(struct virtio_device *vdev)
{
	struct virtnet_info *vi = vdev->priv;

	unregister_hotcpu_notifier(&vi->nb);

	/* Make sure no work handler is accessing the device. */
	flush_work(&vi->config_work);

	unregister_netdev(vi->dev);

	remove_vq_common(vi);

	free_percpu(vi->stats);
	free_netdev(vi->dev);
}

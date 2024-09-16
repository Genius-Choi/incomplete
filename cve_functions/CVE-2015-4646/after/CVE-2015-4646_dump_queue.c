void dump_queue(struct queue *queue)
{
	pthread_mutex_lock(&queue->mutex);

	printf("Max size %d, size %d%s\n", queue->size - 1,  
		queue->readp <= queue->writep ? queue->writep - queue->readp :
			queue->size - queue->readp + queue->writep,
		queue->readp == queue->writep ? " (EMPTY)" :
			((queue->writep + 1) % queue->size) == queue->readp ?
			" (FULL)" : "");

	pthread_mutex_unlock(&queue->mutex);
}

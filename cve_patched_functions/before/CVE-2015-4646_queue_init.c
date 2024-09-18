struct queue *queue_init(int size)
{
	struct queue *queue = malloc(sizeof(struct queue));

	if(queue == NULL)
		EXIT_UNSQUASH("Out of memory in queue_init\n");

	if(add_overflow(size, 1) ||
				multiply_overflow(size + 1, sizeof(void *)))
		EXIT_UNSQUASH("Size too large in queue_init\n");

	queue->data = malloc(sizeof(void *) * (size + 1));
	if(queue->data == NULL)
		EXIT_UNSQUASH("Out of memory in queue_init\n");

	queue->size = size + 1;
	queue->readp = queue->writep = 0;
	pthread_mutex_init(&queue->mutex, NULL);
	pthread_cond_init(&queue->empty, NULL);
	pthread_cond_init(&queue->full, NULL);

	return queue;
}

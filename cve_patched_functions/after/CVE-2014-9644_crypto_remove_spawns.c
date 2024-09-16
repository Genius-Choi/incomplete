void crypto_remove_spawns(struct crypto_alg *alg, struct list_head *list,
			  struct crypto_alg *nalg)
{
	u32 new_type = (nalg ?: alg)->cra_flags;
	struct crypto_spawn *spawn, *n;
	LIST_HEAD(secondary_spawns);
	struct list_head *spawns;
	LIST_HEAD(stack);
	LIST_HEAD(top);

	spawns = &alg->cra_users;
	list_for_each_entry_safe(spawn, n, spawns, list) {
		if ((spawn->alg->cra_flags ^ new_type) & spawn->mask)
			continue;

		list_move(&spawn->list, &top);
	}

	spawns = &top;
	do {
		while (!list_empty(spawns)) {
			struct crypto_instance *inst;

			spawn = list_first_entry(spawns, struct crypto_spawn,
						 list);
			inst = spawn->inst;

			BUG_ON(&inst->alg == alg);

			list_move(&spawn->list, &stack);

			if (&inst->alg == nalg)
				break;

			spawn->alg = NULL;
			spawns = &inst->alg.cra_users;
		}
	} while ((spawns = crypto_more_spawns(alg, &stack, &top,
					      &secondary_spawns)));

	list_for_each_entry_safe(spawn, n, &secondary_spawns, list) {
		if (spawn->alg)
			list_move(&spawn->list, &spawn->alg->cra_users);
		else
			crypto_remove_spawn(spawn, list);
	}
}

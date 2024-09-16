static Reinst *emit(Reprog *prog, int opcode)
{
	Reinst *inst = prog->end++;
	inst->opcode = opcode;
	inst->n = 0;
	inst->c = 0;
	inst->cc = NULL;
	inst->x = inst->y = NULL;
	return inst;
}

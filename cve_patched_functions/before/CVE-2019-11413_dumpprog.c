static void dumpprog(Reprog *prog)
{
	Reinst *inst;
	int i;
	for (i = 0, inst = prog->start; inst < prog->end; ++i, ++inst) {
		printf("% 5d: ", i);
		switch (inst->opcode) {
		case I_END: puts("end"); break;
		case I_JUMP: printf("jump %d\n", (int)(inst->x - prog->start)); break;
		case I_SPLIT: printf("split %d %d\n", (int)(inst->x - prog->start), (int)(inst->y - prog->start)); break;
		case I_PLA: printf("pla %d %d\n", (int)(inst->x - prog->start), (int)(inst->y - prog->start)); break;
		case I_NLA: printf("nla %d %d\n", (int)(inst->x - prog->start), (int)(inst->y - prog->start)); break;
		case I_ANY: puts("any"); break;
		case I_ANYNL: puts("anynl"); break;
		case I_CHAR: printf(inst->c >= 32 && inst->c < 127 ? "char '%c'\n" : "char U+%04X\n", inst->c); break;
		case I_CCLASS: puts("cclass"); break;
		case I_NCCLASS: puts("ncclass"); break;
		case I_REF: printf("ref %d\n", inst->n); break;
		case I_BOL: puts("bol"); break;
		case I_EOL: puts("eol"); break;
		case I_WORD: puts("word"); break;
		case I_NWORD: puts("nword"); break;
		case I_LPAR: printf("lpar %d\n", inst->n); break;
		case I_RPAR: printf("rpar %d\n", inst->n); break;
		}
	}
}

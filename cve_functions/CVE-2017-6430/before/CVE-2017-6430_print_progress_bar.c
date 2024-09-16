static void print_progress_bar(struct filter_op *fop)
{
   switch(fop->opcode) {
      case FOP_EXIT:
         ef_debug(1, "!");
         break;
      case FOP_TEST:
         ef_debug(1, "?");
         break;
      case FOP_ASSIGN:
         ef_debug(1, "=");
         break;
      case FOP_FUNC:
         ef_debug(1, ".");
         break;
      case FOP_JMP:
         ef_debug(1, ":");
         break;
      case FOP_JTRUE:
      case FOP_JFALSE:
         ef_debug(1, ";");
         break;
   }
}

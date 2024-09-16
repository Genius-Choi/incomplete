static void emitfunction(JF, js_Function *fun)
{
	F->lightweight = 0;
	emit(J, F, OP_CLOSURE);
	emitarg(J, F, addfunction(J, F, fun));
}

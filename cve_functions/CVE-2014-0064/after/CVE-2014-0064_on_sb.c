on_sb(PG_FUNCTION_ARGS)
{
	LSEG	   *lseg = PG_GETARG_LSEG_P(0);
	BOX		   *box = PG_GETARG_BOX_P(1);

	PG_RETURN_BOOL(DatumGetBool(DirectFunctionCall2(on_pb,
												 PointPGetDatum(&lseg->p[0]),
													BoxPGetDatum(box))) &&
				   DatumGetBool(DirectFunctionCall2(on_pb,
												 PointPGetDatum(&lseg->p[1]),
													BoxPGetDatum(box))));
}

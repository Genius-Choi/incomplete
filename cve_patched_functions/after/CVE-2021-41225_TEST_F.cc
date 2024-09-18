TEST_F(AutoParallelTest, SimpleParallelNoDequeue) {
  tensorflow::Scope s = tensorflow::Scope::DisabledShapeInferenceScope();
  Output constant_a = ops::Const(s.WithOpName("constant_a"), 1.0f, {1});
  Output constant_c = ops::Const(s.WithOpName("constant_c"), 1.0f, {1});
  Output constant_b = ops::Const(s.WithOpName("constant_b"), 1, {1});
  Output var = ops::Variable(s.WithOpName("var"), {1}, DT_FLOAT);
  Output assign = ops::Assign(s.WithOpName("assign"), {var}, {constant_a});
  Output add = ops::AddN(s.WithOpName("add"), {constant_a, constant_c});
  Output learning_rate = ops::Const(s.WithOpName("learning_rate"), 0.01f, {1});
  Output apply_gradient = ops::ApplyGradientDescent(
      s.WithOpName("apply_gradient"), {var}, {learning_rate}, {add});

  GrapplerItem item;
  item.init_ops.push_back("assign");
  item.fetch.push_back("apply_gradient");
  item.init_ops.push_back("assign");
  TF_CHECK_OK(s.ToGraphDef(&item.graph));

  AutoParallel parallel(2);
  GraphDef output;
  Status status = parallel.Optimize(nullptr, item, &output);
  TF_EXPECT_OK(status);
}

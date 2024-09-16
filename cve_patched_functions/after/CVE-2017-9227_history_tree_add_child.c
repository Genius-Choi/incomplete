history_tree_add_child(OnigCaptureTreeNode* parent, OnigCaptureTreeNode* child)
{
#define HISTORY_TREE_INIT_ALLOC_SIZE  8

  if (parent->num_childs >= parent->allocated) {
    int n, i;

    if (IS_NULL(parent->childs)) {
      n = HISTORY_TREE_INIT_ALLOC_SIZE;
      parent->childs =
        (OnigCaptureTreeNode** )xmalloc(sizeof(OnigCaptureTreeNode*) * n);
    }
    else {
      n = parent->allocated * 2;
      parent->childs =
        (OnigCaptureTreeNode** )xrealloc(parent->childs,
                                         sizeof(OnigCaptureTreeNode*) * n);
    }
    CHECK_NULL_RETURN_MEMERR(parent->childs);
    for (i = parent->allocated; i < n; i++) {
      parent->childs[i] = (OnigCaptureTreeNode* )0;
    }
    parent->allocated = n;
  }

  parent->childs[parent->num_childs] = child;
  parent->num_childs++;
  return 0;
}


int fun9(int *param_1,int param_2)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    iVar1 = -1;
  }
  else {
    if (param_2 < *param_1) {
      iVar1 = fun9(param_1[1],param_2);
      iVar1 = iVar1 * 2;
    }
    else {
      iVar1 = 0;
      if (*param_1 != param_2) {
        iVar1 = fun9(param_1[2],param_2);
        iVar1 = iVar1 * 2 + 1;
      }
    }
  }
  return iVar1;
}


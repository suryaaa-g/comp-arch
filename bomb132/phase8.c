
void phase_8(undefined4 param_1)

{
  int *piVar1;
  undefined1 *puVar2;
  int **ppiVar3;
  int iVar4;
  int **ppiVar5;
  int in_GS_OFFSET;
  int local_60;
  int *local_50 [6];
  int *local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  
  local_20 = *(int *)(in_GS_OFFSET + 0x14);
  read_six_numbers(param_1,local_50);
  ppiVar5 = local_50;
  local_60 = 0;
  while( true ) {
    ppiVar5 = ppiVar5 + 1;
    if (5 < (int)ppiVar5[-1] - 1U) {
                    /* WARNING: Subroutine does not return */
      explode_bomb();
    }
    local_60 = local_60 + 1;
    ppiVar3 = ppiVar5;
    if (5 < local_60) break;
    do {
      if (ppiVar5[-1] == *ppiVar3) {
                    /* WARNING: Subroutine does not return */
        explode_bomb();
      }
      ppiVar3 = ppiVar3 + 1;
    } while (&local_38 != ppiVar3);
  }
  iVar4 = 0;
  do {
    piVar1 = (int *)0x1;
    puVar2 = node1;
    if (1 < (int)local_50[iVar4]) {
      do {
        puVar2 = *(undefined1 **)((int)puVar2 + 8);
        piVar1 = (int *)((int)piVar1 + 1);
      } while (piVar1 != local_50[iVar4]);
    }
    (&local_38)[iVar4] = (int *)puVar2;
    iVar4 = iVar4 + 1;
  } while (iVar4 != 6);
  local_38[2] = local_34;
  *(int *)(local_34 + 8) = local_30;
  *(int *)(local_30 + 8) = local_2c;
  *(int *)(local_2c + 8) = local_28;
  *(int *)(local_28 + 8) = local_24;
  *(undefined4 *)(local_24 + 8) = 0;
  iVar4 = 5;
  do {
    if (*local_38 != *(int *)local_38[2] && *(int *)local_38[2] <= *local_38) {
                    /* WARNING: Subroutine does not return */
      explode_bomb();
    }
    local_38 = (int *)local_38[2];
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if (local_20 == *(int *)(in_GS_OFFSET + 0x14)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


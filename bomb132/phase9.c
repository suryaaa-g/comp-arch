
void phase_9(char *param_1)

{
  long lVar1;
  int iVar2;
  
  lVar1 = strtol(param_1,(char **)0x0,10);
  if (1000 < lVar1 - 1U) {
                    /* WARNING: Subroutine does not return */
    explode_bomb();
  }
  iVar2 = fun9(n1,lVar1);
  if (iVar2 == 3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  explode_bomb();
}


/*
779
I warned you about stairs, bro!
Bigfoon stole my car, with my friend's birthday present in it!
.sgniht etalucitrani ,raelcnu ot sdael ytisobreV
5
5 2
5 115
6 4 3 5 2 1
90


*/
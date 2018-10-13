void numericDef(int val, int team) {
  int val1 = (val / 100) % 10;
  int val2 = (val / 10) % 10;
  int val3 = val % 10;

  if(team == 0){
    homeScr.setAllLow();
  }else if(team == 1){
    awayScr.setAllLow();
  }

  if(val > 99){
    slctDigit(val1,2,team); //value, which digit, team
  }

  if(val >9){
    slctDigit(val2,1,team);
  }

  slctDigit(val3,0,team);

}

void slctDigit(int val,int dgt, int team){

   switch (val) {
    case 0:
      accessDef(zeroDef, 6, dgt, team);
      break;

    case 1:
      accessDef(oneDef, 2, dgt, team);
      break;

    case 2:
      accessDef(twoDef, 5, dgt, team);
      break;

    case 3:
      accessDef(threeDef, 5, dgt, team);
      break;

    case 4:
      accessDef(fourDef, 4, dgt, team);
      break;

    case 5:
      accessDef(fiveDef, 5, dgt, team);
      break;

    case 6:
      accessDef(sixDef, 6, dgt, team);
      break;

    case 7:
      accessDef(sevenDef, 3, dgt, team);
      break;

    case 8:
      accessDef(eightDef, 7, dgt, team);
      break;

    case 9:
      accessDef(nineDef, 5, dgt, team);
      break;

    default:
      break;
  }
}

void accessDef(int defin[], int maxSize, int digitSlct, int team) {
  for (int slct = 0; slct < maxSize; slct++) {
    int thisPin = defin[slct];
    if(digitSlct == 1){
      thisPin+=7;
    }else if(digitSlct == 2){
      thisPin+=14;
    }
    if(team == 0){
      homeScr.setNoUpdate(thisPin, HIGH);
    }else if(team == 1){
      awayScr.setNoUpdate(thisPin, HIGH);
    }
  }
}


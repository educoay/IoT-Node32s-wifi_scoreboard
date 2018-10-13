void handleRoot() {
  server.send(200, "text/html", html);
}

void handleNotFound() {
  String message = "File Not Found\n\n\n\n";
  server.send(404, "text/plain", message);
}

void handleGPIO(){
  Serial.println("got request");
  if (server.args() > 0) {
    String req = server.argName(0);
    Serial.print("req: ");
    Serial.println(req);

     if(req.indexOf("home") != -1){
      if(req.indexOf("rst") == -1){
        homeScore = checkReq(req);
        numericDef(homeScore,0);
        homeScr.updateRegisters();
      }
      updtHTMLScores(homeScore);
    }else if(req.indexOf("away") != -1){
      if(req.indexOf("rst") == -1){
        awayScore = checkReq(req);
        numericDef(awayScore,1);
        awayScr.updateRegisters();
      }
      updtHTMLScores(awayScore);
    }
  }
}

int checkReq(String reqArg){
    int reqScore = (reqArg.indexOf("home") != -1) ? homeScore : awayScore;
    if(reqArg.indexOf("-set") != -1){
      if(reqArg.length() > 9){
        reqScore = reqArg.substring(9,reqArg.length()).toInt();
      }else{
        reqScore = 0;
      }
    }else if(reqArg == "-rst"){
      reqScore = 0;
    }else if(reqArg.indexOf("-minus") != -1){
      reqScore -= reqArg.substring(11,reqArg.length()).toInt();
    }else if(reqArg.indexOf("-plus") != -1){
      reqScore += reqArg.substring(10,reqArg.length()).toInt();
    }

    if(reqScore < 0){
      reqScore = 0;
    }else if(reqScore > 999){
      reqScore = 999;
    }

    return reqScore;
}

void updtHTMLScores(int score){
    char thsScr[3];
    sprintf(thsScr, "%d", score);
    server.send(200, "text/plain", thsScr);
}


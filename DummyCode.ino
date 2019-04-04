//Pseudocode for purposes of working out the loop structure
var pos; // Some custom class or variable for tracking last known enemy location
final int COMBAT_DISTANCE; //Distance cutoff for engagement logic - Needs to be set


void setup() {
  var pos = new pos(); // initialize pos
  wait(5); //Regulation waiting
}

void loop() {
  pos = searchLoop();
  if (pos.getDist() <= COMBAT_DISTANCE){
    engage(pos);
  }
  else {
    switch (pos.getSide()){ //getSide will need to return an enum with each of the 4 sides the enemy bot is on/was on
      case side.FRONT:
        moveToEngage(Pos);
        break;
      case side.BACK:
        evasiveTurn();
        break;
      case side.RIGHT:
      case side.LEFT:
        zeroDegreeTurn(pos.getSide());
        break;
  }
}

pos searchLoop(){
  pos x;
  while (true) {
    pos x;
    if ( FRONT_SENSOR1.blocked() ){
      x = new Pos(FRONT_SENSOR1.getInfo(), FRONT_SENSOR2.getInfo());
      return x;
    }
    else if ( FRONT_SENSOR2.blocked() ){
      x = new Pos(FRONT_SENSOR2.getInfo(), FRONT_SENSOR2.getInfo());
      return x;
    }
    else if ( SIDE_SENSOR1.blocked() ){
      x = new Pos(SIDE_SENSOR1.getInfo());
      return x;
    }
    else if ( SIDE_SENSOR2.blocked() ){
      x = new Pos(SIDE_SENSOR2.getInfo());
      return x;
    }
    else if ( BACK_SESNSOR.blocked() ){
      x = new Pos(BACK_SENSOR.getInfo());
      return x;
    }
  
    pos lastKnown = pos;
  
    switch (lastKnown.getSide()){ //getSide will need to return an enum with each of the 4 sides the enemy bot is on/was on
        case side.FRONT:
          if (lastKnown.getF1Dist() >= lastKnown.getF2Dist()) {
            turnToFaceRight();
          else
            turnToFaceLeft();
          break;
        case side.BACK:
          backTurn();
          break;
        case side.RIGHT:
        case side.LEFT:
          frontTurn(lastKnown.getSide());
          break;
    }
  }
}

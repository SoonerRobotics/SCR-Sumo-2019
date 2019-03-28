//Pseudocode for purposes of working out the loop structure
var pos; // Some custom class or variable for tracking last known enemy location
final int COMBAT_DISTANCE;


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

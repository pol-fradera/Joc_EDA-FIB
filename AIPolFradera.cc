#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME PolFradera


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }
  
  /**
   * Types and attributes for your player can be defined here.
   */

  typedef vector<int> VI;

  void move_units() {
    Pos p0 = Pos(rows()/2,cols()/2);
    VI U = my_units(me());
    int n = U.size();
    for (int i = 0; i < n; ++i) {
      int id = U[i];
      Unit u = unit(id);
      if (u.pos < p0) {
        move(id, BOTTOM);
      }
      else move(id, TOP);
    }
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    move_units();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

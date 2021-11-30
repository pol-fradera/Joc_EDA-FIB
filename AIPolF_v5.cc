#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME PolF_v5


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

  bool ataca_fuig(Unit& u) {
    Cell c1 = cell(u.pos+TOP);
    if (c1.unit_id != -1) {
      Unit u1 = unit(c1.unit_id);
      if (u1.player != me()) {
        if (u1.health <= u.health) move(u.id, TOP);
        else move(u.id, BOTTOM);
        return true;
      }
    }
    Cell c2 = cell(u.pos+BOTTOM);
    if (c2.unit_id != -1) {
      Unit u2 = unit(c2.unit_id);
      if (u2.player != me()) {
        if (u2.health <= u.health) move(u.id, BOTTOM);
        else move(u.id, TOP);
        return true;
      }
    } 
    Cell c3 = cell(u.pos+RIGHT);
    if (c3.unit_id != -1) {
      Unit u3 = unit(c3.unit_id);
      if (u3.player != me()) {
        if (u3.health <= u.health) move(u.id, RIGHT);
        else move(u.id, LEFT);
        return true;
      }
    }
    Cell c4 = cell(u.pos+LEFT);
    if (c4.unit_id != -1) {
      Unit u4 = unit(c4.unit_id);
      if (u4.player != me()) {
        if (u4.health <= u.health) move(u.id, LEFT);
        else move(u.id, RIGHT);
        return true;
      }
    }
    return false;
  }

  bool entra_ciutat_cami(Unit& u){
    Cell c1 = cell(u.pos+TOP);
    if (c1.unit_id == -1) {
      if (c1.type == CITY or c1.type == PATH) {
        move(u.id, TOP);
        return true;
      }
    }
    Cell c2 = cell(u.pos+BOTTOM);
    if (c2.unit_id == -1) {
      if (c2.type == CITY or c2.type == PATH) {
        move(u.id, BOTTOM);
        return true;
      }
    } 
    Cell c3 = cell(u.pos+RIGHT);
    if (c3.unit_id == -1) {
      if (c3.type == CITY or c3.type == PATH) {
        move(u.id, RIGHT);
        return true;
      }
    }
    Cell c4 = cell(u.pos+LEFT);
    if (c4.unit_id == -1) {
      if (c4.type == CITY or c4.type == PATH) {
        move(u.id, LEFT);
        return true;
      }
    }
    return false;
  }

  bool mascareta(Unit& u){
    Cell c1 = cell(u.pos+TOP);
    if (c1.unit_id == -1 and c1.mask) {
        move(u.id, TOP);
        return true;
    }
    Cell c2 = cell(u.pos+BOTTOM);
    if (c2.unit_id == -1 and c2.mask) {
        move(u.id, TOP);
        return true;
    }
    Cell c3 = cell(u.pos+RIGHT);
    if (c3.unit_id == -1 and c3.mask) {
        move(u.id, TOP);
        return true;
    }
    Cell c4 = cell(u.pos+LEFT);
    if (c4.unit_id == -1 and c4.mask) {
        move(u.id, TOP);
        return true;
    }
    return false;
  }

  void move_units() {
    Pos mid = Pos(rows()/2,cols()/2);
    VI U = my_units(me());
    int n = U.size();
    for (int i = 0; i < n; ++i) {
      int id = U[i];
      Unit u = unit(id);
      Pos p0 = u.pos;
      Cell c = cell(p0);
      if (not ataca_fuig(u)) {
        if (not mascareta(u)) {
        //if (c.type == CITY or c.type == PATH) move(id, NONE);
          if (not entra_ciutat_cami(u)) {
            if ((p0.i == rows()/2 or p0.i == rows()/2-1) and p0.j < cols()/2) move(id,RIGHT);
            else if ((p0.i == rows()/2 or p0.i == rows()/2-1) and p0.j > cols()/2) move(id,LEFT);
            else if (p0 < mid) {
            move(id, BOTTOM);
            }
            else move(id, TOP);
          }
        }
      }
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

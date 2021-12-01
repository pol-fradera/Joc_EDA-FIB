#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME PolF_v9


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
  typedef vector<VI>  VVI;

  typedef vector<Cell> VC;
  typedef vector<VC> VVC;

  int files = rows();
  int columnes = cols();
  VVC mapa = VVC(files, VC(columnes));

  void llegir_mapa() {
    for (int i = 0; i < files; ++i) {
      for (int j = 0; j < columnes; ++j) {
        Cell c = cell(i,j);
        mapa[i][j] = c;
      }
    }
  }

  Pos func_bfs(const VVC& mapa, Pos origen) {
    queue<Pos> q;
    map<Pos,Pos> m;
    bool meva_unitat = false;
    //vector<bool> trob(files*columnes,false);
    q.push(origen);
    m[origen] = origen;
    while (not q.empty()) {
      Pos actual = q.front();
      Cell c = cell(actual);
      if (c.unit_id != -1) {
        Unit u = unit(c.unit_id);
        if (u.player == me()) meva_unitat = true;
        else meva_unitat = false;
      }
      else meva_unitat = false;      
      q.pop();
      if ((c.type == CITY and city_owner(c.city_id) != me() and not meva_unitat) or (c.type == PATH and path_owner(c.path_id) != me() and not meva_unitat)) {
        Pos dest = actual;
        while (m[dest] != origen) {
          dest = m[dest];
        }
        return dest;
      }
      for (int i = 0; i < 4; ++i) {
        Pos u = actual+Dir(i);
        Cell c1 = cell(u);
        if (c1.type != WALL and m.find(u) == m.end()) {
          q.push(u);
          m[u] = actual;
        }
      }
    }
  }

  bool ataca(Unit& u) {
    Cell c1 = cell(u.pos+TOP);
    if (c1.unit_id != -1) {
      Unit u1 = unit(c1.unit_id);
      if (u1.player != me()) {
        move(u.id, TOP);
        return true;
      }
    }
    Cell c2 = cell(u.pos+BOTTOM);
    if (c2.unit_id != -1) {
      Unit u2 = unit(c2.unit_id);
      if (u2.player != me()) {
        move(u.id, BOTTOM);
        return true;
      }
    } 
    Cell c3 = cell(u.pos+RIGHT);
    if (c3.unit_id != -1) {
      Unit u3 = unit(c3.unit_id);
      if (u3.player != me()) {
        move(u.id, RIGHT);
        return true;
      }
    }
    Cell c4 = cell(u.pos+LEFT);
    if (c4.unit_id != -1) {
      Unit u4 = unit(c4.unit_id);
      if (u4.player != me()) {
        move(u.id, LEFT);
        return true;
      }
    }
    return false;
  }

  

  /*bool cela_virus(Unit& u) {
    Cell c = cell(u.pos);
    if (u.damage == 0 and c.virus > 0) {
      Cell c1 = cell(u.pos + TOP);
      Cell c2 = cell(u.pos + BOTTOM);
      Cell c3 = cell(u.pos + RIGHT);
      Cell c4 = cell(u.pos + LEFT);
      if (c1.type == GRASS) {
        move(u.id, TOP);
        return true;
      }
      if (c2.type == GRASS) {
        move(u.id, BOTTOM);
        return true;
      }
      if (c3.type == GRASS) {
        move(u.id, RIGHT);
        return true;
      }
      if (c4.type == GRASS) {
        move(u.id, LEFT);
        return true;
      }     
    }
    return false;
  }*/

  bool mascareta(Unit& u){
    Cell c1 = cell(u.pos+TOP);
    if (c1.unit_id == -1 and c1.mask) {
        move(u.id, TOP);
        return true;
    }
    Cell c2 = cell(u.pos+BOTTOM);
    if (c2.unit_id == -1 and c2.mask) {
        move(u.id, BOTTOM);
        return true;
    }
    Cell c3 = cell(u.pos+RIGHT);
    if (c3.unit_id == -1 and c3.mask) {
        move(u.id, RIGHT);
        return true;
    }
    Cell c4 = cell(u.pos+LEFT);
    if (c4.unit_id == -1 and c4.mask) {
        move(u.id, LEFT);
        return true;
    }
    return false;
  }

  void move_units() {
    //Pos mid = Pos(rows()/2,cols()/2);
    VI U = my_units(me());
    int n = U.size();
    for (int i = 0; i < n; ++i) {
      int id = U[i];
      Unit u = unit(id);
      //Pos p0 = u.pos;
      if (not ataca(u)) {
        if (not mascareta(u)) {
        //if (c.type == CITY or c.type == PATH) move(id, NONE);
          //if (not cela_virus(u)) {
          Pos p1 = func_bfs(mapa, u.pos);
          if (p1.i < u.pos.i) move(id, TOP);
          else if (p1.i > u.pos.i) move(id, BOTTOM);
          else if (p1.j < u.pos.j) move(id, LEFT);
          else if (p1.j > u.pos.j) move(id, RIGHT);
        }
      }
    }
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    if (nb_rounds() == 0) llegir_mapa();
    move_units();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
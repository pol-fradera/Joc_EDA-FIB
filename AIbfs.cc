#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME bfs


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
    //vector<bool> trob(files*columnes,false);
    q.push(origen);
    m.insert(origen,origen);
    while (not q.empty()) {
      Pos actual = q.front();
      Cell c = cell(actual);
      q.pop();
      if (c.type == CITY) {
        while ()
        return m[actual];
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

  void move_units() {
    //Pos p0 = Pos(rows()/2,cols()/2);
    VI U = my_units(me());
    int n = U.size();
    for (int i = 0; i < n; ++i) {
      int id = U[i];
      Unit u = unit(id);
      Pos p1 = func_bfs(mapa, u.pos);
      if (p1.i < u.pos.i) move(id, TOP);
      else if (p1.i > u.pos.i) move(id, BOTTOM);
      else if (p1.j < u.pos.j) move(id, LEFT);
      else if (p1.j > u.pos.j) move(id, RIGHT);
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

#pragma once
class Mouse {
 private:
  int x;
  int y;

 public:
  Mouse();
  ~Mouse();
  void mouseTo(int x, int y);
  int getX() { return x; }
  int getY() { return y; }
};

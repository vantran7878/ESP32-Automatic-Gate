struct Led {
  int red_pin;
  int green_pin;
  int duration = 0;

  Led(int red, int green);
  void init();
  void light_red();
  void light_green();
  void no_light();
};
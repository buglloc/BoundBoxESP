#ifndef GUI_H
#define GUI_H

class TGUI
{
public:
  static TGUI& Create();
private:
  TGUI() = default;
};

#endif
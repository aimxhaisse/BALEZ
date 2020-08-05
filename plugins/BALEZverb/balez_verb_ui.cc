#include "DistrhoUI.hpp"

START_NAMESPACE_DISTRHO

using DGL_NAMESPACE::Rectangle;

class BALEZVerbUI : public UI {
public:
  BALEZVerbUI() : UI(512, 512) {}

  void parameterChanged(uint32_t index, float value) {}
  void onDisplay() {}
  void programLoaded(uint32_t index) {}
};

UI *createUI() { return new BALEZVerbUI(); }

END_NAMESPACE_DISTRHO

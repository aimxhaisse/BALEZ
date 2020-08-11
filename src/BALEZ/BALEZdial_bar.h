#pragma once

#include <map>

#include "BALEZdial.h"
#include "BALEZprocessor_base.h"

// A generic class to store a horizontal bar of dials.
class BalezDialBar {
public:
  BalezDialBar();

  BalezDial &addNewDial(juce::String name, int index);
  BalezDial &getDial(int index);

  void setInitialPosition(int x, int y);
  void setUp(juce::AudioProcessorEditor &editor);
  void resized();

private:
  std::map<int, std::unique_ptr<BalezDial>> dials_;
};

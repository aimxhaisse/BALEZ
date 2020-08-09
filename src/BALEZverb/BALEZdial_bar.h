#pragma once

#include <map>

#include "BALEZdial.h"

// A generic class to store a horizontal bar of dials.
class BalezDialBar {
public:
  BalezDialBar();

  BalezDial &addNewDial(juce::String name, int index);
  BalezDial &getDial(int index);

  void setInitialPosition(int x, int y);
  void setUp(juce::AudioProcessorEditor *proc);
  void resized();

private:
  std::map<int, std::unique_ptr<BalezDial>> dials_;
};

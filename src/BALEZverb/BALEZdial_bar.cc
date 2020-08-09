#include "BALEZdial_bar.h"

BalezDialBar::BalezDialBar() {}

BalezDial &BalezDialBar::addNewDial(juce::String name, int index) {
  BalezDial &dial =
      *(dials_.insert(std::make_pair(index, std::make_unique<BalezDial>(name)))
            .first->second);

  dial.setIndex(index);

  return dial;
}

BalezDial &BalezDialBar::getDial(int index) {
  return *(dials_.find(index)->second);
}

void BalezDialBar::setUp(juce::AudioProcessorEditor *proc) {
  for (auto &iter : dials_) {
    iter.second->setUp(proc);
  }
}

void BalezDialBar::resized() {
  for (auto &iter : dials_) {
    iter.second->resized();
  }
}

void BalezDialBar::setInitialPosition(int x, int y) {
  for (auto &iter : dials_) {
    iter.second->setInitialPosition(x, y);
  }
}

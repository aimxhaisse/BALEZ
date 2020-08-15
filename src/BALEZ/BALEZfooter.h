#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "BALEZ/BALEZconstants.h"

class BalezFooter {
public:
  static constexpr int getHeight() { return kFooterHeight; }

  void setUp(juce::AudioProcessorEditor &editor);
  void resized();

private:
  juce::DrawableText footer_;
};

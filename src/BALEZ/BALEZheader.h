#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "BALEZ/BALEZconstants.h"

class BalezHeader {
public:
  static constexpr int getHeight() { return kHeaderHeight; }

  void setUp(juce::AudioProcessorEditor &editor, const juce::String &name);
  void resized();

private:
  juce::DrawableText header_;
};

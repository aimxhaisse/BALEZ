#pragma once

#include "BALEZverb_processor.h"

class BalezVerbEditor : public juce::AudioProcessorEditor {
public:
  explicit BalezVerbEditor(BalezVerbProcessor &proc);
  ~BalezVerbEditor() override;

  void paint(juce::Graphics &gfx) override;
  void resized() override;

private:
  void paintBuildDate(juce::Graphics &gfx);

  BalezVerbProcessor &proc_;
};

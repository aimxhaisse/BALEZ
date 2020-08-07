#pragma once

#include "BALEZverb_processor.h"

class BalezVerbEditor : public juce::AudioProcessorEditor {
public:
  explicit BalezVerbEditor(BalezVerbProcessor &);
  ~BalezVerbEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  BalezVerbProcessor &proc_;
};

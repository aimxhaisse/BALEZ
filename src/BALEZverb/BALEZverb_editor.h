#pragma once

#include <memory>
#include <utility>

#include "BALEZ/BALEZdial_bar.h"
#include "BALEZverb_processor.h"

class BalezVerbEditor : public juce::AudioProcessorEditor {
public:
  explicit BalezVerbEditor(BalezVerbProcessor &proc);
  ~BalezVerbEditor() override;

  void paint(juce::Graphics &gfx) override;
  void resized() override;

private:
  juce::DrawableText header_;
  BalezDialBar dial_bar_;
  juce::DrawableText footer_;

  BalezVerbProcessor &proc_;
};

#pragma once

#include "BALEZverb_processor.h"

class BalezVerbEditor : public juce::AudioProcessorEditor,
                        public juce::Slider::Listener {
public:
  explicit BalezVerbEditor(BalezVerbProcessor &proc);
  ~BalezVerbEditor() override;

  void paint(juce::Graphics &gfx) override;
  void resized() override;
  void sliderValueChanged(juce::Slider *slider) override;

  static constexpr int kDialCount = 6;

private:
  juce::DrawableText header_;
  juce::DrawableText footer_;

  juce::Slider dials_[kDialCount];
  juce::DrawableText descriptions_[kDialCount];
  float values_[kDialCount];

  BalezVerbProcessor &proc_;
};

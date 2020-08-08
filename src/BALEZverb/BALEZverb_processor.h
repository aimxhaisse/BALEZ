#pragma once

#include "BALEZprocessor_base.h"

class BalezVerbProcessor : public BalezProcessorBase {
public:
  BalezVerbProcessor();
  ~BalezVerbProcessor() override;

  const juce::String getName() const override;
  juce::AudioProcessorEditor *createEditor() override;

  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;
  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
  void setParameters(const juce::Reverb::Parameters &params);

private:
  static constexpr int kNumberChans = 2;

  juce::Reverb reverbs_[kNumberChans];
};

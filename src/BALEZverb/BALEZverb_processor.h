#pragma once

#include <mutex>

#include "BALEZprocessor_base.h"

enum {
  PARAM_ROOM = 0,
  PARAM_DAMPING = 1,
  PARAM_WET = 2,
  PARAM_DRY = 3,
  PARAM_WIDTH = 4,
  PARAM_FREEZE = 5
};

constexpr int kParamCount = 6;

class BalezVerbProcessor : public BalezProcessorBase {
public:
  BalezVerbProcessor();
  ~BalezVerbProcessor() override;

  const juce::String getName() const override;
  juce::AudioProcessorEditor *createEditor() override;

  void reloadParameters();
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;
  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
  void parameterValueChanged(int idx, float value) override;

private:
  static constexpr int kNumberChans = 2;

  juce::Reverb reverbs_[kNumberChans];
};

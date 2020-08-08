#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class BalezProcessorBase : public juce::AudioProcessor {
public:
  BalezProcessorBase(const BusesProperties &layouts)
      : juce::AudioProcessor(layouts) {}

  bool hasEditor() const override { return true; }
  bool acceptsMidi() const override { return false; }
  bool producesMidi() const override { return false; }
  bool isMidiEffect() const override { return false; }

  double getTailLengthSeconds() const override { return 0.0; }

  int getNumPrograms() override { return 1; }
  int getCurrentProgram() override { return 0; }
  void setCurrentProgram(int) override {}
  const juce::String getProgramName(int) override { return {}; }
  void changeProgramName(int, const juce::String &) override {}

  void getStateInformation(juce::MemoryBlock &destData) override {}
  void setStateInformation(const void *data, int sizeInBytes) override {}
};

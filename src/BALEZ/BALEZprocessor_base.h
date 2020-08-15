#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class BalezProcessorBase : public juce::AudioProcessor,
                           public juce::AudioProcessorParameter::Listener {
public:
  BalezProcessorBase(const BusesProperties &layouts);

  bool hasEditor() const override;
  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;

  double getTailLengthSeconds() const override;

  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int) override;
  const juce::String getProgramName(int) override;
  void changeProgramName(int, const juce::String &) override;

  void getStateInformation(juce::MemoryBlock &dest) override;
  void setStateInformation(const void *data, int size) override;

  void parameterValueChanged(int idx, float value) override;
  void parameterGestureChanged(int idx, bool gesture) override;

  float getParameterValue(int index);
  void setParameterValue(int index, float value);
};

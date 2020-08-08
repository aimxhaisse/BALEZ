#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class BalezVerbProcessor : public juce::AudioProcessor {
public:
  BalezVerbProcessor();
  ~BalezVerbProcessor() override;

  const juce::String getName() const override;

  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

  // Editor.
  juce::AudioProcessorEditor *createEditor() override;
  bool hasEditor() const override;

  // Midi config.
  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;

  double getTailLengthSeconds() const override;

  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

private:
  static constexpr int kNumberChans = 2;

  juce::Reverb reverbs_[kNumberChans];
};

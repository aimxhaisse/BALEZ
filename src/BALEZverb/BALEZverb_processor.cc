#include <juce_audio_basics/juce_audio_basics.h>

#include "BALEZverb_editor.h"
#include "BALEZverb_processor.h"

BalezVerbProcessor::BalezVerbProcessor()
    : BalezProcessorBase(
          BusesProperties()
              .withInput("Input", juce::AudioChannelSet::stereo())
              .withOutput("Output", juce::AudioChannelSet::stereo())
              .withInput("Sidechain", juce::AudioChannelSet::stereo())) {}

BalezVerbProcessor::~BalezVerbProcessor() {}

const juce::String BalezVerbProcessor::getName() const {
  return JucePlugin_Name;
}

void BalezVerbProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
  for (int i = 0; i < kNumberChans; ++i) {
    reverbs_[i].setSampleRate(sampleRate);
  }
}

void BalezVerbProcessor::releaseResources() {
  for (int i = 0; i < kNumberChans; ++i) {
    reverbs_[i].reset();
  }
}

bool BalezVerbProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
  if (layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo()) {
    return true;
  }

  return false;
}

void BalezVerbProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                      juce::MidiBuffer &midi_msgs) {
  juce::ignoreUnused(midi_msgs);
  juce::ScopedNoDenormals no_denormals;

  const int input_chans = getTotalNumInputChannels();
  const int output_chans = getTotalNumOutputChannels();

  for (int chan = input_chans; chan < output_chans; ++chan) {
    buffer.clear(chan, 0, buffer.getNumSamples());
  }

  for (int chan = 0; chan < kNumberChans; ++chan) {
    auto *data = buffer.getWritePointer(chan);
    reverbs_[chan].processMono(data, buffer.getNumSamples());
  }
}

juce::AudioProcessorEditor *BalezVerbProcessor::createEditor() {
  return new BalezVerbEditor(*this);
}

void BalezVerbProcessor::setParameters(const juce::Reverb::Parameters &params) {
  for (int i = 0; i < kNumberChans; ++i) {
    reverbs_[i].setParameters(params);
  }
}

// This creates new instances of the plugin.
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new BalezVerbProcessor();
}

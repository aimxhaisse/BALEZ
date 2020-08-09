#include <juce_audio_basics/juce_audio_basics.h>

#include "BALEZverb_editor.h"
#include "BALEZverb_processor.h"

BalezVerbProcessor::BalezVerbProcessor()
    : BalezProcessorBase(
          BusesProperties()
              .withInput("Input", juce::AudioChannelSet::stereo())
              .withOutput("Output", juce::AudioChannelSet::stereo())
              .withInput("Sidechain", juce::AudioChannelSet::stereo())) {
  addParameter(
      new juce::AudioParameterFloat("REVERBRoom", "room", 0.0, 1.0, 0.5));
  addParameter(
      new juce::AudioParameterFloat("REVERBDamping", "damping", 0.0, 1.0, 0.5));
  addParameter(
      new juce::AudioParameterFloat("REVERBWetLevel", "wet", 0.0, 1.0, 0.33));
  addParameter(
      new juce::AudioParameterFloat("REVERBDryLevel", "dry", 0.0, 1.0, 0.4));
  addParameter(
      new juce::AudioParameterFloat("REVERBWidth", "width", 0.0, 1.0, 1.0));
  addParameter(
      new juce::AudioParameterFloat("REVERBFreeze", "freeze", 0.0, 1.0, 0.5));

  for (auto &parameter : getParameters()) {
    parameter->addListener(this);
  }
}

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

void BalezVerbProcessor::reloadParameters() {
  juce::Reverb::Parameters params;

  params.roomSize = getParameterValue(PARAM_ROOM);
  params.damping = getParameterValue(PARAM_DAMPING);
  params.wetLevel = getParameterValue(PARAM_WET);
  params.dryLevel = getParameterValue(PARAM_DRY);
  params.width = getParameterValue(PARAM_WIDTH);
  params.freezeMode = getParameterValue(PARAM_FREEZE);

  for (int i = 0; i < kNumberChans; ++i) {
    reverbs_[i].setParameters(params);
  }
}

void BalezVerbProcessor::parameterValueChanged(int idx, float value) {
  setParameterValue(idx, value);

  reloadParameters();
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new BalezVerbProcessor();
}

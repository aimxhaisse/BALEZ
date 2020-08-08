#include <juce_audio_basics/juce_audio_basics.h>

#include "BALEZverb_editor.h"
#include "BALEZverb_processor.h"

BalezVerbProcessor::BalezVerbProcessor()
    : AudioProcessor(
          BusesProperties()
              .withInput("Input", juce::AudioChannelSet::stereo())
              .withOutput("Output", juce::AudioChannelSet::stereo())
              .withInput("Sidechain", juce::AudioChannelSet::stereo())) {}

BalezVerbProcessor::~BalezVerbProcessor() {}

const juce::String BalezVerbProcessor::getName() const {
  return JucePlugin_Name;
}

bool BalezVerbProcessor::acceptsMidi() const { return false; }
bool BalezVerbProcessor::producesMidi() const { return false; }
bool BalezVerbProcessor::isMidiEffect() const { return false; }

double BalezVerbProcessor::getTailLengthSeconds() const { return 0.0; }

int BalezVerbProcessor::getNumPrograms() {
  return 1; // NB: some hosts don't cope very well if you tell them there are
            // 0 programs, so this should be at least 1, even if you're not
            // really implementing programs.
}

int BalezVerbProcessor::getCurrentProgram() { return 0; }

void BalezVerbProcessor::setCurrentProgram(int index) {
  juce::ignoreUnused(index);
}

const juce::String BalezVerbProcessor::getProgramName(int index) {
  juce::ignoreUnused(index);
  return {};
}

void BalezVerbProcessor::changeProgramName(int index,
                                           const juce::String &newName) {
  juce::ignoreUnused(index, newName);
}

void BalezVerbProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  juce::ignoreUnused(samplesPerBlock);

  for (int i = 0; i < kNumberChans; ++i) {
    reverbs_[i].setSampleRate(sampleRate);
  }
}

void BalezVerbProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.

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

  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
  for (int chan = input_chans; chan < output_chans; ++chan) {
    buffer.clear(chan, 0, buffer.getNumSamples());
  }

  for (int chan = 0; chan < kNumberChans; ++chan) {
    auto *data = buffer.getWritePointer(chan);
    reverbs_[chan].processMono(data, buffer.getNumSamples());
  }
}

bool BalezVerbProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor *BalezVerbProcessor::createEditor() {
  return new BalezVerbEditor(*this);
}

void BalezVerbProcessor::getStateInformation(juce::MemoryBlock &destData) {
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
}

void BalezVerbProcessor::setStateInformation(const void *data,
                                             int sizeInBytes) {
  // You should use this method to restore your parameters from this memory
  // block, whose contents will have been created by the getStateInformation()
  // call.
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

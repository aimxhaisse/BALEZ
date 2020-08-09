#include "BALEZprocessor_base.h"

BalezProcessorBase::BalezProcessorBase(const BusesProperties &layouts)
    : juce::AudioProcessor(layouts) {}

bool BalezProcessorBase::hasEditor() const { return true; }

bool BalezProcessorBase::acceptsMidi() const { return false; }

bool BalezProcessorBase::producesMidi() const { return false; }

bool BalezProcessorBase::isMidiEffect() const { return false; }

double BalezProcessorBase::getTailLengthSeconds() const { return 0.0; }

int BalezProcessorBase::getNumPrograms() { return 1; }

int BalezProcessorBase::getCurrentProgram() { return 0; }

void BalezProcessorBase::setCurrentProgram(int) {}

const juce::String BalezProcessorBase::getProgramName(int) { return {}; }

void BalezProcessorBase::changeProgramName(int, const juce::String &) {}

void BalezProcessorBase::getStateInformation(juce::MemoryBlock &dest) {}

void BalezProcessorBase::setStateInformation(const void *data, int size) {}

void BalezProcessorBase::parameterValueChanged(int idx, float value) {}

void BalezProcessorBase::parameterGestureChanged(int idx, bool gesture) {}

float BalezProcessorBase::getParameterValue(int index) {
  return getParameters().getReference(index)->getValue();
}

void BalezProcessorBase::setParameterValue(int index, float value) {
  return getParameters().getReference(index)->setValue(value);
}

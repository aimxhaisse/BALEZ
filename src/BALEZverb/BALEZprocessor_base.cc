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

void BalezProcessorBase::getStateInformation(juce::MemoryBlock &dest) {
  std::unique_ptr<juce::XmlElement> xml(new juce::XmlElement("BALEZplug-in"));
  for (auto &param : getParameters()) {
    xml->setAttribute(param->getName(512),
                      static_cast<double>(param->getValue()));
  }
  copyXmlToBinary(*xml, dest);
}

void BalezProcessorBase::setStateInformation(const void *data, int size) {
  std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, size));
  if (xml.get() && xml->hasTagName("BALEZplug-in")) {
    for (auto &param : getParameters()) {
      param->setValue(
          xml->getDoubleAttribute(param->getName(512), param->getValue()));
    }
  }
}

void BalezProcessorBase::parameterValueChanged(int idx, float value) {}

void BalezProcessorBase::parameterGestureChanged(int idx, bool gesture) {}

float BalezProcessorBase::getParameterValue(int index) {
  return getParameters().getReference(index)->getValue();
}

void BalezProcessorBase::setParameterValue(int index, float value) {
  return getParameters().getReference(index)->setValue(value);
}

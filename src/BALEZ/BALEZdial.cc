#include "BALEZdial.h"
#include "BALEZ/BALEZconstants.h"

BalezDial::BalezDial(const juce::String &name) : name_(name) {}

BalezDial::~BalezDial() {}

void BalezDial::bindParameter(juce::RangedAudioParameter &parameter) {
  parameter_ = &parameter;
}

void BalezDial::setInitialPosition(int x, int y) {
  initial_x_ = x;
  initial_y_ = y;
}

void BalezDial::setIndex(int idx) { index_ = idx; }

void BalezDial::setUp(juce::AudioProcessorEditor &editor) {
  dial_ = std::make_unique<juce::Slider>();
  dial_->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  dial_->setSliderStyle(juce::Slider::Rotary);
  const auto &range = parameter_->getNormalisableRange().getRange();
  dial_->setRange(range.getStart(), range.getEnd(), kValueIncrement);
  dial_->setValue(parameter_->getValue());
  dial_->addListener(this);
  editor.addAndMakeVisible(dial_.get());

  description_ = std::make_unique<juce::DrawableText>();
  description_->setColour(juce::Colours::white);
  description_->setFont(juce::Font(16.0f, juce::Font::plain), true);
  description_->setJustification(juce::Justification::centred);
  description_->setText(name_);
  editor.addAndMakeVisible(description_.get());
}

void BalezDial::resized() {
  const int start_x = initial_x_ + index_ * kDialWidth;
  const int start_y = initial_y_;

  dial_->setBounds(start_x, start_y, kSizeWidth, kDialHeight);
  description_->setBoundingBox(juce::Rectangle<float>(
      start_x, start_y + kDialHeight, kSizeWidth, kDialTextHeight));
}

void BalezDial::sliderValueChanged(juce::Slider *slider) {
  parameter_->sendValueChangedMessageToListeners(slider->getValue());
}

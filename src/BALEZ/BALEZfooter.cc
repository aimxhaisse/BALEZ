#include "BALEZfooter.h"

void BalezFooter::setUp(juce::AudioProcessorEditor &editor) {
  footer_.setColour(juce::Colours::white);
  footer_.setFont(juce::Font(10.0f, juce::Font::plain), true);
  footer_.setText(__DATE__ " - " __TIME__);
  footer_.setJustification(juce::Justification::right);

  editor.addAndMakeVisible(footer_);
}

void BalezFooter::resized() {
  footer_.setBoundingBox(juce::Rectangle<float>(
      kPaddingWidth, kHeaderHeight + kDialHeight + kPaddingHeight,
      kSizeWidth - 2 * kPaddingWidth, kFooterHeight - 2 * kPaddingHeight));
}

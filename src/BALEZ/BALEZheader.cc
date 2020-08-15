#include "BALEZheader.h"

void BalezHeader::setUp(juce::AudioProcessorEditor &editor,
                        const juce::String &name) {
  header_.setColour(juce::Colours::white);
  header_.setFont(juce::Font(25.0f, juce::Font::plain), true);
  header_.setText(name);
  header_.setJustification(juce::Justification::left);

  editor.addAndMakeVisible(header_);
}

void BalezHeader::resized() {
  header_.setBoundingBox(juce::Rectangle<float>(
      kPaddingWidth, kPaddingHeight, kSizeWidth - 2 * kPaddingWidth,
      kHeaderHeight - 2 * kPaddingHeight));
}

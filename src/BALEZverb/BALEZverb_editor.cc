#include "BALEZverb_editor.h"
#include "BALEZverb_processor.h"

namespace {

constexpr int kPaddingWidth = 15;
constexpr int kPaddingHeight = 10;

constexpr int kHeaderHeight = 20 + 2 * kPaddingWidth;
constexpr int kFooterHeight = 10 + 2 * kPaddingHeight;

constexpr int kDialTextHeight = 40;
constexpr int kDialWidth = 100;
constexpr int kDialHeight = kDialWidth + kDialTextHeight;

constexpr int kSizeWidth = BalezVerbEditor::kDialCount * kDialWidth;
constexpr int kSizeHeight = kHeaderHeight + kFooterHeight + kDialHeight;

} // namespace

BalezVerbEditor::BalezVerbEditor(BalezVerbProcessor &proc)
    : AudioProcessorEditor(&proc), proc_(proc) {

  header_.setColour(juce::Colours::white);
  header_.setFont(juce::Font(25.0f, juce::Font::plain), true);
  header_.setText("BALEZverb");
  header_.setJustification(juce::Justification::left);

  addAndMakeVisible(header_);

  for (int i = 0; i < kDialCount; ++i) {
    dials_[i].setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    dials_[i].setSliderStyle(juce::Slider::Rotary);
    addAndMakeVisible(dials_[i]);

    descriptions_[i].setColour(juce::Colours::white);
    descriptions_[i].setFont(juce::Font(16.0f, juce::Font::plain), true);
    descriptions_[i].setJustification(juce::Justification::centred);
    addAndMakeVisible(descriptions_[i]);
  }

  descriptions_[0].setText("room");
  descriptions_[1].setText("damping");
  descriptions_[2].setText("wet");
  descriptions_[3].setText("dry");
  descriptions_[4].setText("width");
  descriptions_[5].setText("freeze");

  footer_.setColour(juce::Colours::white);
  footer_.setFont(juce::Font(10.0f, juce::Font::plain), true);
  footer_.setText(__DATE__ " - " __TIME__);
  footer_.setJustification(juce::Justification::right);
  addAndMakeVisible(footer_);

  setSize(kSizeWidth, kSizeHeight);
}

BalezVerbEditor::~BalezVerbEditor() {}

void BalezVerbEditor::paint(juce::Graphics &gfx) {
  gfx.fillAll(juce::Colours::darkgrey);
}

void BalezVerbEditor::resized() {
  header_.setBoundingBox(juce::Rectangle<float>(
      kPaddingWidth, kPaddingHeight, kSizeWidth - 2 * kPaddingWidth,
      kHeaderHeight - 2 * kPaddingHeight));

  for (int i = 0; i < kDialCount; ++i) {
    dials_[i].setBounds(i * kDialWidth, kHeaderHeight, kDialWidth, kDialHeight);
    descriptions_[i].setBoundingBox(juce::Rectangle<float>(
        i * kDialWidth, kHeaderHeight + kDialHeight - kDialTextHeight,
        kDialWidth, kDialTextHeight));
  }

  footer_.setBoundingBox(juce::Rectangle<float>(
      kPaddingWidth, kHeaderHeight + kDialHeight + kPaddingHeight,
      kSizeWidth - 2 * kPaddingWidth, kFooterHeight - 2 * kPaddingHeight));
}

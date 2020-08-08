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

enum {
  CONFIG_ROOM = 0,
  CONFIG_DAMPING = 1,
  CONFIG_WET = 2,
  CONFIG_DRY = 3,
  CONFIG_WIDTH = 4,
  CONFIG_FREEZE = 5
};

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
    dials_[i].setRange(0.0, 1.0, 0.001);
    dials_[i].addListener(this);
    addAndMakeVisible(dials_[i]);

    descriptions_[i].setColour(juce::Colours::white);
    descriptions_[i].setFont(juce::Font(16.0f, juce::Font::plain), true);
    descriptions_[i].setJustification(juce::Justification::centred);
    addAndMakeVisible(descriptions_[i]);
  }

  descriptions_[CONFIG_ROOM].setText("room");
  descriptions_[CONFIG_DAMPING].setText("damping");
  descriptions_[CONFIG_WET].setText("wet");
  descriptions_[CONFIG_DRY].setText("dry");
  descriptions_[CONFIG_WIDTH].setText("width");
  descriptions_[CONFIG_FREEZE].setText("freeze");

  dials_[CONFIG_ROOM].setValue(0.5f);
  dials_[CONFIG_DAMPING].setValue(0.5f);
  dials_[CONFIG_WET].setValue(0.33f);
  dials_[CONFIG_DRY].setValue(0.4f);
  dials_[CONFIG_WIDTH].setValue(1.0f);
  dials_[CONFIG_FREEZE].setValue(0.0f);

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

void BalezVerbEditor::sliderValueChanged(juce::Slider *slider) {
  juce::Reverb::Parameters params;

  params.roomSize = dials_[CONFIG_ROOM].getValue();
  params.damping = dials_[CONFIG_DAMPING].getValue();
  params.wetLevel = dials_[CONFIG_WET].getValue();
  params.dryLevel = dials_[CONFIG_DRY].getValue();
  params.width = dials_[CONFIG_WIDTH].getValue();
  params.freezeMode = dials_[CONFIG_FREEZE].getValue();

  proc_.setParameters(params);
}

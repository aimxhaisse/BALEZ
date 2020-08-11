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

constexpr int kSizeWidth = 600;
constexpr int kSizeHeight = kHeaderHeight + kFooterHeight + kDialHeight;

} // namespace

BalezVerbEditor::BalezVerbEditor(BalezVerbProcessor &proc)
    : AudioProcessorEditor(&proc), proc_(proc) {

  header_.setColour(juce::Colours::white);
  header_.setFont(juce::Font(25.0f, juce::Font::plain), true);
  header_.setText("BALEZverb");
  header_.setJustification(juce::Justification::left);
  addAndMakeVisible(header_);

  // Order here needs to follow the order of the enum: the identifier
  // created by addNewDial is incremental and is used to refer to the
  // parameter. Not following the order here results in a crash or
  // weird behaviour without warning.
  dial_bar_.addNewDial("Room", PARAM_ROOM);
  dial_bar_.addNewDial("Damping", PARAM_DAMPING);
  dial_bar_.addNewDial("Wet", PARAM_WET);
  dial_bar_.addNewDial("Dry", PARAM_DRY);
  dial_bar_.addNewDial("Width", PARAM_WIDTH);
  dial_bar_.addNewDial("Freeze", PARAM_FREEZE);
  dial_bar_.setUp(*this);

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

  dial_bar_.resized();

  footer_.setBoundingBox(juce::Rectangle<float>(
      kPaddingWidth, kHeaderHeight + kDialHeight + kPaddingHeight,
      kSizeWidth - 2 * kPaddingWidth, kFooterHeight - 2 * kPaddingHeight));
}

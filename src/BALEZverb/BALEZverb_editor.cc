#include "BALEZverb_editor.h"
#include "BALEZ/BALEZconstants.h"
#include "BALEZverb_processor.h"

BalezVerbEditor::BalezVerbEditor(BalezVerbProcessor &proc)
    : AudioProcessorEditor(&proc), proc_(proc) {
  header_.setUp(*this, "BALEZverb");

  dial_bar_.setInitialPosition(0, header_.getHeight());
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
  header_.resized();
  dial_bar_.resized();

  footer_.setBoundingBox(juce::Rectangle<float>(
      kPaddingWidth, kHeaderHeight + kDialHeight + kPaddingHeight,
      kSizeWidth - 2 * kPaddingWidth, kFooterHeight - 2 * kPaddingHeight));
}

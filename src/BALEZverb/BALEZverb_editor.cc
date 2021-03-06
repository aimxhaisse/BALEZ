#include "BALEZverb_editor.h"
#include "BALEZ/BALEZconstants.h"
#include "BALEZverb_processor.h"

BalezVerbEditor::BalezVerbEditor(BalezVerbProcessor &proc)
    : AudioProcessorEditor(&proc), proc_(proc) {
  header_.setUp(*this, "BALEZverb");

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
  dial_bar_.setInitialPosition(0, header_.getHeight());

  footer_.setUp(*this);

  setSize(kSizeWidth, kSizeHeight);
}

BalezVerbEditor::~BalezVerbEditor() {}

void BalezVerbEditor::paint(juce::Graphics &gfx) {
  gfx.fillAll(juce::Colours::darkgrey);
}

void BalezVerbEditor::resized() {
  header_.resized();
  dial_bar_.resized();
  footer_.resized();
}

#include "BALEZverb_editor.h"
#include "BALEZverb_processor.h"

namespace {

constexpr int kPadding = 25;

constexpr int kSizeWidth = 800;
constexpr int kSizeHeight = 600;

} // namespace

BalezVerbEditor::BalezVerbEditor(BalezVerbProcessor &proc)
    : AudioProcessorEditor(&proc), proc_(proc) {
  setSize(kSizeWidth, kSizeHeight);
}

BalezVerbEditor::~BalezVerbEditor() {}

void BalezVerbEditor::paintBuildDate(juce::Graphics &gfx) {
  gfx.setColour(juce::Colours::white);
  gfx.setFont(10.0f);
  gfx.drawSingleLineText(__DATE__ " - " __TIME__, kPadding, kPadding);
}

void BalezVerbEditor::paint(juce::Graphics &gfx) {
  gfx.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  paintVersion(gfx);

  gfx.setColour(juce::Colours::white);
  gfx.setFont(15.0f);
  gfx.drawFittedText("BALEZverb - Le reverb des BALEZES", getLocalBounds(),
                     juce::Justification::centred, 1);
}

void BalezVerbEditor::resized() {}

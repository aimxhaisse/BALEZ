#include "BALEZverb_editor.h"
#include "BALEZverb_processor.h"

namespace {

constexpr int kPadding = 25;

constexpr int kSizeWidth = 800;
constexpr int kSizeHeight = 600;

} // namespace

BalezVerbEditor::BalezVerbEditor(BalezVerbProcessor &p)
    : AudioProcessorEditor(&p), proc_(p) {
  setSize(kSizeWidth, kSizeHeight);
}

BalezVerbEditor::~BalezVerbEditor() {}

void BalezVerbEditor::paint(juce::Graphics &g) {
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  g.setColour(juce::Colours::white);
  g.setFont(10.0f);
  g.drawSingleLineText(__DATE__ " - " __TIME__, kPadding, kPadding);

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("BALEZverb - Le reverb des BALEZES", getLocalBounds(),
                   juce::Justification::centred, 1);
}

void BalezVerbEditor::resized() {}

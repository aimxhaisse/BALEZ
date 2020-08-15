#pragma once

#include <memory>
#include <utility>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

// A class to reprent and manipulate a dial, this is wrapped together
// so we get to update the style and behavior of all buttons at once.
//
// One property of BALEZ plug-ins is their randomize button, this is
// achieved for all dials through this class.
class BalezDial : public juce::Slider::Listener {
public:
  static constexpr float kValueIncrement = 0.001;

  BalezDial(const juce::String &name);
  ~BalezDial();

  void setName(const juce::String &name);
  void setInitialPosition(int x, int y);
  void setIndex(int idx);
  void bindParameter(juce::RangedAudioParameter &parameter);

  void sliderValueChanged(juce::Slider *slider);
  void setUp(juce::AudioProcessorEditor &editor);
  void resized();

private:
  juce::String name_;

  int initial_x_ = 0;
  int initial_y_ = 0;
  int index_ = 0;

  std::unique_ptr<juce::Slider> dial_;
  std::unique_ptr<juce::DrawableText> description_;

  // This is owned by the processor thread.
  juce::RangedAudioParameter *parameter_ = nullptr;
};

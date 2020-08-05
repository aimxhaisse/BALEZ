#include "DistrhoPlugin.hpp"

START_NAMESPACE_DISTRHO

class BALEZVerb : public Plugin {
public:
  BALEZVerb() : Plugin(9, 2, 0) {}

  const char *getLabel() const override { return "BALEZverb"; }
  const char *getDescription() const override { return "BALEZ Reverb Plugin"; }
  const char *getMaker() const override { return "mxs"; }
  const char *getHomePage() const override { return "https://mxs.sbrk.org/"; }
  const char *getLicense() const override { return "copyright mxs@sbrk.org"; }

  uint32_t getVersion() const override { return d_version(1, 0, 0); }
  int64_t getUniqueId() const override { return d_cconst('B', 'L', 'Z', 'r'); }

  void run(const float **inputs, float **outputs, uint32_t frames) {
    if (outputs[0] != inputs[0]) {
      std::memcpy(outputs[0], inputs[0], sizeof(float) * frames);
    }

    if (outputs[1] != inputs[1]) {
      std::memcpy(outputs[1], inputs[1], sizeof(float) * frames);
    }
  }

  void initProgramName(uint32_t index, String &programName) {}
  void initParameter(uint32_t index, Parameter &parameter) {}

  float getParameterValue(uint32_t index) const { return 0.0; }
  void setParameterValue(uint32_t index, float value) {}

  void loadProgram(uint32_t index) {}
};

Plugin *createPlugin() { return new BALEZVerb(); }

END_NAMESPACE_DISTRHO

#pragma once

#include "Event.h"

namespace LG {

  class LG_API KeyEvent : public Event
  {
  public:
    inline int GetKeyCode() { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

  protected:
    KeyEvent(int keyCode)
      : m_KeyCode(keyCode) {}

    int m_KeyCode;
  };

  class LG_API KeyPressedEvent : public KeyEvent
  {
  public:
    KeyPressedEvent(int keyCode, int repeatCount)
      : KeyEvent(keyCode)
      , m_RepeatCount(repeatCount) {}

    inline int GetRepeatCount() const { return m_RepeatCount; }

    virtual std::string ToString() const override
    {
      std::stringstream ss;
      ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)

  private:
    int m_RepeatCount;
  };

  class LG_API KeyReleasedEvent : public KeyEvent
  {
  public:
    KeyReleasedEvent(int keyCode)
      : KeyEvent(keyCode) {}

    virtual std::string ToString() const override
    {
      std::stringstream ss;
      ss << "KeyReleasedEvent: " << m_KeyCode;
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
  };


}
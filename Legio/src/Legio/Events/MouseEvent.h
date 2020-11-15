#pragma once

#include "Event.h"


namespace LG {

  class LG_API MouseMovedEvent : public Event
  {
  public:
    MouseMovedEvent(float x, float y)
      : m_MouseX(x)
      , m_MouseY(y) {}

    inline float GetX() const { return m_MouseX; }
    inline float GetY() const { return m_MouseY; }

    virtual std::string ToString() const override
    {
      std::stringstream ss;
      ss << "MouseMovedEvent: " << m_MouseX << "," << m_MouseY;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    int m_MouseX;
    int m_MouseY;
  };


  class LG_API MouseScrolledEvent : public Event
  {
  public:
    MouseScrolledEvent(float xOffset, float yOffset)
      : m_XOffset(xOffset)
      , m_YOffset(yOffset) {}

    inline float GetXOffset() const { return m_XOffset; }
    inline float GetYOffset() const { return m_YOffset; }

    virtual std::string ToString() const override
    {
      std::stringstream ss;
      ss << "MouseScrolledEvent: " << m_XOffset << "," << m_YOffset;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    int m_XOffset;
    int m_YOffset;
  };

  class LG_API MouseButtonEvent : public Event
  {
  public:
    inline int getMouseButton() const { return m_Button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  protected:
    MouseButtonEvent(int button)
      : m_Button(button) {}

    int m_Button;
  };

  class LG_API MouseButtonPressedEvent : public MouseButtonEvent
  {
  public:

    MouseButtonPressedEvent(int button)
      : MouseButtonEvent(button)
      {}

    virtual std::string ToString() const override
    {
      std::stringstream ss;
      ss << "MouseButtonPressed: " << m_Button;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)

  };

  class LG_API MouseButtonReleasedEvent : public MouseButtonEvent
  {
  public:

    MouseButtonReleasedEvent(int button)
      : MouseButtonEvent(button) {}

    virtual std::string ToString() const override
    {
      std::stringstream ss;
      ss << "MouseButtonReleasedEvent: " << m_Button;
      return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
  };

}

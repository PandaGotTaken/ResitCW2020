#pragma once

#include "event.h"
#include <glm/glm.hpp>

namespace IMAT3905 {

	/**
	* \class MouseMovedEvent
	* MouseMovedEvent class with implementation
	*/

	class MouseMovedEvent : public Event
	{
	private:
		float m_mouseX, m_mouseY;
	public:
		MouseMovedEvent(float x, float y); //!< Basic constructor with mouse position
		static EventType getStaticType(); 
		virtual EventType getEventType() const override;
		virtual int getCategoryFlags() const override;
		inline float getX() const;
		inline float getY() const;
		inline glm::ivec2 getPos() const;
	};

	/**
	* \class MouseScrolledEvent
	* MouseScrolledEvent class with implementation
	*/
	class MouseScrolledEvent : public Event
	{
	private:
		float m_xOffset, m_yOffset;
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

		static EventType getStaticType(); //!< Return the event type with a static function
		virtual EventType getEventType() const override; //!< Return the event type
		virtual int getCategoryFlags() const override; //!< Return the event categories as a bit string
		inline float getXOffset() const; //!< Return the scroll offset in x
		inline float getYOffset() const; //!< Return the scroll offset in y
	};

	/**
	* \class MouseButtonPressedEvent
	* MouseButtonPressedEvent class with implementation
	*/
	class MouseButtonPressedEvent : public Event
	{
	private:
		int m_button;
	public:
		MouseButtonPressedEvent(int button); //!< Basic constructor with button ID
		static EventType getStaticType(); //!< Return the event type with a static function
		virtual EventType getEventType() const override; //!< Return the event type
		virtual int getCategoryFlags() const override; //!< Return the event categories as a bit string
		inline int getButton() const; //!< Return the button ID
	};

	/**
	* \class MouseButtonReleasedEvent
	* MouseButtonReleasedEvent class with implementation
	*/
	class MouseButtonReleasedEvent : public Event
	{
	private:
		int m_button;
	public:
		MouseButtonReleasedEvent(int button); //!< Basic constructor with button ID
		static EventType getStaticType(); //!< Return the event type with a static function
		virtual EventType getEventType() const override; //!< Return the event type
		virtual int getCategoryFlags() const override; //!< Return the event categories as a bit string
		inline int getButton() const; //!< Return the button ID
	};

}
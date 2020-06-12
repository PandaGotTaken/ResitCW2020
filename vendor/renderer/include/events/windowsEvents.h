#pragma once

#include "event.h"

#include <glm/glm.hpp>

namespace IMAT3905 {

	/**
	* \class WindowCloseEvent
	* WindowCloseEvent class with implementation
	*/

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(); //!< Empty Constructor
		static EventType getStaticType(); //!< Return the event type with a static function
		virtual EventType getEventType() const override; //!< Return the event type
		virtual int getCategoryFlags() const override; //!< Return the event categories as a bit string
	};

	/**
	* \class WindowResizeEvent
	* WindowResizeEvent class with implementation
	*/

	class WindowResizeEvent : public Event
	{
	private:
		int m_width; //!< Windows new width
		int m_height; //!< Windows new height
	public:
		WindowResizeEvent(int width, int height); //!< Copnstructor with new width and height
		static EventType getStaticType(); //!< Return the event type with a static function
		virtual EventType getEventType() const override; //!< Return the event type
		virtual int getCategoryFlags() const override; //!< Return the event categories as a bit string
		int getWidth() const; //!< Return the new width of the window
		int getHeight() const; //!< Return the new height of the window
		glm::ivec2 getSize() const; //!< Return the size of the window
	};

	/**
	* \class WindowLostFocusEvent
	* WindowLostFocusEvent class with implementation
	*/
	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent(); //!< Empty constructor
		static EventType getStaticType(); //!< Return the event type with a static function
		virtual EventType getEventType() const override; //!< Return the event type
		virtual int getCategoryFlags() const override; //!< Return the event categories as a bit string
	};

	/**
	* \class WindowMovedEvent
	* WindowMovedEvent class with implementation
	*/
	class WindowMovedEvent : public Event
	{
	private:
		int m_xPos; //!< New position in x
		int m_yPos; //!< New position in y
	public:
		WindowMovedEvent(int x, int y); //!< Constructor with new x and y position
		static EventType getStaticType(); //!< Return the event type with a static function
		virtual EventType getEventType() const override; //!< Return the event type
		virtual int getCategoryFlags() const override; //!< Return the event categories as a bit string
		int getXPos() const; //!< Return the new position of the window in x
		int getYPos() const;//!< Return the new position of the window in y
		glm::ivec2 getPos() const;//!< Return the new position of the window in x and y
	};
}


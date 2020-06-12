/** \file event.h
*/

#pragma once

#include <functional>
#include <string>

namespace IMAT3905 {
	/**
	* \Enum EventType
	* Enum type for event types
	*/
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/**
	* \Enum EventCategory
	* Enum type for event categories
	*/
	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0,      // 00000001
		EventCategoryInput = 1 << 1,       // 00000010
		EventCategoryKeyboard = 1 << 2,    // 00000100
		EventCategoryMouse = 1 << 3,       // 00001000
		EventCategoryMouseButton = 1 << 4  // 00010000
	};

	/**
	* \class Event
	* base class
	*/

	class Event
	{
	private:
		bool m_handled = false;
	public:
		virtual EventType getEventType() const = 0; //!< Return the event type
		virtual int getCategoryFlags() const = 0; //!< Return the event categories as a bit string
		bool handled() const; //!< Has the event been handled
		void handle(bool isHandled); //!< Handle the event
		bool isInCategory(EventCategory category); //!< Is this event in the category?
	};

	/**
	* \class EventDispatcher
	*/

	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_event(event)
		{
		}

		template<typename T>
		bool dispatch(EventFunc<T> func)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.handle(func(*((T*)&m_event)));
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};
}
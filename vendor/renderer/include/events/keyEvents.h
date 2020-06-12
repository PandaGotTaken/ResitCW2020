#pragma once

#include "event.h"

namespace IMAT3905 {

	/**
	* \class KeyEvent
	* KeyEvent base class
	*/

	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int keyCode); //!< Basic contructor with keycode
		int m_keyCode; //!< Interal code of the ID key being pressed
	public:
		int GetKeyCode() const; //!< Return the ID for this key event
		virtual int getCategoryFlags() const override; //!< Return the event categories as a bit string
	};

	/**
	* \class KeyPressedEvent
	* KeyPressedEvent class with implementation
	*/
	class KeyPressedEvent : public KeyEvent
	{
	private:
		int m_repeatCount; //!< Has the key been pressed before, is it a repeat key 0 or 1
	public:
		KeyPressedEvent(int keycode, int repeatCount); //!< Basic constructor with with code and repeat count
		int GetRepeatCount() const; //!< Return the repeat count
		static EventType getStaticType(); //!< Return the event type with a static function
		virtual EventType getEventType() const override; //!< Return the event type
	};

	/**
	* \class KeyReleasedEvent
	* KeyReleasedEvent class with implementation
	*/
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode); //!< Basic contructor with keycode
		static EventType getStaticType(); //!< Return the event type with a static function
		virtual EventType getEventType() const override; //!< Return the event type
	};

	/**
	* \class KeyTypedEvent
	* KeyTypedEvent class with implementation
	*/
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode); //!< Basic contructor with keycode
		static EventType getStaticType(); //!< Return the event type with a static function
		virtual EventType getEventType() const override; //!< Return the event type
	};
}